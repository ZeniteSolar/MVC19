#include "ui.h"

/**
 * @brief inicializa o UI
 */
void ui_init(void)
{
    display_init();
    test_display();

    ui_clear();
    ui_draw_layout();
    ui_update();
}

void ui_clear(void)
{
    display_clear();
}

void ui_update(void)
{
    display_update();
}

void ui_draw_layout(void)
{
    display_layout();
}

void ui_update_battery_voltage_main(uint16_t num)
{
    display_send_uint16(num, col2, line2);
}

void ui_update_battery_voltage_auxiliary(uint16_t num)
{
    display_send_uint16(num, col2, line3);
}

void ui_update_battery_voltage_extra(uint16_t num)
{
    display_send_uint16(num, col2, line4);
}

void ui_update_battery_current_input(uint16_t num)
{
    display_send_uint16(num, col4, line2);
}

void ui_update_battery_current_output(uint16_t num)
{
    display_send_uint16(num, col4, line3);
}

void ui_update_no_communication_from_battery_main()
{
    display_send_string(" N.C.", col2, line2);
}

void ui_update_no_communication_from_battery_auxiliary()
{
    display_send_string(" N.C.", col2, line3);
}

void ui_update_no_communication_from_battery_extra()
{
    display_send_string(" N.C.", col2, line4);
}

void ui_update_no_communication_from_current_input()
{
    display_send_string(" N.C.", col4, line2);
}

void ui_update_no_communication_from_current_output()
{
    display_send_string(" N.C.", col4, line3);
}

void ui_cap_charging()
{
    display_clear();
    display_send_string("  CAP ", col2, line3);
    display_send_string("CHARGING", col2, line4);
    display_update();
}

void ui_boat_on()
{
    display_clear();
    display_send_string("   BOAT ON!", col2, line2);
    display_update();
    _delay_ms(500);
    LCD_Fill(1);
    display_update();
    display_layout();
    display_update();
}

void ui_boat_off()
{
    display_clear();
    display_send_string("   BOAT OFF!", col2, line2);
    display_update();
    _delay_ms(250);
}

void ui_no_communication_with_mic()
{
  display_clear();
  display_send_string("No communication", col1, line2);
  display_send_string("   with MIC!", col2, line3);
  display_update();
}
