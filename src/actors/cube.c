#include "actors/cube.h"
#include "usb/debug.h"

#define ACTOR_SEGMENT_OFFSET(__MEMBER__) ((SEGMENT_ACTOR << 24) | OFFSETOF(Actor_Cube, __MEMBER__))

Vtx test_cube_test_cube_mesh_vtx_cull[8] = {
	{-63, -62, -63, 0, -16, -16, 0x0, 0x0, 0x0, 0x0},
	{-63, -62, 63, 0, -16, -16, 0x0, 0x0, 0x0, 0x0},
	{-63, 63, 63, 0, -16, -16, 0x0, 0x0, 0x0, 0x0},
	{-63, 63, -63, 0, -16, -16, 0x0, 0x0, 0x0, 0x0},
	{63, -62, -63, 0, -16, -16, 0x0, 0x0, 0x0, 0x0},
	{63, -62, 63, 0, -16, -16, 0x0, 0x0, 0x0, 0x0},
	{63, 63, 63, 0, -16, -16, 0x0, 0x0, 0x0, 0x0},
	{63, 63, -63, 0, -16, -16, 0x0, 0x0, 0x0, 0x0},
};

Vtx test_cube_test_cube_mesh_vtx_0[19] = {
	{-63, 63, 63, 0, -16, 1008, 0xFF, 0xFF, 0xFF, 0xFF},
	{63, -62, 63, 0, 1008, 1008, 0xFF, 0xFF, 0xFF, 0xFF},
	{63, 63, 63, 0, 1008, -16, 0xFF, 0xFF, 0xFF, 0xFF},
	{-63, 63, -63, 0, -16, 1008, 0xFF, 0xFF, 0xFF, 0xFF},
	{-63, -62, 63, 0, 1008, 1008, 0xFF, 0xFF, 0xFF, 0xFF},
	{-63, 63, 63, 0, 1008, -16, 0xFF, 0xFF, 0xFF, 0xFF},
	{63, 63, -63, 0, -16, 1008, 0xFF, 0xFF, 0xFF, 0xFF},
	{63, -62, -63, 0, 1008, -16, 0xFF, 0xFF, 0xFF, 0xFF},
	{-63, -62, -63, 0, 1008, 1008, 0xFF, 0xFF, 0xFF, 0xFF},
	{-63, 63, -63, 0, 1008, -16, 0xFF, 0xFF, 0xFF, 0xFF},
	{63, 63, 63, 0, -16, 1008, 0xFF, 0xFF, 0xFF, 0xFF},
	{-63, 63, -63, 0, 1008, 1008, 0xFF, 0xFF, 0xFF, 0xFF},
	{-63, -62, -63, 0, -16, 1008, 0xFF, 0xFF, 0xFF, 0xFF},
	{-63, -62, 63, 0, 1008, -16, 0xFF, 0xFF, 0xFF, 0xFF},
	{63, -62, 63, 0, 1008, -16, 0xFF, 0xFF, 0xFF, 0xFF},
	{63, 63, 63, 0, 1008, 1008, 0xFF, 0xFF, 0xFF, 0xFF},
	{63, -62, -63, 0, 1008, 1008, 0xFF, 0xFF, 0xFF, 0xFF},
	{-63, -62, -63, 0, 1008, -16, 0xFF, 0xFF, 0xFF, 0xFF},
	{63, 63, -63, 0, 1008, 1008, 0xFF, 0xFF, 0xFF, 0xFF},
};

Gfx test_cube_test_cube_mesh_tri_0[] = {
	gsSPVertex(test_cube_test_cube_mesh_vtx_0 + 0, 19, 0),
	gsSP2Triangles(0, 1, 2, 0, 3, 4, 5, 0),
	gsSP2Triangles(6, 1, 7, 0, 6, 8, 9, 0),
	gsSP2Triangles(10, 11, 5, 0, 12, 1, 13, 0),
	gsSP2Triangles(0, 4, 14, 0, 3, 8, 13, 0),
	gsSP2Triangles(6, 15, 14, 0, 6, 16, 17, 0),
	gsSP2Triangles(10, 18, 9, 0, 12, 16, 14, 0),
	gsSPEndDisplayList(),
};

static Vec3 sSpawnPos = { 0, 0, 15.0f };

void Actor_Cube_Step(Actor_Cube* thisx, GlobalCtx* global) {
}

void Actor_Cube_Draw(Actor_Cube* thisx, GlobalCtx* global) {
    gSPDisplayList(global->gfxCtx.dlist++, test_cube_test_cube_mesh_tri_0);
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

