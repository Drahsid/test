#include "actors/cube.h"
#include "usb/debug.h"

#define ACTOR_SEGMENT_OFFSET(__MEMBER__) ((SEGMENT_ACTOR << 24) | OFFSETOF(Actor_Cube, __MEMBER__))

Gfx fast64_room_0_entry_0_opaque[] = {
	gsSPDisplayList(fast64_dl_test_cube_mesh_layer_Opaque),
	gsSPEndDisplayList(),
};

Vtx fast64_dl_test_cube_mesh_layer_Opaque_vtx_cull[8] = {
	{-63, -183, 63, 0, -16, -16, 0x0, 0x0, 0x0, 0x0},
	{-63, -57, 63, 0, -16, -16, 0x0, 0x0, 0x0, 0x0},
	{-63, -57, -63, 0, -16, -16, 0x0, 0x0, 0x0, 0x0},
	{-63, -183, -63, 0, -16, -16, 0x0, 0x0, 0x0, 0x0},
	{63, -183, 63, 0, -16, -16, 0x0, 0x0, 0x0, 0x0},
	{63, -57, 63, 0, -16, -16, 0x0, 0x0, 0x0, 0x0},
	{63, -57, -63, 0, -16, -16, 0x0, 0x0, 0x0, 0x0},
	{63, -183, -63, 0, -16, -16, 0x0, 0x0, 0x0, 0x0},
};

Vtx fast64_dl_test_cube_mesh_layer_Opaque_vtx_0[31] = {
	{-63, -57, 63, 0, -16, 1008, 0x0, 0x0, 0x7F, 0xFF},
	{63, -183, 63, 0, 1008, 1008, 0x0, 0x0, 0x7F, 0xFF},
	{63, -57, 63, 0, 1008, -16, 0x0, 0x0, 0x7F, 0xFF},
	{-63, -57, -63, 0, -16, 1008, 0x81, 0x0, 0x0, 0xFF},
	{-63, -183, 63, 0, 1008, 1008, 0x81, 0x0, 0x0, 0xFF},
	{-63, -57, 63, 0, 1008, -16, 0x81, 0x0, 0x0, 0xFF},
	{63, -57, -63, 0, -16, 1008, 0x7F, 0x0, 0x0, 0xFF},
	{63, -183, 63, 0, 1008, 1008, 0x7F, 0x0, 0x0, 0xFF},
	{63, -183, -63, 0, 1008, -16, 0x7F, 0x0, 0x0, 0xFF},
	{63, -57, -63, 0, -16, 1008, 0x0, 0x0, 0x81, 0xFF},
	{-63, -183, -63, 0, 1008, 1008, 0x0, 0x0, 0x81, 0xFF},
	{-63, -57, -63, 0, 1008, -16, 0x0, 0x0, 0x81, 0xFF},
	{63, -57, 63, 0, -16, 1008, 0x0, 0x7F, 0x0, 0xFF},
	{-63, -57, -63, 0, 1008, 1008, 0x0, 0x7F, 0x0, 0xFF},
	{-63, -57, 63, 0, 1008, -16, 0x0, 0x7F, 0x0, 0xFF},
	{-63, -183, -63, 0, -16, 1008, 0x0, 0x81, 0x0, 0xFF},
	{63, -183, 63, 0, 1008, 1008, 0x0, 0x81, 0x0, 0xFF},
	{-63, -183, 63, 0, 1008, -16, 0x0, 0x81, 0x0, 0xFF},
	{-63, -57, 63, 0, -16, 1008, 0x0, 0x0, 0x7F, 0xFF},
	{-63, -183, 63, 0, 1008, 1008, 0x0, 0x0, 0x7F, 0xFF},
	{63, -183, 63, 0, 1008, -16, 0x0, 0x0, 0x7F, 0xFF},
	{-63, -183, -63, 0, 1008, 1008, 0x81, 0x0, 0x0, 0xFF},
	{-63, -183, 63, 0, 1008, -16, 0x81, 0x0, 0x0, 0xFF},
	{63, -57, 63, 0, 1008, 1008, 0x7F, 0x0, 0x0, 0xFF},
	{63, -183, 63, 0, 1008, -16, 0x7F, 0x0, 0x0, 0xFF},
	{63, -183, -63, 0, 1008, 1008, 0x0, 0x0, 0x81, 0xFF},
	{-63, -183, -63, 0, 1008, -16, 0x0, 0x0, 0x81, 0xFF},
	{63, -57, -63, 0, 1008, 1008, 0x0, 0x7F, 0x0, 0xFF},
	{-63, -57, -63, 0, 1008, -16, 0x0, 0x7F, 0x0, 0xFF},
	{63, -183, -63, 0, 1008, 1008, 0x0, 0x81, 0x0, 0xFF},
	{63, -183, 63, 0, 1008, -16, 0x0, 0x81, 0x0, 0xFF},
};

