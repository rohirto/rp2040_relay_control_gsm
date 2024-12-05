/**
 * @file ssd1306_i2c_driver.h
 * @author rohirto
 * @brief I2C Display Header File
 * @version 0.1
 * @date 2024-12-01
 * 
 * @copyright Copyright (c) 2024
 * 
 *  Example code to talk to an SSD1306-based OLED display

   The SSD1306 is an OLED/PLED driver chip, capable of driving displays up to
   128x64 pixels.

   NOTE: Ensure the device is capable of being driven at 3.3v NOT 5v. The Pico
   GPIO (and therefore I2C) cannot be used at 5v.

   You will need to use a level shifter on the I2C lines if you want to run the
   board at 5v.

   Connections on Raspberry Pi Pico board, other boards may vary.

   GPIO PICO_DEFAULT_I2C_SDA_PIN (on Pico this is GP4 (pin 6)) -> SDA on display
   board
   GPIO PICO_DEFAULT_I2C_SCL_PIN (on Pico this is GP5 (pin 7)) -> SCL on
   display board
   3.3v (pin 36) -> VCC on display board
   GND (pin 38)  -> GND on display board
 * 
 */

#pragma once

#ifdef __cplusplus
extern "C"{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "hardware/i2c.h"
//#include "raspberry26x32.h"
#include "ssd1306_font.h"

#include "FreeRTOS.h"
#include "task.h"
}
#endif

#include <iostream>
#include <string>
#include <vector>
#include "ssd1306_private.h"

class SSD1306
{
    public:
    SSD1306();
    void set_all_pixels();
    void go_back_to_previous_state();
    void clear_all_pixels();
    void render_image(int image_height, int image_width, uint8_t* imag_buf);
    void write_string(const std::string& str);
    void write_string_array(const std::vector<std::string>& text);

    private:
    void SSD1306_init();
    void SSD1306_send_cmd_list(uint8_t *buf, int num);
    void SSD1306_send_cmd(uint8_t cmd);
    void render(); 
    void SSD1306_scroll(bool on);

    struct render_area 
    {
        uint8_t start_col;
        uint8_t end_col;
        uint8_t start_page;
        uint8_t end_page;

        int buflen;
    };

    render_area frame_area;
    uint8_t buf[SSD1306_BUF_LEN];

};