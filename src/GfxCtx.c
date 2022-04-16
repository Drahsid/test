#include "GfxCtx.h"
#include "Heap.h"
#include "linker_symbols.h"

GfxCtx* gpGfxCtx;

static Gfx sClearCFB[] = {
    gsDPSetColorImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, BASE_RES_X, SEGMENT_CFB << 24),
    gsDPSetOtherMode(G_CYC_FILL | G_PM_1PRIMITIVE | G_TP_PERSP | G_TD_CLAMP | G_TL_TILE | G_TT_NONE | G_TF_BILERP | G_TC_FILT | G_CK_NONE | G_CD_DISABLE | G_AD_DISABLE, G_AC_NONE | G_ZS_PRIM | G_RM_NOOP | G_RM_NOOP2),
    gsDPSetScissor(G_SC_NON_INTERLACE, 0, 0, BASE_RES_X, BASE_RES_Y),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsDPSetFillColor(0),
    gsDPFillRectangle(0, 0, BASE_RES_X - 1, BASE_RES_Y - 1),
    gsSPEndDisplayList()
};

static Gfx sRdpInit[] = {
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPPipelineMode(G_PM_1PRIMITIVE),
    gsDPSetScissor(G_SC_NON_INTERLACE, 0, 0, BASE_RES_X, BASE_RES_Y),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTextureConvert(G_TC_FILT),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsDPSetCombineKey(G_CK_NONE),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPSetRenderMode(G_RM_OPA_SURF, G_RM_OPA_SURF2),
    gsDPSetColorDither(G_CD_DISABLE),
    gsDPPipeSync(),
    gsSPEndDisplayList()
};

static void GfxCtx_RspInit(GfxCtx* thisx) {
    gSPViewport(thisx->dlist++, &thisx->viewport);
    gSPClearGeometryMode(thisx->dlist++, G_SHADE | G_SHADING_SMOOTH | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD);
    gSPTexture(thisx->dlist++, 0, 0, 0, 0, G_OFF);
    gSPSetGeometryMode(thisx->dlist++, G_SHADE | G_SHADING_SMOOTH);
}

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

    osCreateViManager(OS_PRIORITY_VIMGR);
    osViSetMode(&osViModeTable[OS_VI_NTSC_HAN1]);

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
	    BASE_RES_X * 2, BASE_RES_Y * 2, G_MAXZ / 2, 0,
	    BASE_RES_X * 2, BASE_RES_Y * 2, G_MAXZ / 2, 0,
    };
}

void GfxCtx_GfxBegin(GfxCtx* thisx) {
    u16* cfb = gFramebuffer[thisx->framebufferIndex];

   thisx->dlist = thisx->glist[thisx->framebufferIndex]; 

    // clear framebuffer
    gSPSegment(thisx->dlist++, SEGMENT_CFB, cfb);
    gSPSegment(thisx->dlist++, SEGMENT_ZFB, gFramebuffer2);
    gSPSegment(thisx->dlist++, SEGMENT_CODE, __code_start);
    gSPDisplayList(thisx->dlist++, sRdpInit);
    GfxCtx_RspInit(thisx);
    gSPDisplayList(thisx->dlist++, sClearCFB);

    // initial persp/view
    gSPMatrix(thisx->dlist++, OS_K0_TO_PHYSICAL(&thisx->projection), G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
    gSPMatrix(thisx->dlist++, OS_K0_TO_PHYSICAL(&thisx->view), G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
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
