#include "main.h"
#include "GlobalCtx.h"
#include "Actor.h"
#include "actors/triangle.h"
#include "thread.h"
#include "framebuffer.h"
#include "linker_symbols.h"
#include "usb/debug.h"

Actor* triActor = NULLPTR;

void entrypoint_main(void);
void IdleThreadFunction(GlobalCtx* global);
void MainThreadFunction(GlobalCtx* global);

void entrypoint_main(void) {
    // Initialize the hardware and software
    osInitialize();
    
    // Create the idle thread
    osCreateThread(&gThreadIdle, THREAD_ID_IDLE, IdleThreadFunction, gpGlobalCtx, gStackIdle + BOOT_STACKSIZE, 0);
    osStartThread(&gThreadIdle);
}

void IdleThreadFunction(GlobalCtx* global) {
    debug_initialize();
    debug_printf("Hello, World!\n");

    GlobalCtx_Construct(global);
    debug_printf("GlobalCtx_Construct OK\n");

    triActor = Actor_Spawn(global, &gActorInit_TriangleActor);
    if (triActor) {
        debug_printf("Spawned triangle\n");
    }
    else {
        debug_printf("Failed to spawn triangle\n");
    }

    // Create the main thread
    osCreateThread(&gThreadMain, THREAD_ID_MAIN, MainThreadFunction, global, gStackMain + MAIN_STACKSIZE, 10);
    osStartThread(&gThreadMain);
    
    // Spin forever
    while(1);
}

Actor testActor;

static Vtx sTriangleVtx2[] = {
    {-64,  64, -5, 0, 0, 0, 0, 0xff, 0, 0xff},
    { 64,  64, -5, 0, 0, 0, 0, 0, 0, 0xff},
    { 64, -64, -5, 0, 0, 0, 0, 0, 0xff, 0xff},
    {-64, -64, -5, 0, 0, 0, 0xff, 0, 0, 0xff},
};

static Gfx sTriangleGfx2[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_OPA_SURF, G_RM_AA_OPA_SURF2),
    gsSPSetGeometryMode(G_SHADE | G_SHADING_SMOOTH),
    gsSPVertex(&(sTriangleVtx2[0]), 4, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSP1Triangle(0, 2, 3, 0),
    gsSPEndDisplayList()
};

void MainThreadFunction(GlobalCtx* global) {
    OSTime then;
    OSTime now;
    OSTime delta;
    u16 perspNorm;

    debug_printf("Build date %s %s\n", __DATE__, __TIME__);

    guMtxIdent(&testActor.mtxTranslate);
    guMtxIdent(&testActor.mtxRotate);
    guMtxIdent(&testActor.mtxScale);

    guScale(&testActor.mtxScale, 1.0f, 1.0f, 1.0f);
    guTranslate(&testActor.mtxTranslate, 0.0f, 0.0f, 10.0f);

    while (1) {
        Actor_StepAll(global);
        global->camera.pos.x = triActor->pos.x + (cosf(global->gfxCtx.time) * 15.0f);
        global->camera.pos.y = triActor->pos.y;
        global->camera.pos.z = triActor->pos.z + (sinf(global->gfxCtx.time) * 15.0f);

        guPerspective(&global->gfxCtx.projection, &perspNorm, 90.0f, BASE_RES_X / BASE_RES_Y, 0.1f, G_MAXZ, 1.0f);
        guLookAt(&global->gfxCtx.view,
                global->camera.pos.x, global->camera.pos.y, global->camera.pos.z,
                triActor->pos.x, triActor->pos.y, triActor->pos.z,
                0.0f, 1.0f, 0.0f);

        then = osGetTime();
        GfxCtx_GfxBegin(&global->gfxCtx);
        
        Actor_DrawAll(global);

        GfxCtx_GfxEnd(&global->gfxCtx);
        osWritebackDCache(global, sizeof(GlobalCtx));
        GfxCtx_GfxSendTask(&global->gfxCtx);
        GfxCtx_GfxRetrace(&global->gfxCtx);
        now = osGetTime();

        delta = now - then;
        global->gfxCtx.frames++;
        global->gfxCtx.frameclocks = delta;
        global->gfxCtx.frametime = (f64)OS_CYCLES_TO_USEC(delta) / 1000000.0f;
        global->gfxCtx.framerate = 1.0f / global->gfxCtx.frametime;
        global->gfxCtx.time += global->gfxCtx.frametime;
    }
}

