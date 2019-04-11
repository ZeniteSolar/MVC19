/**
 * @file display.h
 *
 * @defgroup DISPLAY DISPLAY Module
 *
 * @brief Simple display using pooling method
 *
 */

#ifndef DISPLAY_H
#define DISPLAY_H

#include <avr/io.h>
//#include "../lib/bit_utils.h"
#include "conf.h"
#include "../lib/DISPLAYS/SSD1306_AVR/ssd1306.h"
#include "../lib/DISPLAYS/SSD1306_AVR/fonts/Font_9_Mono.h"
//#include "../lib/DISPLAYS/SSD1306_AVR/fonts/Font_8_Myke.h"
//#include "../lib/DISPLAYS/SSD1306_AVR/fonts/Font_3_Picopixel.h"

#define normal_font _9_Mono

void display_init(void);
void display_clear(void);
void display_update(void);

void display_goto(uint8_t x, uint8_t y);
void display_gotox(uint8_t x);
void display_gotoy(uint8_t y);
void display_movex(int8_t x);
void display_movey(int8_t y);
void display_move(int8_t x, int8_t y);

void display_send_char(char data);
void display_send_string(const char *s);

void display_send_int8(int8_t num);
void display_send_uint8(uint8_t num);

void display_send_int16(int16_t num);
void display_send_uint16(uint16_t num);

void display_send_int32(int32_t num);
void display_send_uint32(uint32_t num);

void display_send_float(float num);
void display_send_double(double num);

#endif
