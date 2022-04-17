#include "GfxCtx.h"
#include "Heap.h"

GfxCtx* gpGfxCtx;

void GfxCtx_Construct(GfxCtx* thisx) {
    u32 index;

    thisx->taskList = (OSTask){
        M_GFXTASK,
        OS_TASK_DP_WAIT | OS_TASK_LOADABLE,
        rspbootTextStart,
        (SIZE_TYPE)rspbootTextEnd - (SIZE_TYPE)rspbootTextStart,
        gspF3DEX2_fifoTextStart,
        SP_UCODE_SIZE,
        gspF3DEX2_fifoDataStart,
        SP_UCODE_DATA_SIZE,
        NULLPTR,
        NULL,
        thisx->rdpFifo,
        (SIZE_TYPE)thisx->rdpFifo + (SIZE_TYPE)RDPFIFO_SIZE,
        NULLPTR,
        NULL,
        thisx->rspYield,
        OS_YIELD_DATA_SIZE
    };

    osCreateMesgQueue(&thisx->rspMessageQ, &thisx->rspMessageBuf, 1);
    osCreateMesgQueue(&thisx->rdpMessageQ, &thisx->rdpMessageBuf, 1);
    osCreateMesgQueue(&thisx->retraceMessageQ, &thisx->retraceMessageBuf, 1);

    osSetEventMesg(OS_EVENT_SP, &thisx->rspMessageQ, NULL);
    osSetEventMesg(OS_EVENT_DP, &thisx->rdpMessageQ, NULL);
    osViSetEvent(&thisx->retraceMessageQ, NULL, 1);

    for (index = 0; index < FRAMEBUFFER_COUNT; index++) {
        thisx->glist[index] = malloc(sizeof(Gfx) * 4096);
        memset_u64(thisx->glist[index], 0, sizeof(Gfx) * 4096);
    }

    thisx->framebufferIndex = 0;
    thisx->dlist = thisx->glist[0];

    thisx->viewport.vp = (Vp_t){
	    gScreenResX * 2, gScreenResY * 2, G_MAXZ / 2, 0,
	    gScreenResX * 2, gScreenResY * 2, G_MAXZ / 2, 0,
    };
}

void GfxCtx_GfxBegin(GfxCtx* thisx) {
    u16* cfb = gFramebuffer[thisx->framebufferIndex];

   thisx->dlist = thisx->glist[thisx->framebufferIndex]; 

    // setup common segments
    gSPSegment(thisx->dlist++, SEGMENT_CFB, cfb);
    gSPSegment(thisx->dlist++, SEGMENT_ZFB, gFramebuffer[FRAMEBUFFER_INDEX_Z]);
    gSPSegment(thisx->dlist++, SEGMENT_CODE, __code_start);

    // rsp init
    gSPViewport(thisx->dlist++, &thisx->viewport);
    gSPClearGeometryMode(thisx->dlist++, 0xFFFFFFFF); // clear everything
    gSPSetGeometryMode(thisx->dlist++, G_SHADE | G_SHADING_SMOOTH | G_ZBUFFER | G_CULL_BACK);
    gSPTexture(thisx->dlist++, 0, 0, 0, 0, G_OFF);

    // rdp init
    gDPSetRenderMode(thisx->dlist++, G_RM_OPA_SURF, G_RM_OPA_SURF2);
    gDPSetCombineMode(thisx->dlist++, G_CC_SHADE, G_CC_SHADE);
    gDPSetScissor(thisx->dlist++, G_SC_NON_INTERLACE, 0, 0, gScreenResX, gScreenResY);
    gDPSetColorDither(thisx->dlist++, G_CD_BAYER);

    // clear zbuffer
    gDPSetDepthImage(thisx->dlist++, SEGMENT_BASE(SEGMENT_ZFB));
    gDPSetCycleType(thisx->dlist++, G_CYC_FILL);
    gDPSetColorImage(thisx->dlist++, G_IM_FMT_RGBA, G_IM_SIZ_16b, gScreenResX, SEGMENT_BASE(SEGMENT_ZFB));

    // fill with max z
    gDPSetFillColor(thisx->dlist++, GPACK_ZDZ(G_MAXFBZ, 0) << 16 | GPACK_ZDZ(G_MAXFBZ, 0));
    gDPFillRectangle(thisx->dlist++, 0, 0, gScreenResX - 1, gScreenResY - 1);
    gDPPipeSync(thisx->dlist++);

    // clear framebuffer
    gDPSetColorImage(thisx->dlist++, G_IM_FMT_RGBA, G_IM_SIZ_16b, gScreenResX, SEGMENT_BASE(SEGMENT_CFB));
    gDPSetFillColor(thisx->dlist++, 0);
    gDPFillRectangle(thisx->dlist++, 0, 0, gScreenResX - 1, gScreenResY - 1);
    gDPPipeSync(thisx->dlist++);

    // initial persp/view
    gSPMatrix(thisx->dlist++, OS_K0_TO_PHYSICAL(&thisx->projection), G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
    gSPMatrix(thisx->dlist++, OS_K0_TO_PHYSICAL(&thisx->view), G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
    gDPPipeSync(thisx->dlist++);

    // init various
    gDPSetCycleType(thisx->dlist++, G_CYC_1CYCLE);
    gDPSetTexturePersp(thisx->dlist++, G_TP_NONE);
    gDPSetTextureFilter(thisx->dlist++, G_TF_BILERP);

}

void GfxCtx_GfxEnd(GfxCtx* thisx) {
    // end dlist
    gDPFullSync(thisx->dlist++);
    gSPEndDisplayList(thisx->dlist++);
}

void GfxCtx_GfxSendTask(GfxCtx* thisx) {
    Gfx* glist = thisx->glist[thisx->framebufferIndex];
    Gfx* dlist = thisx->dlist;

    thisx->taskList.t.data_ptr = glist;
    thisx->taskList.t.data_size = (SIZE_TYPE)dlist - (SIZE_TYPE)glist;
    osWritebackDCache(glist, (SIZE_TYPE)dlist - (SIZE_TYPE)glist);
    osWritebackDCache(thisx, sizeof(GfxCtx));
    osSpTaskStart(&thisx->taskList);
}

void GfxCtx_GfxRetrace(GfxCtx* thisx) {
    osRecvMesg(&thisx->rdpMessageQ, NULLPTR, OS_MESG_BLOCK);
    osViSwapBuffer(gFramebuffer[thisx->framebufferIndex]);

    if (MQ_IS_FULL(&thisx->retraceMessageQ)) {
        osRecvMesg(&thisx->retraceMessageQ, NULLPTR, OS_MESG_BLOCK);
    }

    osRecvMesg(&thisx->retraceMessageQ, NULLPTR, OS_MESG_BLOCK);

    thisx->framebufferIndex = 1 - thisx->framebufferIndex;
}
