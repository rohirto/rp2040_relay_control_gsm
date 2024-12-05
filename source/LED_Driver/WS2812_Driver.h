/**
 * @file WS2812_Driver.h
 * @author rohirto
 * @brief Header File for WS2812B LED 
 * @version 0.1
 * @date 2024-12-01
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "ws2812.pio.h"

#include "FreeRTOS.h"
#include "task.h"
}
#endif

class LED
{
    public:
    LED();
    void LED_On();
    void LED_Off();
    void LED_State(int r, int g, int b);
    void LED_Red();
    void LED_Green();
    void LED_Blue();
    private:
    // todo get free sm
    PIO pio;
    uint sm;
    uint offset;
    bool isInitialized;

};
