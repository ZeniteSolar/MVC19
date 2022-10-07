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
 * |S 13,01 |        |
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

#include "conf.h"
#include "dbg_vrb.h"
#include "usart.h"
#include "display.h"
#include <util/delay.h>
#include "machine.h"

#ifndef DESCONNECTED_MESSAGE
#define DESCONNECTED_MESSAGE		"  N.C.  "
#endif

typedef enum screen
{
    VOLTAGE,
    CURRENT,
    MPPT,
    CURRENT_SMALL,
    LAST_SCREEN,
}screen_t;

extern screen_t screen;
extern display_font_size_t font_selected;
extern uint8_t screen_toggle; 

void ui_init(void);

void ui_update_main_battery_voltage(void);
void ui_update_auxiliary_battery_voltage(void);
void ui_update_battery_current(void);
void ui_update_mppt_measurements(void);
void ui_update_rpm(void);

void ui_draw_layout(void);

void ui_select_screen(screen_t screen);
void ui_update(void);

#endif /* ifndef _UI_H_ */
