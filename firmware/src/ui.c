#include "ui.h"

/**
 * @brief inicializa o UI
 */
void ui_init(void)
{
    display_init();
#if CAN_SIGNATURE_SELF == CAN_SIGNATURE_MVC19_1
    display_send_string("Display 1", 0, 0, font_big);
#elif CAN_SIGNATURE_SELF == CAN_SIGNATURE_MVC19_2
    display_send_string("Display 2", 0, 0, font_big);
#endif
    _delay_ms(700);
    display_test();
    font_selected = font_big;
}

/**
 * @brief Atualiza a tensao medida nas baterias
 */
void ui_update_main_battery_voltage(void)
{
    static uint8_t i;

    if(system_flags.no_message_from_MSC19_1 || system_flags.no_message_from_MSC19_2 || system_flags.no_message_from_MSC19_3)
    {
        display_send_string(DESCONNECTED_MESSAGE, COL1, LINE1, font_selected);
    }
    else
    {
	if(undervoltage.main_bank)
	{
	    i++;
	    if(i < 4)
        	display_send_float((battery_voltage.main_bank/VSCALE_FLOAT), COL1, LINE1, font_selected);
	    else if(i == 4)
		display_send_string(("BAT. LOW"), COL1, LINE1, font_selected);
	    else if(i == 8)
		i = 0;
	}
	else			
            display_send_float((battery_voltage.main_bank/VSCALE_FLOAT), COL1, LINE1, font_selected);
}


/**
 * @brief Atualiza a corrente medida nas baterias
 */
void ui_update_battery_current(void)
{
    if(system_flags.no_message_from_MSC19_4)
        display_send_string(DESCONNECTED_MESSAGE, COL1, LINE1, font_selected);
    else
        display_send_float((battery_current.in/VSCALE_FLOAT), COL1, LINE1, font_selected);

    if(system_flags.no_message_from_MSC19_5)
        display_send_string(DESCONNECTED_MESSAGE, COL1, LINE2, font_selected);
    else
        display_send_float((battery_current.out/VSCALE_FLOAT), COL1, LINE2, font_selected);
}

/**
 * @brief
 */
void ui_update_rpm(void)
{
    if(system_flags.no_message_from_MT19)
        display_send_string(DESCONNECTED_MESSAGE, COL1, LINE3, font_selected);
    else
        display_send_uint16(boat_rpm, COL1, LINE3, font_selected);
}

void ui_update(void)
{
    switch(screen)
    {
        default:
        case VOLTAGE:
            ui_update_main_battery_voltage();
            break;

        case CURRENT:
            ui_update_battery_current();
            ui_update_rpm();
            break;

        case CURRENT_SMALL:
            ui_update_battery_current();
            ui_update_rpm();
            break;
    }
}

void ui_check_modules_failure(void)
{
   
}

void ui_draw_layout(void)
{
    switch(screen)
    {
        default:
        case VOLTAGE:
            display_send_string("-VOLTAGES-", COL0, LINE0, font_big);
            display_send_string("M:", COL0, LINE1, font_selected);
            display_send_string("A:", COL0, LINE2, font_selected);
            display_send_string("E:", COL0, LINE3, font_selected);
            break;

        case CURRENT:
            display_send_string("-CURRENTS-", COL0, LINE0, font_big);
            display_send_string(">:", COL0, LINE1, font_selected);
            display_send_string("<:", COL0, LINE2, font_selected);
            display_send_string("T:", COL0, LINE3, font_selected);
            break;

        case CURRENT_SMALL:
            display_send_string("-CURRENTS-", COL0, LINE0, font_small);
            display_send_string(">:", COL0, LINE1, font_small);
            display_send_string("<:", COL0, LINE2, font_small);
            display_send_string("T:", COL0, LINE3, font_small);
	    display_send_string("A:", COL2, LINE1, font_small);
	    display_send_string("E:", COL2, LINE2, font_small);
            break;
    }
}

void ui_select_screen(screen_t screen_selected)
{   
    #ifdef VERBOSE_ON_DISPLAY
    usart_send_string("\nui_select_screen: ");
    #endif

    if(screen_selected < LAST_SCREEN)
    {
        screen = screen_selected;
        display_clear();
        ui_draw_layout();

        if(screen == CURRENT_SMALL)
            font_selected = font_small;
        else
            font_selected = font_big;

    #ifdef VERBOSE_ON_DISPLAY
        if(screen == VOLTAGE)               usart_send_string("Voltage selected");
        else if(screen == CURRENT)          usart_send_string("Current selected");
        else if(screen == CURRENT_SMALL)    usart_send_string("Current_small selected");
    #endif
    }

}
