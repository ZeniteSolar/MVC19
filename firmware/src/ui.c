#include "ui.h"

screen_t screen;
display_font_size_t font_selected;
uint8_t screen_toggle; 

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
    //_delay_ms(700);
    //display_test();
    font_selected = font_big;
}

/**
 * @brief Atualiza a tensao medida nas baterias
 */
void ui_update_main_battery_voltage(void)
{
	usart_send_string("update!");

    if (system_flags.no_message_from_MDE)
        display_send_string(DESCONNECTED_MESSAGE, COL1, LINE0, font_selected);
    else
        display_send_float((steeringbat_measurements.steeringbat_voltage / VSCALE_FLOAT), COL1, LINE0, font_selected);

#ifdef VERBOSE_ON_UI
    usart_send_uint16(steeringbat_measurements.steeringbat_voltage);
    usart_send_char('\n');
#endif

    if (system_flags.no_message_from_MSC19_1)
        display_send_string(DESCONNECTED_MESSAGE, COL1, LINE1, font_selected);
    else
        display_send_float((battery_voltage.main_cell_1 / VSCALE_FLOAT) , COL1, LINE1, font_selected);

#ifdef VERBOSE_ON_UI
    usart_send_uint16(battery_voltage.main_cell_1);
    usart_send_char('\t');
#endif

    if (system_flags.no_message_from_MSC19_2)
        display_send_string(DESCONNECTED_MESSAGE, COL1, LINE2, font_selected);
    else
        display_send_float((battery_voltage.main_cell_2 / VSCALE_FLOAT), COL1, LINE2, font_selected);

#ifdef VERBOSE_ON_UI
    usart_send_uint16(battery_voltage.main_cell_1);
    usart_send_char('\t');
#endif

    if (system_flags.no_message_from_MSC19_3)
        display_send_string(DESCONNECTED_MESSAGE, COL1, LINE3, font_selected);
    else
        display_send_float((battery_voltage.main_cell_3 / VSCALE_FLOAT), COL1, LINE3, font_selected);

#ifdef VERBOSE_ON_UI
    usart_send_uint16(battery_voltage.main_cell_1);
    usart_send_char('\t');
#endif
}

/**
 * @brief Atualiza a corrente medida nas baterias
 */
void ui_update_battery_current(void)
{
    // MSC19_4 -> Corrente de entrada
    // MSC19_5 -> Corrente de saída

    if (system_flags.no_message_from_MSC19_4)
        display_send_string(DESCONNECTED_MESSAGE, COL1, LINE1, font_selected);
    else
        display_send_float((battery_current.in / I_SCALE_FLOAT), COL1, LINE0, font_selected);
#ifdef VERBOSE_ON_UI
        usart_send_uint16(battery_current.in);
        usart_send_char('\t');
#endif
    // Pout = Vmain * Iout
    if (system_flags.no_message_from_MSC19_5) 
        display_send_string(DESCONNECTED_MESSAGE, COL1, LINE2, font_selected);
    else
        display_send_float((battery_current.out / I_SCALE_FLOAT), COL1, LINE1, font_selected);
#ifdef VERBOSE_ON_UI
        usart_send_uint16(battery_current.out);
        usart_send_char('\t');
#endif

    if (system_flags.no_message_from_MCC19_5 || system_flags.no_message_from_MCC19_6)
        display_send_string(DESCONNECTED_MESSAGE, COL1, LINE1, font_selected);
    else if 
        display_send_float((mcc[4].vi*mcc[4].ii/ I_SCALE_FLOAT), COL1, LINE2, font_selected);
        display_send_float((mcc[5].vi*mcc[5].ii/ I_SCALE_FLOAT), COL1, LINE3, font_selected);
#ifdef VERBOSE_ON_UI
        usart_send_uint16(mcc[5].vi*mcc[4].ii);
        usart_send_char('\t');
        usart_send_uint16(mcc[4].vi*mcc[5].ii);
        usart_send_char('\n');
}

