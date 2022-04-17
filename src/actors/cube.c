#include "actors/cube.h"
#include "usb/debug.h"

#define ACTOR_SEGMENT_OFFSET(__MEMBER__) ((SEGMENT_ACTOR << 24) | OFFSETOF(Actor_Cube, __MEMBER__))

Vtx test_cube_test_cube_mesh_vtx_cull[8] = {
	{-83, -80, -75, 0, -16, -16, 0x0, 0x0, 0x0, 0x0},
	{-83, -80, 75, 0, -16, -16, 0x0, 0x0, 0x0, 0x0},
	{-83, 72, 75, 0, -16, -16, 0x0, 0x0, 0x0, 0x0},
	{-83, 72, -75, 0, -16, -16, 0x0, 0x0, 0x0, 0x0},
	{78, -80, -75, 0, -16, -16, 0x0, 0x0, 0x0, 0x0},
	{78, -80, 75, 0, -16, -16, 0x0, 0x0, 0x0, 0x0},
	{78, 72, 75, 0, -16, -16, 0x0, 0x0, 0x0, 0x0},
	{78, 72, -75, 0, -16, -16, 0x0, 0x0, 0x0, 0x0},
};

Vtx test_cube_test_cube_mesh_vtx_0[14] = {
	{-83, -80, -75, 0, 624, 1008, 0xFF, 0xB, 0x0, 0xFF},
	{-83, 72, 75, 0, 368, 752, 0x1A, 0x0, 0xFF, 0xFF},
	{-83, 72, -75, 0, 368, 1008, 0xF5, 0xA, 0x1, 0xF5},
	{-83, -80, 75, 0, 624, 752, 0x1A, 0x3, 0xFF, 0xFF},
	{78, 72, 75, 0, 368, 496, 0x4, 0x4, 0x4, 0x4},
	{78, -80, 75, 0, 624, 496, 0x0, 0x0, 0x0, 0x0},
	{78, 72, -75, 0, 368, 240, 0xB, 0xAA, 0x2, 0xAA},
	{78, -80, -75, 0, 624, 240, 0x11, 0xFF, 0x0, 0xFF},
	{-83, -80, 75, 0, 880, 496, 0x1A, 0x3, 0xFF, 0xFF},
	{-83, -80, -75, 0, 880, 240, 0xFF, 0xB, 0x0, 0xFF},
	{-83, 72, -75, 0, 368, -16, 0xF5, 0xA, 0x1, 0xF5},
	{-83, -80, -75, 0, 624, -16, 0xFF, 0xB, 0x0, 0xFF},
	{-83, 72, -75, 0, 112, 240, 0xF5, 0xA, 0x1, 0xF5},
	{-83, 72, 75, 0, 112, 496, 0x1A, 0x0, 0xFF, 0xFF},
};

Gfx test_cube_test_cube_mesh_tri_0[] = {
	gsSPVertex(test_cube_test_cube_mesh_vtx_0 + 0, 14, 0),
	gsSP2Triangles(0, 1, 2, 0, 0, 3, 1, 0),
	gsSP2Triangles(3, 4, 1, 0, 3, 5, 4, 0),
	gsSP2Triangles(5, 6, 4, 0, 5, 7, 6, 0),
	gsSP2Triangles(8, 7, 5, 0, 8, 9, 7, 0),
	gsSP2Triangles(7, 10, 6, 0, 7, 11, 10, 0),
	gsSP2Triangles(4, 12, 13, 0, 4, 6, 12, 0),
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

