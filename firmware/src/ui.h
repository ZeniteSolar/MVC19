/**
 * @file ui.h
 *
 * @defgroup UI    UI Module
 *
 * @brief This module implements a simple UI
 *
 *  ________________
 * | BAT.  | CURR.  |
 * |________________|
 * |M:36.1V|I:042.2A|
 * |A:11.2V|O:100.2A|
 * |S:13.0V|        |
 * |________________|
 *
 */

#ifndef _UI_H_
#define _UI_H_

#include "conf.h"
#include "dbg_vrb.h"
#include "usart.h"
#include "display.h"

void ui_init(void);

void update_battery_voltage_main(const char *s);
void update_battery_voltage_auxiliary(const char *s);
void update_battery_voltage_security(const char *s);
void update_battery_current_input(const char *s);
void update_battery_current_output(const char *s);

#endif /* ifndef _UI_H_ */
