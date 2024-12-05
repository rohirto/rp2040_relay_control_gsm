/**
 * @file WS2812_Driver.cpp
 * @author rohirto
 * @brief WS2812 Driver Module
 * @version 0.1
 * @date 2024-12-01
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "WS2812_Driver.h"

//Private Defines
#define WS2812_PIN 16
// Check the pin is compatible with the platform
#if WS2812_PIN >= NUM_BANK0_GPIOS
#error Attempting to use a pin>=32 on a platform that does not support it
#endif
#define IS_RGBW false
#define NUM_PIXELS 1

static inline void put_pixel(PIO pio, uint sm, uint32_t pixel_grb) {
    pio_sm_put_blocking(pio, sm, pixel_grb << 8u);
}

static inline uint32_t urgb_u32(uint8_t r, uint8_t g, uint8_t b) {
    return
            ((uint32_t) (r) << 8) |
            ((uint32_t) (g) << 16) |
            (uint32_t) (b);
}

static inline uint32_t urgbw_u32(uint8_t r, uint8_t g, uint8_t b, uint8_t w) {
    return
            ((uint32_t) (r) << 8) |
            ((uint32_t) (g) << 16) |
            ((uint32_t) (w) << 24) |
            (uint32_t) (b);
}

LED::LED()
{

    // This will find a free pio and state machine for our program and load it for us
    // We use pio_claim_free_sm_and_add_program_for_gpio_range (for_gpio_range variant)
    // so we will get a PIO instance suitable for addressing gpios >= 32 if needed and supported by the hardware
    bool success = pio_claim_free_sm_and_add_program_for_gpio_range(&ws2812_program, &pio, &sm, &offset, WS2812_PIN, 1, true);
    configASSERT(success);
    ws2812_program_init(pio, sm, offset, WS2812_PIN, 800000, IS_RGBW);

    isInitialized = true;
}

void LED::LED_On()
{
    put_pixel(pio, sm, urgb_u32(255, 255, 255)); // Full brightness white
}

void LED::LED_Off()
{
    put_pixel(pio, sm, urgb_u32(0, 0, 0)); // Black/off
}

void LED::LED_State(int r, int g, int b)
{
    put_pixel(pio, sm, urgb_u32(r, g, b)); 
}

void LED::LED_Red()
{
    put_pixel(pio, sm, urgb_u32(255, 0, 0)); // Red LED
}


void LED::LED_Green()
{
    put_pixel(pio, sm, urgb_u32(0, 255, 0)); // Green LED
}

void LED::LED_Blue()
{
     put_pixel(pio, sm, urgb_u32(0, 0, 255)); // Green LED
}