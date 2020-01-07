/**
 * @file ui.h
 *
 * @defgroup UI    UI Module
 *
 * @brief This module implements a simple UI
 *
 *  _________________
 * |  BAT.  |  CURR. |    <! DISPLAY 1
 * |_________________|
 * |M 43,22 |> 39,72 |
 * |A 12,66 |< 104,21|
 * |S:13,01 |        |
 * |_________________|
 *
 *  _________________
 * |  TEMP  |   RPM  |    <! DISPLAY 2
 * |_________________|
 * |T1 43,1 |  1200  |
 * |T2 25,7 |        |
 * |T3 39,0 |        |
 * |_________________|
 */

#ifndef _UI_H_
#define _UI_H_


#ifndef PRIMARY_DISPLAY
#undef UI_FONT_SMALL
#endif

#include "conf.h"
#include "dbg_vrb.h"
#include "usart.h"
#include "display.h"
#include <util/delay.h>
#include "machine.h"

void ui_init(void);
void ui_update_battery_voltage(void);
void ui_update_battery_current(void);
void ui_update_temperatures(void);
void ui_update_rpm(void);

// modules check
void ui_check_mam(void);

volatile uint8_t update_display;
volatile uint8_t ui_state;
volatile uint8_t display_freeze;
#endif /* ifndef _UI_H_ */
