/**
 * @file ui.h
 *
 * @defgroup UI    UI Module
 *
 * @brief This module implements a simple UI
 *
 *  _________________
 * |  BAT.  |  CURR. |
 * |_________________|
 * |M 43218 |> 03972 |
 * |A 12657 |< 10421 |
 * |S:13014 |        |
 * |_________________|
 *
 */

#ifndef _UI_H_
#define _UI_H_

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

#endif /* ifndef _UI_H_ */
