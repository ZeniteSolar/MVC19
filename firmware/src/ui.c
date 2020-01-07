#include "ui.h"

/**
 * @brief inicializa o UI
 */
void ui_init(void)
{
    display_init();
#ifdef PRIMARY_DISPLAY
    display_send_string("Display 1", 0, 0, font_small);
#else
    display_send_string("Display 2", 0, 0, font_small);
#endif
    _delay_ms(700);
    display_test();
    update_display = 1;
}

/**
 * @brief Atualiza a tensao medida nas baterias
 */
void ui_update_battery_voltage(void)
{
#ifdef UI_FONT_SMALL
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
#else
    if(error_flags.no_message_from_MSC19_1)
        display_send_string("  N.C.  ", COL1, LINE1, font_big);
    else
        display_send_float((battery_voltage.main/100.f), COL1, LINE1, font_big);

    if(error_flags.no_message_from_MSC19_2)
        display_send_string("  N.C.  ", COL1, LINE2, font_big);
    else
        display_send_float((battery_voltage.aux/100.f), COL1, LINE2, font_big);

    if(error_flags.no_message_from_MSC19_3)
        display_send_string("  N.C.  ", COL1, LINE3, font_big);
    else
        display_send_float((battery_voltage.extra/100.f), COL1, LINE3, font_big);
#endif  /* UI_FONT_SMALL */
}

/**
 * @brief Atualiza a corrente medida nas baterias
 */
void ui_update_battery_current(void)
{
#ifdef PRIMARY_DISPLAY
    if(error_flags.no_message_from_MSC19_4)
        display_send_string("  N.C.  ", COL3, LINE1, font_small);
    else
        display_send_float((battery_current.in/100.f), COL3, LINE1, font_small);

    if(error_flags.no_message_from_MSC19_5)
        display_send_string("  N.C.  ", COL3, LINE2, font_small);
    else
        display_send_float((battery_current.out/100.f), COL3, LINE2, font_small);

#else
    if(error_flags.no_message_from_MSC19_4)
        display_send_string("  N.C.  ", COL1, LINE1, font_small);
    else
        display_send_float((battery_current.in/100.f), COL1, LINE1, font_small);

    if(error_flags.no_message_from_MSC19_5)
        display_send_string("  N.C.  ", COL1, LINE2, font_small);
    else
        display_send_float((battery_current.out/100.f), COL1, LINE2, font_small);
#endif /* UI_FONT_SMALL */
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
        display_send_string("  N.C.  ", COL1, LINE3, font_small);
    else
        display_send_uint16(boat_rpm, COL1, LINE3, font_small);
}

void ui_check_mam(void)
{
#ifdef UI_ENABLE_MODULES_FAILURE_MESSAGE
    static uint8_t ui_mam_clk_div, display_warning_msg;

    if(error_flags.no_communication_with_mam)
    {
        display_warning_msg = 1;
        if(ui_mam_clk_div == 0)
        {
            display_send_string("MAM", 12, 1, font_big);
            display_send_string("FAIL", 12, 4, font_big);
        }
        if(ui_mam_clk_div == 50)
        {
            display_send_string("     ", 12, 1, font_big);
            display_send_string("     ", 12, 4, font_big);
        }
        if(ui_mam_clk_div++ == 100)
          ui_mam_clk_div = 0;
    }
    else
    {
        if(display_warning_msg)
        {
            display_warning_msg = 0;
            display_send_string("     ", 12, 1, font_big);
            display_send_string("     ", 12, 4, font_big);
            ui_mam_clk_div = 0;
        }
    }

#endif /* UI_ENABLE_MODULES_FAILURE_MESSAGE */
}
