#include "ui.h"

/**
 * @brief inicializa o UI
 */
void ui_init(void)
{
    display_init();
    display_test();
}

/**
 * @brief Atualiza a tensao medida nas baterias
 */
void ui_update_battery_voltage(void)
{
    if(error_flags.no_message_from_MSC19_1)
        display_send_string("  N.C.  ", COL1, LINE1, font_small);
    else
        display_send_float((battery_voltage.main/100.f), COL1, LINE1, font_small);

    if(error_flags.no_message_from_MSC19_2)
        display_send_string("  N.C.  ", COL1, LINE2, font_small);
    else
        display_send_float((battery_voltage.aux/100.f), COL1, LINE2, font_small);

    if(error_flags.no_message_from_MSC19_3)
        display_send_string("  N.C.  ", COL1, LINE3, font_small);
    else
        display_send_float((battery_voltage.extra/100.f), COL1, LINE3, font_small);
}

/**
 * @brief Atualiza a corrente medida nas baterias
 */
void ui_update_battery_current(void)
{
    if(error_flags.no_message_from_MSC19_4)
        display_send_string("  N.C.  ", COL3, LINE1, font_small);
    else
        display_send_float((battery_current.in/100.f), COL3, LINE1, font_small);

    if(error_flags.no_message_from_MSC19_5)
        display_send_string("  N.C.  ", COL3, LINE2, font_small);
    else
        display_send_float((battery_current.out/100.f), COL3, LINE2, font_small);
}

/**
 * @brief
 */
void ui_update_temperatures()
{
    
}

/**
 * @brief
 */
void ui_update_rpm(void)
{
    if(error_flags.no_message_from_MT19)
        display_send_string("  N.C.  ", COL3, LINE3, font_small);
    else
        display_send_uint16(control.rpm, COL3, LINE3, font_small);
}
