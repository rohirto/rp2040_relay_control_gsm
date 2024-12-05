/**
 * @file main.cpp
 * @author rohirto
 * @brief Main entry of Project
 * @version 0.1
 * @date 2024-12-01
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifdef __cplusplus
extern "C" {
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/clocks.h"
#include "hardware/pio.h"
#include "FreeRTOS.h"
#include "task.h"
#include "ws2812.pio.h"
}

#endif
#include <iostream>
#include <string>
#include "WS2812_Driver.h"
#include "ssd1306_i2c_driver.h"
#include "mario.h"
#include "yoda.h"
#include "rohirto.h"
#include "Opening_Screen.h"

void task1(void *pvParams);
void task2(void* pvParams);


int main() {
    stdio_init_all();
    set_sys_clock_khz(125000, true);  // 125 MHz, enable PLL to lock
   
    

    xTaskCreate(task1,   // Task function
                "Task1",         // Task name
                1000,            // Stack size in words
                NULL,            // Parameters passed to task (NULL here)
                1,               // Priority (1 is low priority)
                NULL);           // Task handle (NULL here)
    xTaskCreate(task2,   // Task function
                "Task2",         // Task name
                1000,            // Stack size in words
                NULL,            // Parameters passed to task (NULL here)
                1,               // Priority (1 is low priority)
                NULL); 
    
    vTaskStartScheduler();


    while (true) {
        
    }

    return 0;
}

void task1(void* pvParams)
{
    LED l;
    for(;;)
    {
        l.LED_On();
        vTaskDelay(pdMS_TO_TICKS(1000));
        l.LED_Red();
        vTaskDelay(pdMS_TO_TICKS(1000));
        l.LED_Blue();
        vTaskDelay(pdMS_TO_TICKS(1000));
        l.LED_Green();
        vTaskDelay(pdMS_TO_TICKS(1000));
        l.LED_Off();
        vTaskDelay(pdMS_TO_TICKS(1000));
        
    }
}

void task2(void* pvParams)
{
    SSD1306 Screen;
    Screen.set_all_pixels();
    vTaskDelay(pdMS_TO_TICKS(5000));
    Screen.go_back_to_previous_state();
    vTaskDelay(pdMS_TO_TICKS(5000));
    Screen.render_image(IMG_HEIGHT, IMG_WIDTH, (uint8_t *)rohirto_white_bg);
    vTaskDelay(pdMS_TO_TICKS(5000));
    Screen.write_string_array(text);
    vTaskDelay(pdMS_TO_TICKS(5000));
    std::string str = "Hello";
    Screen.write_string(str);

    for(;;)
    {
        
    }
}

