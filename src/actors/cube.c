#include "actors/cube.h"
#include "usb/debug.h"

#define ACTOR_SEGMENT_OFFSET(__MEMBER__) ((SEGMENT_ACTOR << 24) | OFFSETOF(Actor_Cube, __MEMBER__))

Vtx test_cube_test_cube_mesh_vtx_cull[8] = {
	{-626, -626, -626, 0, -16, -16, 0x0, 0x0, 0x0, 0x0},
	{-626, -626, 626, 0, -16, -16, 0x0, 0x0, 0x0, 0x0},
	{-626, 626, 626, 0, -16, -16, 0x0, 0x0, 0x0, 0x0},
	{-626, 626, -626, 0, -16, -16, 0x0, 0x0, 0x0, 0x0},
	{626, -626, -626, 0, -16, -16, 0x0, 0x0, 0x0, 0x0},
	{626, -626, 626, 0, -16, -16, 0x0, 0x0, 0x0, 0x0},
	{626, 626, 626, 0, -16, -16, 0x0, 0x0, 0x0, 0x0},
	{626, 626, -626, 0, -16, -16, 0x0, 0x0, 0x0, 0x0},
};

Vtx test_cube_test_cube_mesh_vtx_0[34] = {
	{-626, 626, 626, 0, -16, 1008, 0x0, 0x0, 0x7F, 0xFF},
	{626, -626, 626, 0, 1008, 1008, 0x0, 0x0, 0x7F, 0xFF},
	{626, 626, 626, 0, 1008, -16, 0x0, 0x0, 0x7F, 0xFF},
	{-626, 626, -626, 0, -16, 1008, 0x81, 0x0, 0x0, 0xFF},
	{-626, -626, 626, 0, 1008, 1008, 0x81, 0x0, 0x0, 0xFF},
	{-626, 626, 626, 0, 1008, -16, 0x81, 0x0, 0x0, 0xFF},
	{626, 626, -626, 0, -16, 1008, 0x7F, 0x0, 0x0, 0xFF},
	{626, -626, 626, 0, 1008, 1008, 0x7F, 0x0, 0x0, 0xFF},
	{626, -626, -626, 0, 1008, -16, 0x7F, 0x0, 0x0, 0xFF},
	{626, 626, -626, 0, -16, 1008, 0x0, 0x0, 0x81, 0xFF},
	{-626, -626, -626, 0, 1008, 1008, 0x0, 0x0, 0x81, 0xFF},
	{-626, 626, -626, 0, 1008, -16, 0x0, 0x0, 0x81, 0xFF},
	{626, 626, 626, 0, -16, 1008, 0x0, 0x7F, 0x0, 0xFF},
	{-626, 626, -626, 0, 1008, 1008, 0x0, 0x7F, 0x0, 0xFF},
	{-626, 626, 626, 0, 1008, -16, 0x0, 0x7F, 0x0, 0xFF},
	{-626, -626, -626, 0, -16, 1008, 0x0, 0x81, 0x0, 0xFF},
	{626, -626, 626, 0, 1008, 1008, 0x0, 0x81, 0x0, 0xFF},
	{-626, -626, 626, 0, 1008, -16, 0x0, 0x81, 0x0, 0xFF},
	{-626, 626, 626, 0, -16, 1008, 0x0, 0x0, 0x7F, 0xFF},
	{-626, -626, 626, 0, 1008, 1008, 0x0, 0x0, 0x7F, 0xFF},
	{626, -626, 626, 0, 1008, -16, 0x0, 0x0, 0x7F, 0xFF},
	{-626, -626, -626, 0, 1008, 1008, 0x81, 0x0, 0x0, 0xFF},
	{-626, -626, 626, 0, 1008, -16, 0x81, 0x0, 0x0, 0xFF},
	{626, 626, -626, 0, -16, 1008, 0x7F, 0x0, 0x0, 0xFF},
	{626, 626, 626, 0, 1008, 1008, 0x7F, 0x0, 0x0, 0xFF},
	{626, -626, 626, 0, 1008, -16, 0x7F, 0x0, 0x0, 0xFF},
	{626, 626, -626, 0, -16, 1008, 0x0, 0x0, 0x81, 0xFF},
	{626, -626, -626, 0, 1008, 1008, 0x0, 0x0, 0x81, 0xFF},
	{-626, -626, -626, 0, 1008, -16, 0x0, 0x0, 0x81, 0xFF},
	{626, 626, -626, 0, 1008, 1008, 0x0, 0x7F, 0x0, 0xFF},
	{-626, 626, -626, 0, 1008, -16, 0x0, 0x7F, 0x0, 0xFF},
	{-626, -626, -626, 0, -16, 1008, 0x0, 0x81, 0x0, 0xFF},
	{626, -626, -626, 0, 1008, 1008, 0x0, 0x81, 0x0, 0xFF},
	{626, -626, 626, 0, 1008, -16, 0x0, 0x81, 0x0, 0xFF},
};

Gfx test_cube_test_cube_mesh_tri_0[] = {
	gsSPVertex(test_cube_test_cube_mesh_vtx_0 + 0, 31, 0),
	gsSP2Triangles(0, 1, 2, 0, 3, 4, 5, 0),
	gsSP2Triangles(6, 7, 8, 0, 9, 10, 11, 0),
	gsSP2Triangles(12, 13, 14, 0, 15, 16, 17, 0),
	gsSP2Triangles(18, 19, 20, 0, 3, 21, 22, 0),
	gsSP2Triangles(23, 24, 25, 0, 26, 27, 28, 0),
	gsSP1Triangle(12, 29, 30, 0),
	gsSPVertex(test_cube_test_cube_mesh_vtx_0 + 31, 3, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSPEndDisplayList(),
};

Gfx mat_test_cube_test[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, 1, COMBINED, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED),
	gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
	gsSPSetOtherMode(G_SETOTHERMODE_H, 4, 20, G_AD_NOISE | G_TC_FILT | G_TF_BILERP | G_TL_TILE | G_TD_CLAMP | G_TP_PERSP | G_CYC_2CYCLE | G_CD_ENABLE | G_PM_NPRIMITIVE),
	gsSPSetOtherMode(G_SETOTHERMODE_L, 0, 32, G_AC_NONE | G_ZS_PIXEL | G_RM_FOG_SHADE_A | G_RM_AA_ZB_OPA_SURF2),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsDPSetPrimColor(0, 0, 254, 254, 254, 255),
	gsSPEndDisplayList(),
};

Gfx test_cube_test_cube_mesh[] = {
	gsSPClearGeometryMode(G_LIGHTING),
	gsSPVertex(test_cube_test_cube_mesh_vtx_cull + 0, 8, 0),
	gsSPCullDisplayList(0, 7),
	gsSPDisplayList(mat_test_cube_test),
	gsSPDisplayList(test_cube_test_cube_mesh_tri_0),
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPClearGeometryMode(G_TEXTURE_GEN),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 0),
	gsSPEndDisplayList(),
};


static Vec3 sSpawnPos = { 0, 0, 15.0f };

void Actor_Cube_Step(Actor_Cube* thisx, GlobalCtx* global) {
}

void Actor_Cube_Draw(Actor_Cube* thisx, GlobalCtx* global) {
    gSPDisplayList(global->gfxCtx.dlist++, test_cube_test_cube_mesh);
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

