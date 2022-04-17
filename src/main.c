#include "main.h"
#include "GlobalCtx.h"
#include "Actor.h"
#include "actors/triangle.h"
#include "actors/cube.h"
#include "thread.h"
#include "framebuffer.h"
#include "usb/debug.h"

Actor* triActor = NULLPTR;

void entrypoint_main(void);
void IdleThreadFunction(GlobalCtx* global);
void MainThreadFunction(GlobalCtx* global);

void entrypoint_main(void) {
    // Initialize the hardware and software
    osInitialize();
    
    // Create the idle thread
    osCreateThread(&gThreadIdle, THREAD_ID_IDLE, IdleThreadFunction, gpGlobalCtx, gStackIdle + BOOT_STACKSIZE, THREAD_PRI_NONE);
    osStartThread(&gThreadIdle);
}

void IdleThreadFunction(GlobalCtx* global) {
    debug_initialize();
    debug_printf("Hello, World!\n");

    GlobalCtx_Construct(global);
    debug_printf("GlobalCtx_Construct OK\n");

    triActor = Actor_Spawn(global, &gActorInit_CubeActor);
    if (triActor) {
        triActor->scale = 0.1f;
        debug_printf("Spawned triangle\n");
    }
    else {
        debug_printf("Failed to spawn triangle\n");
    }

    // Create the main thread
    osCreateThread(&gThreadMain, THREAD_ID_MAIN, MainThreadFunction, global, gStackMain + MAIN_STACKSIZE, THREAD_PRI_DEFAULT);
    osStartThread(&gThreadMain);
    
    while(1);
}

void MainThreadFunction(GlobalCtx* global) {
    OSTime then;
    OSTime now;
    OSTime delta;
    u16 perspNorm;

    debug_printf("Build date %s %s\n", __DATE__, __TIME__);

    while (1) {
        //ControllerCtx_Step(&global->controllerCtx);
        Actor_StepAll(global);

        global->camera.pos.x = triActor->pos.x + (cosf(global->gfxCtx.time) * 15.0f);
        global->camera.pos.y = triActor->pos.y + (cosf(global->gfxCtx.time) * 15.0f);
        global->camera.pos.z = triActor->pos.z + (sinf(global->gfxCtx.time) * 15.0f);

        guPerspective(&global->gfxCtx.projection, &perspNorm, 83.0f, (f32)gScreenResX / (f32)gScreenResY, 10.0f, G_MAXZ, 1.0f);
        guLookAt(&global->gfxCtx.view,
                global->camera.pos.x, global->camera.pos.y, global->camera.pos.z,
                triActor->pos.x, triActor->pos.y, triActor->pos.z,
                0.0f, 1.0f, 0.0f);

        then = osGetTime();
        GfxCtx_GfxBegin(&global->gfxCtx);
        
        //ControllerCtx_Draw(&global->controllerCtx);
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
        debug_printf("time: %.3f\n", global->gfxCtx.time);
    }
}

