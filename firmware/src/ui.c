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
    

}
