#ifndef CONTROLLERCTX_H
#define CONTROLLERCTX_H

#include "common.h"

enum {
    BUTTON_FLAG_PRESSED = (1 << 0),
    BUTTON_FLAG_RELEASED = (1 << 1)
};

enum {
    BUTTON_STATE_UP = 0,
    BUTTON_STATE_DOWN
};

enum {
    BUTTONS_CR = 0,
    BUTTONS_CL,
    BUTTONS_CD,
    BUTTONS_CU,
    BUTTONS_RT,
    BUTTONS_LT,
    BUTTONS_UNUSED0,
    BUTTONS_UNUSED1,
    BUTTONS_DR,
    BUTTONS_DL,
    BUTTONS_DD,
    BUTTONS_DU,
    BUTTONS_ST,
    BUTTONS_Z,
    BUTTONS_B,
    BUTTONS_A,
    BUTTONS_COUNT
};

typedef struct {
#pragma pack(1)
    struct {
        u8 state : 1;
        u8 flag : 2;
        u8 unused : 5;
    };
#pragma pack()
    OSTime time;
    f32 timef;
} Button;

typedef union {
    Button buttons[BUTTONS_COUNT];
    struct {
        Button cr;
        Button cl;
        Button cd;
        Button cu;
        Button rt;
        Button lt;
        Button unused0;
        Button unused1;
        Button dr;
        Button dl;
        Button dd;
        Button du;
        Button st;
        Button z;
        Button b;
        Button a;
    };
    u8 jx;
    u8 jy;
    float jxf;
    float jyf;
} Controller;

typedef struct {
    OSContStatus status[4];
    OSContPad data[4];
    Controller controllers[4];
    OSMesgQueue serialMessageQ;
    OSMesgQueue controllerMessageQ;
    OSMesg serialMsgBuf;
    OSMesg controllerMsgBuf;
} ControllerCtx;

extern void ControllerCtx_Construct(ControllerCtx* thisx);
extern void ControllerCtx_Draw(ControllerCtx* thisx);
extern void ControllerCtx_Step(ControllerCtx* thisx);

#endif

