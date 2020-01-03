#include "ui.h"

/**
 * @brief inicializa o UI
 */
void ui_init(void)
{
    display_init();
    display_test();
    _delay_ms(500);
    display_clear();
    _delay_ms(100);
#ifdef PRIMARY_DISPLAY
    display_send_string("Display 1", 0, 0, font_small);
#else
    display_send_string("Display 2", 0, 0, font_small);
#endif
    _delay_ms(500);

    update_display = 1;
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
void ui_update_temperatures(void)
{
    display_send_string("  ----  ", COL1, LINE1, font_small);
    display_send_string("  ----  ", COL1, LINE2, font_small);
    display_send_string("  ----  ", COL1, LINE3, font_small);
}

/**
 * @brief
 */
void ui_update_rpm(void)
{
    if(error_flags.no_message_from_MT19)
        display_send_string("  N.C.  ", COL3, LINE1, font_small);
    else
        display_send_uint16(boat_rpm, COL3, LINE1, font_small);
}
