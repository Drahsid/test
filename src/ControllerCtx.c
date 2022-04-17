#include "ControllerCtx.h"

void ControllerCtx_Construct(ControllerCtx* thisx) {
    u8 index = 0;
    u8 pattern = 0;

    memset_u32(thisx, 0, sizeof(ControllerCtx));

    osCreateMesgQueue(&thisx->serialMessageQ, &thisx->serialMsgBuf, 1);
    osSetEventMesg(OS_EVENT_SI, &thisx->serialMessageQ, 1);

    osContInit(&thisx->serialMessageQ, &pattern, &thisx->status);

    osCreateMesgQueue(&thisx->controllerMessageQ, &thisx->controllerMsgBuf, 1);
    osSetEventMesg(OS_EVENT_SI, &thisx->controllerMessageQ, 0);

    osContStartReadData(&thisx->controllerMessageQ); // start spinning
}

void ControllerCtx_Draw(ControllerCtx* thisx) {
    osContStartReadData(&thisx->controllerMessageQ);
}

void ControllerCtx_Step(ControllerCtx* thisx) {
    u32 qndex;
    u32 index;
    u32 mask;
    u32 state;

    osRecvMesg(&thisx->controllerMessageQ, NULL, OS_MESG_BLOCK);
    osContGetReadData(thisx->data);

    for (qndex = 0; qndex < 4; qndex++) {
        for (index = 0; index < BUTTONS_COUNT; index++) {
            mask = 1 << index;
            state = thisx->data[qndex].button & mask;
            if (state) {
                if (thisx->controllers[qndex].buttons[index].state) {
                    thisx->controllers[qndex].buttons[index].flag &= ~BUTTON_FLAG_PRESSED;
                }
                else {
                    thisx->controllers[qndex].buttons[index].state = 1;
                    thisx->controllers[qndex].buttons[index].flag |= BUTTON_FLAG_PRESSED;
                }
            }
            else {
                if (thisx->controllers[qndex].buttons[index].state) {
                    thisx->controllers[qndex].buttons[index].state = 0;
                    thisx->controllers[qndex].buttons[index].flag |= BUTTON_FLAG_RELEASED;
                }
                else {
                    thisx->controllers[qndex].buttons[index].flag &= ~BUTTON_FLAG_PRESSED;
                }
            }
        }
    }
}