/**
 * @brief
 */
void ui_update_rpm(void)
{
    if (system_flags.no_message_from_MT19)
        display_send_string(DESCONNECTED_MESSAGE, COL1, LINE0, font_selected);
    else
        display_send_uint16(boat_rpm, COL1, LINE0, font_selected);
}

void ui_update_mppt_measurements(void)
{
    if (system_flags.no_message_from_MCC19_1 || system_flags.no_message_from_MCC19_2 || system_flags.no_message_from_MCC19_3 || system_flags.no_message_from_MCC19_4)
        display_send_string(DESCONNECTED_MESSAGE, COL1, LINE1, font_selected);
    else if 
        display_send_float((mcc[0].vi*mcc[1].ii/ I_SCALE_FLOAT), COL1, LINE0, font_selected);
        display_send_float((mcc[1].vi*mcc[2].ii/ I_SCALE_FLOAT), COL1, LINE1, font_selected);
        display_send_float((mcc[2].vi*mcc[2].ii/ I_SCALE_FLOAT), COL1, LINE2, font_selected);
        display_send_float((mcc[3].vi*mcc[3].ii/ I_SCALE_FLOAT), COL1, LINE3, font_selected);
#ifdef VERBOSE_ON_UI
        usart_send_uint16(mcc[0].vi*mcc[0].ii);
        usart_send_char('\t');
        usart_send_uint16(mcc[1].vi*mcc[1].ii);
        usart_send_char('\t');
        usart_send_uint16(mcc[2].vi*mcc[2].ii);
        usart_send_char('\t');
        usart_send_uint16(mcc[3].vi*mcc[3].ii);
        usart_send_char('\n');
#endif
}

void ui_update(void)
{
	static uint8_t update = 0;
    switch (screen)
    {
    default:
    case VOLTAGE:
        ui_update_main_battery_voltage();
        ui_update_rpm();
        break;

    case CURRENT:
        ui_update_battery_current();
        break;

    case MPPT:
        ui_update_mppt_measurements();
        break;

    /*case CURRENT_SMALL:
        ui_update_battery_current();
        // ui_update_rpm();*/
        break;
    }

	if (++update >= 100){
		update = 0;
		display_send_string("|", COL3,LINE0,font_selected);
	}else {
		display_send_string("/", COL3,LINE0,font_selected);
	}
}

void ui_draw_layout(void)
{
    switch (screen)
    {
    default:
    case VOLTAGE:
        display_send_string("D:", COL0, LINE0, font_selected);
        display_send_string("1:", COL0, LINE1, font_selected);
        display_send_string("2:", COL0, LINE2, font_selected);
        display_send_string("3:", COL0, LINE3, font_selected);
        break;

    case CURRENT:
        display_send_string("I:", COL0, LINE0, font_selected);
        display_send_string("O:", COL0, LINE1, font_selected);
        display_send_string("6:", COL0, LINE2, font_selected);
        display_send_string("7:", COL0, LINE3, font_selected);
        break;

    case MPPT:
        display_send_string("1:", COL0, LINE0, font_selected);
        display_send_string("2:", COL0, LINE1, font_selected);
        display_send_string("3:", COL0, LINE2, font_selected);
        display_send_string("4:", COL0, LINE3, font_selected);
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

    if (screen_selected < LAST_SCREEN)
    {
        screen = screen_selected;
        display_clear();
        ui_draw_layout();

        if (screen == CURRENT_SMALL)
            font_selected = font_small;
        else
            font_selected = font_big;

#ifdef VERBOSE_ON_DISPLAY
        if (screen == VOLTAGE)
            usart_send_string("Voltage selected");
        else if (screen == CURRENT)
            usart_send_string("Current selected");
        else if (screen == CURRENT_SMALL)
            usart_send_string("Current_small selected");
#endif
    }
}