Gfx fast64_dl_test_cube_mesh_layer_Opaque_tri_0[] = {
	gsSPVertex(fast64_dl_test_cube_mesh_layer_Opaque_vtx_0 + 0, 31, 0),
	gsSP2Triangles(0, 1, 2, 0, 3, 4, 5, 0),
	gsSP2Triangles(6, 7, 8, 0, 9, 10, 11, 0),
	gsSP2Triangles(12, 13, 14, 0, 15, 16, 17, 0),
	gsSP2Triangles(18, 19, 20, 0, 3, 21, 22, 0),
	gsSP2Triangles(6, 23, 24, 0, 9, 25, 26, 0),
	gsSP2Triangles(12, 27, 28, 0, 15, 29, 30, 0),
	gsSPEndDisplayList(),
};

Gfx mat_fast64_dl_test_layerOpaque[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, 1, COMBINED, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED),
	gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
	gsSPSetOtherMode(G_SETOTHERMODE_H, 4, 20, G_AD_NOISE | G_TC_FILT | G_TF_BILERP | G_TL_TILE | G_TD_CLAMP | G_TP_PERSP | G_CYC_2CYCLE | G_CD_ENABLE | G_PM_NPRIMITIVE),
	gsSPSetOtherMode(G_SETOTHERMODE_L, 0, 32, G_AC_NONE | G_ZS_PIXEL | G_RM_FOG_SHADE_A | G_RM_AA_ZB_OPA_SURF2),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsDPSetPrimColor(0, 0, 254, 254, 254, 255),
	gsSPEndDisplayList(),
};

Gfx fast64_dl_test_cube_mesh_layer_Opaque[] = {
	gsSPClearGeometryMode(G_LIGHTING),
	gsSPVertex(fast64_dl_test_cube_mesh_layer_Opaque_vtx_cull + 0, 8, 0),
	gsSPCullDisplayList(0, 7),
	gsSPDisplayList(mat_fast64_dl_test_layerOpaque),
	gsSPDisplayList(fast64_dl_test_cube_mesh_layer_Opaque_tri_0),
	gsSPEndDisplayList(),
};




static Vec3 sSpawnPos = { 0, 0, 15.0f };

void Actor_Cube_Step(Actor_Cube* thisx, GlobalCtx* global) {
}

void Actor_Cube_Draw(Actor_Cube* thisx, GlobalCtx* global) {
    gSPDisplayList(global->gfxCtx.dlist++, fast64_room_0_entry_0_opaque);
}

void Actor_Cube_Construct(Actor_Cube* thisx, GlobalCtx* global) {
    Actor_SetPosition(thisx, &sSpawnPos);
}

void Actor_Cube_Deconstruct(Actor_Cube* thisx, GlobalCtx* global) {
}

ActorInit gActorInit_CubeActor = {
    .step = Actor_Cube_Step,
    .draw = Actor_Cube_Draw,
    .ctor = Actor_Cube_Construct,
    .dtor = Actor_Cube_Deconstruct,
    .size = sizeof(Actor_Cube)
};

