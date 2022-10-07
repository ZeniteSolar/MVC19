#include "can_app.h"

uint16_t can_app_checks_without_mam_msg;
uint16_t can_app_checks_without_mic17_msg;
uint16_t can_app_checks_without_mcs19_msg;
uint16_t can_app_checks_without_msc19_1_msg;
uint16_t can_app_checks_without_msc19_2_msg;
uint16_t can_app_checks_without_msc19_3_msg;
uint16_t can_app_checks_without_msc19_4_msg;
uint16_t can_app_checks_without_msc19_5_msg;
uint16_t can_app_checks_without_mcc19[6];
uint16_t can_app_checks_without_mt19;
uint16_t can_app_send_state_clk_div;
uint16_t can_app_checks_without_mic17_msg;
uint16_t can_app_checks_without_mcs19_msg;
uint16_t can_app_checks_without_msc19_1_msg;
uint16_t can_app_checks_without_msc19_2_msg;
uint16_t can_app_checks_without_msc19_3_msg;
uint16_t can_app_checks_without_msc19_4_msg;
uint16_t can_app_checks_without_msc19_5_msg;
uint16_t can_app_checks_without_mcc19_1_msg;
uint16_t can_app_checks_without_mcc19_2_msg;
uint16_t can_app_checks_without_mcc19_3_msg;
uint16_t can_app_checks_without_mcc19_4_msg;
uint16_t can_app_checks_without_mde_msg;
uint16_t can_app_checks_without_mt19;
uint16_t can_app_checks_without_mde;
uint16_t can_app_send_state_clk_div;

/**
 * @brief Prints a can message via usart
 */
inline void can_app_print_msg(can_t *msg)
{
#ifdef USART_ON
    usart_send_string("ID: ");
    usart_send_uint16(msg->id);
    usart_send_string(". D: ");

    for (uint8_t i = 0; i < msg->length; i++)
    {
        usart_send_uint16(msg->data[i]);
        usart_send_char(' ');
    }

    usart_send_string(". ERR: ");
    can_error_register_t err = can_read_error_register();
    usart_send_uint16(err.rx);
    usart_send_char(' ');
    usart_send_uint16(err.tx);
    usart_send_char('\n');
#endif
}

/**
 * @brief Manages the canbus application protocol
 */
inline void can_app_task(void)
{
    check_can();

    if (can_app_send_state_clk_div++ >= CAN_APP_SEND_STATE_CLK_DIV)
    {
#ifdef USART_ON
        VERBOSE_MSG_CAN_APP(usart_send_string("state msg was sent.\n"));
#endif
        can_app_send_state();
        can_app_send_state_clk_div = 0;
    }
}

inline void can_app_send_state(void)
{
    can_t msg;
    msg.id = CAN_MSG_MAM19_STATE_ID;
    msg.length = CAN_MSG_GENERIC_STATE_LENGTH;
    msg.flags.rtr = 0;

    msg.data[CAN_MSG_GENERIC_STATE_SIGNATURE_BYTE] = CAN_SIGNATURE_SELF;
    msg.data[CAN_MSG_GENERIC_STATE_STATE_BYTE] = (uint8_t)state_machine;
    msg.data[CAN_MSG_GENERIC_STATE_ERROR_BYTE] = error_flags.all;

    can_send_message(&msg);
#ifdef VERBOSE_MSG_CAN_APP
    VERBOSE_MSG_CAN_APP(can_app_print_msg(&msg));
#endif
}

void can_app_extractor_msc19_1_state(can_t *msg)
{
    // if(msg->data[CAN_MSG_GENERIC_STATE_SIGNATURE_BYTE] == CAN_SIGNATURE_MSC19_1){
    //     if(msg->data[CAN_MSG_GENERIC_STATE_ERROR_BYTE]){
    //         //ERROR!!!
    //     }
    // }
}

void can_app_extractor_msc19_2_state(can_t *msg)
{
    // if(msg->data[CAN_MSG_GENERIC_STATE_SIGNATURE_BYTE] == CAN_SIGNATURE_MSC19_2){
    //     if(msg->data[CAN_MSG_GENERIC_STATE_ERROR_BYTE]){
    //         //ERROR!!!
    //     }
    // }
}

void can_app_extractor_msc19_3_state(can_t *msg)
{
    // if(msg->data[CAN_MSG_GENERIC_STATE_SIGNATURE_BYTE] == CAN_SIGNATURE_MSC19_3){
    //     if(msg->data[CAN_MSG_GENERIC_STATE_ERROR_BYTE]){
    //         //ERROR!!!
    //     }
    // }
}

void can_app_extractor_msc19_4_state(can_t *msg)
{
    //     if(msg->data[CAN_MSG_GENERIC_STATE_SIGNATURE_BYTE] == CAN_SIGNATURE_MSC19_4){
    //         if(msg->data[CAN_MSG_GENERIC_STATE_ERROR_BYTE]){
    //             //ERROR!!!
    //         }
    //     }
}

void can_app_extractor_msc19_5_state(can_t *msg)
{
    // if(msg->data[CAN_MSG_GENERIC_STATE_SIGNATURE_BYTE] == CAN_SIGNATURE_MSC19_5){
    //     if(msg->data[CAN_MSG_GENERIC_STATE_ERROR_BYTE]){
    //         //ERROR!!!
    //     }
    // }
}

void can_app_extractor_mccs(can_t *msg)
{
    uint8_t index = 0;
    switch (msg->data[CAN_MSG_GENERIC_STATE_SIGNATURE_BYTE])
    {
    case CAN_SIGNATURE_MCC19_1:
        system_flags.no_message_from_MCC19_1 = 0;
        index = 0;
        break;
    case CAN_SIGNATURE_MCC19_2:
        system_flags.no_message_from_MCC19_2 = 0;
        index = 1;
        break;
    case CAN_SIGNATURE_MCC19_3:
        system_flags.no_message_from_MCC19_3 = 0;
        index = 2;
        break;
    case CAN_SIGNATURE_MCC19_4:
        system_flags.no_message_from_MCC19_4 = 0;
        index = 3;
        break;
    case CAN_SIGNATURE_MCC19_5:
        system_flags.no_message_from_MCC19_5 = 0;
        index = 4;
        break;
    case CAN_SIGNATURE_MCC19_6:
        system_flags.no_message_from_MCC19_6 = 0;
        index = 5;
        break;
    default:
        return;
    }
    can_app_checks_without_mcc19[index] = 0;

        
    HIGH_LOW(mcc[index].ii,
        msg->data[CAN_MSG_MCC19_1_MEASUREMENTS_INPUT_CURRENT_H_BYTE],
        msg->data[CAN_MSG_MCC19_1_MEASUREMENTS_INPUT_CURRENT_L_BYTE]);

    HIGH_LOW(mcc[index].vi,
        msg->data[CAN_MSG_MCC19_1_MEASUREMENTS_INPUT_VOLTAGE_H_BYTE],
        msg->data[CAN_MSG_MCC19_1_MEASUREMENTS_INPUT_VOLTAGE_L_BYTE]);
}

void can_app_extractor_msc19_1_adc(can_t *msg)
{
    if (msg->data[CAN_MSG_GENERIC_STATE_SIGNATURE_BYTE] == CAN_SIGNATURE_MSC19_1)
    {
        system_flags.no_message_from_MSC19_1 = 0;
        can_app_checks_without_msc19_1_msg = 0;

        HIGH_LOW(battery_voltage.main_cell_1, msg->data[CAN_MSG_MSC19_1_ADC_AVG_H_BYTE], msg->data[CAN_MSG_MSC19_1_ADC_AVG_L_BYTE]);
    }
}

void can_app_extractor_msc19_2_adc(can_t *msg)
{
    if (msg->data[CAN_MSG_GENERIC_STATE_SIGNATURE_BYTE] == CAN_SIGNATURE_MSC19_2)
    {
        can_app_checks_without_msc19_2_msg = 0;
        system_flags.no_message_from_MSC19_2 = 0;

        HIGH_LOW(battery_voltage.main_cell_2, msg->data[CAN_MSG_MSC19_2_ADC_AVG_H_BYTE], msg->data[CAN_MSG_MSC19_2_ADC_AVG_L_BYTE]);
    }
}

void can_app_extractor_msc19_3_adc(can_t *msg)
{
    if (msg->data[CAN_MSG_GENERIC_STATE_SIGNATURE_BYTE] == CAN_SIGNATURE_MSC19_3)
    {
        can_app_checks_without_msc19_3_msg = 0;
        system_flags.no_message_from_MSC19_3 = 0;

        HIGH_LOW(battery_voltage.main_cell_3, msg->data[CAN_MSG_MSC19_3_ADC_AVG_H_BYTE], msg->data[CAN_MSG_MSC19_3_ADC_AVG_L_BYTE]);
    }
}

void can_app_extractor_msc19_4_adc(can_t *msg)
{
    if (msg->data[CAN_MSG_GENERIC_STATE_SIGNATURE_BYTE] == CAN_SIGNATURE_MSC19_4)
    {
        can_app_checks_without_msc19_4_msg = 0;
        system_flags.no_message_from_MSC19_4 = 0;

        HIGH_LOW(battery_current.in, msg->data[CAN_MSG_MSC19_4_ADC_AVG_H_BYTE], msg->data[CAN_MSG_MSC19_4_ADC_AVG_L_BYTE]);
    }
}

void can_app_extractor_msc19_5_adc(can_t *msg)
{
    if (msg->data[CAN_MSG_GENERIC_STATE_SIGNATURE_BYTE] == CAN_SIGNATURE_MSC19_5)
    {
        can_app_checks_without_msc19_5_msg = 0;
        system_flags.no_message_from_MSC19_5 = 0;

        HIGH_LOW(battery_current.out, msg->data[CAN_MSG_MSC19_5_ADC_AVG_H_BYTE], msg->data[CAN_MSG_MSC19_5_ADC_AVG_L_BYTE]);
    }
}

void can_app_extractor_mcs_state(can_t *msg)
{
    // if(msg->data[CAN_MSG_GENERIC_STATE_SIGNATURE_BYTE] == CAN_SIGNATURE_MCS19){
    //     if(msg->data[CAN_MSG_GENERIC_STATE_ERROR_BYTE] == 0xFF){
    //       system_flags.charge_failed = 1;
    //     }
    //     else if(msg->data[CAN_MSG_GENERIC_STATE_ERROR_BYTE] == 0x00)
    //     {
    //       system_flags.charge_failed = 0;
    //     }
    // }
}

void can_app_extractor_mt19_rpm(can_t *msg)
{
    if (msg->data[CAN_MSG_GENERIC_STATE_SIGNATURE_BYTE] == CAN_SIGNATURE_MT19)
    {
        can_app_checks_without_mt19 = 0;
        system_flags.no_message_from_MT19 = 0;
        HIGH_LOW(boat_rpm, msg->data[CAN_MSG_MT19_RPM_AVG_H_BYTE], msg->data[CAN_MSG_MT19_RPM_AVG_L_BYTE])
    }
}

void can_app_extractor_mt19_state(can_t *msg)
{
}

void can_app_extractor_mcc_1_measurements(can_t *msg)
{
    if (msg->data[CAN_MSG_GENERIC_STATE_SIGNATURE_BYTE] == CAN_SIGNATURE_MCC19_1)
    {
        can_app_checks_without_mcc19_1_msg = 0;
        system_flags.no_message_from_MCC19_1 = 0;
        //HIGH_LOW(boat_rpm, msg->data[CAN_MSG_MT19_RPM_AVG_H_BYTE], msg->data[CAN_MSG_MT19_RPM_AVG_L_BYTE])
                                                                                                                            
    }
}

/*void can_app_extractor_mcs_relay(can_t *msg)
{
    if (msg->data[CAN_MSG_GENERIC_STATE_SIGNATURE_BYTE] == CAN_SIGNATURE_MCS19)
    {
        if (msg->data[CAN_MSG_MCS19_START_STAGES_CHARGE_RELAY_BYTE] == 0xFF)
        {
            system_flags.cap_charging = 1;
        }
        else if (msg->data[CAN_MSG_MCS19_START_STAGES_CHARGE_RELAY_BYTE] == 0x00)
        {
            system_flags.cap_charging = 0;
        }

        if (msg->data[CAN_MSG_MCS19_START_STAGES_MAIN_RELAY_BYTE] == 0xFF)
        {
            system_flags.boat_on = 1;
        }
        else if (msg->data[CAN_MSG_MCS19_START_STAGES_MAIN_RELAY_BYTE] == 0x00)
        {
            system_flags.boat_on = 0;
        }
    }
}*/

void can_app_extractor_mde_state(can_t *msg)
{
    //
}

void can_app_extractor_mde_measurements(can_t *msg)
{
    if (msg->data[CAN_MSG_GENERIC_STATE_SIGNATURE_BYTE] == CAN_SIGNATURE_MDE22)
    {
        can_app_checks_without_mde = 0;
        system_flags.no_message_from_MDE = 0;
        HIGH_LOW(steeringbat_measurements.steeringbat_voltage, msg->data[CAN_MSG_MDE22_STEERINGBAT_MEASUREMENTS_BATVOLTAGE_H_BYTE], msg->data[CAN_MSG_MDE22_STEERINGBAT_MEASUREMENTS_BATVOLTAGE_L_BYTE]);
        HIGH_LOW(steeringbat_measurements.tail_position, msg->data[CAN_MSG_MDE22_STEERINGBAT_MEASUREMENTS_POSITION_H_BYTE], msg->data[CAN_MSG_MDE22_STEERINGBAT_MEASUREMENTS_POSITION_L_BYTE]);
        HIGH_LOW(steeringbat_measurements.steeringbat_current, msg->data[CAN_MSG_MDE22_STEERINGBAT_MEASUREMENTS_BATCURRENT_H_BYTE], msg->data[CAN_MSG_MDE22_STEERINGBAT_MEASUREMENTS_BATCURRENT_L_BYTE]);
    }
}

void can_app_extractor_mic19_pumps(can_t *msg)
{
    if (msg->data[CAN_MSG_GENERIC_STATE_SIGNATURE_BYTE] == CAN_MSG_MIC19_PUMPS_SIGNATURE_BYTE)
    {
        can_app_checks_without_mic17_msg = 0;   
        system_flags.no_message_from_MIC19 = 0;
        screen_toggle = CAN_MSG_MIC19_PUMPS_PUMPS_BYTE;     
    }

}


/**
 * @brief redirects a specific message extractor to a given message
 * @param *msg pointer to the message to be extracted
 */
inline void can_app_msg_extractors_switch(can_t *msg)
{

    if (msg->data[CAN_MSG_MCC19_1_MEASUREMENTS_ID] ||
        msg->data[CAN_MSG_MCC19_2_MEASUREMENTS_ID] ||
        msg->data[CAN_MSG_MCC19_3_MEASUREMENTS_ID] ||
        msg->data[CAN_MSG_MCC19_4_MEASUREMENTS_ID] ||
        msg->data[CAN_MSG_MCC19_5_MEASUREMENTS_ID] ||
        msg->data[CAN_MSG_MCC19_6_MEASUREMENTS_ID])
    {
        can_app_extractor_mccs(msg);
    }

    /*if (msg->data[CAN_MSG_GENERIC_STATE_SIGNATURE_BYTE] == CAN_SIGNATURE_MCS19)
    {
        // can_app_checks_without_mcs19_msg = 0;

        switch (msg->id)
        {
        case CAN_MSG_MCS19_STATE_ID:
#ifdef USART_ON
            VERBOSE_MSG_CAN_APP(usart_send_string(" got a state msg from MCS: "));
#endif
            VERBOSE_MSG_CAN_APP(can_app_print_msg(msg));
            can_app_extractor_mcs_state(msg);
            break;

        case CAN_MSG_MCS19_START_STAGES_ID:
#ifdef USART_ON
            VERBOSE_MSG_CAN_APP(usart_send_string(" got a relay msg from MCS: "));
#endif
            VERBOSE_MSG_CAN_APP(can_app_print_msg(msg));
            can_app_extractor_mcs_relay(msg);
            break;

        default:
#ifdef USART_ON
            VERBOSE_MSG_CAN_APP(usart_send_string(" got a unknown msg from MCS"));
#endif
            VERBOSE_MSG_CAN_APP(can_app_print_msg(msg));
            break;
        }
    } // CAN_SIGNATURE_MCS19*/

    if (msg->data[CAN_MSG_GENERIC_STATE_SIGNATURE_BYTE] == CAN_SIGNATURE_MSC19_1)
    {
        switch (msg->id)
        {
        case CAN_MSG_MSC19_1_STATE_ID:
#ifdef USART_ON
            VERBOSE_MSG_CAN_APP(usart_send_string(" got a state msg from MSC19_1: "));
#endif
            VERBOSE_MSG_CAN_APP(can_app_print_msg(msg));
            // can_app_extractor_msc19_1_state(msg);
            break;

        case CAN_MSG_MSC19_1_ADC_ID:
#ifdef USART_ON
            VERBOSE_MSG_CAN_APP(usart_send_string(" got a adc msg from MSC19_1: "));
#endif
            VERBOSE_MSG_CAN_APP(can_app_print_msg(msg));
            can_app_extractor_msc19_1_adc(msg);
            break;

        default:
#ifdef USART_ON
            VERBOSE_MSG_CAN_APP(usart_send_string(" got a unknown msg: "));
#endif
            VERBOSE_MSG_CAN_APP(can_app_print_msg(msg));
            break;
        }
    } // CAN_SIGNATURE_MSC19_1

    if (msg->data[CAN_MSG_GENERIC_STATE_SIGNATURE_BYTE] == CAN_SIGNATURE_MSC19_2)
    {
        switch (msg->id)
        {
        case CAN_MSG_MSC19_2_STATE_ID:
#ifdef USART_ON
            VERBOSE_MSG_CAN_APP(usart_send_string(" got a state msg from MSC19_2: "));
#endif
            VERBOSE_MSG_CAN_APP(can_app_print_msg(msg));
            // can_app_extractor_msc19_2_state(msg);
            break;

        case CAN_MSG_MSC19_2_ADC_ID:
#ifdef USART_ON
            VERBOSE_MSG_CAN_APP(usart_send_string(" got a adc msg from MSC19_2: "));
#endif
            VERBOSE_MSG_CAN_APP(can_app_print_msg(msg));
            can_app_extractor_msc19_2_adc(msg);
            break;

        default:
#ifdef USART_ON
            VERBOSE_MSG_CAN_APP(usart_send_string(" got a unknown msg: "));
#endif
            VERBOSE_MSG_CAN_APP(can_app_print_msg(msg));
            break;
        }
    } // CAN_SIGNATURE_MSC19_2

    if (msg->data[CAN_MSG_GENERIC_STATE_SIGNATURE_BYTE] == CAN_SIGNATURE_MSC19_3)
    {
        switch (msg->id)
        {
        case CAN_MSG_MSC19_3_STATE_ID:
#ifdef USART_ON
            VERBOSE_MSG_CAN_APP(usart_send_string(" got a state msg from MSC19_3: "));
#endif
            VERBOSE_MSG_CAN_APP(can_app_print_msg(msg));
            // can_app_extractor_msc19_3_state(msg);
            break;

        case CAN_MSG_MSC19_3_ADC_ID:
#ifdef USART_ON
            VERBOSE_MSG_CAN_APP(usart_send_string(" got a adc msg from MSC19_3"));
#endif
            VERBOSE_MSG_CAN_APP(can_app_print_msg(msg));
            can_app_extractor_msc19_3_adc(msg);
            break;

        default:
#ifdef USART_ON
            VERBOSE_MSG_CAN_APP(usart_send_string(" got a unknown msg from MSC19_3"));
#endif
            VERBOSE_MSG_CAN_APP(can_app_print_msg(msg));
            break;
        }
    } // CAN_SIGNATURE_MSC19_3

    if (msg->data[CAN_MSG_GENERIC_STATE_SIGNATURE_BYTE] == CAN_SIGNATURE_MSC19_4)
    {
        switch (msg->id)
        {
        case CAN_MSG_MSC19_4_STATE_ID:
#ifdef USART_ON
            VERBOSE_MSG_CAN_APP(usart_send_string(" got a state msg from MSC19_4: "));
#endif
            VERBOSE_MSG_CAN_APP(can_app_print_msg(msg));
            // can_app_extractor_msc19_4_state(msg);
            break;

        case CAN_MSG_MSC19_4_ADC_ID:
#ifdef USART_ON
            VERBOSE_MSG_CAN_APP(usart_send_string(" got a adc msg from MSC19_4"));
#endif
            VERBOSE_MSG_CAN_APP(can_app_print_msg(msg));
            can_app_extractor_msc19_4_adc(msg);
            break;

        default:
#ifdef USART_ON
            VERBOSE_MSG_CAN_APP(usart_send_string(" got a unknown msg from MSC19_4"));
#endif
            VERBOSE_MSG_CAN_APP(can_app_print_msg(msg));
            break;
        }
    } // CAN_SIGNATURE_MSC19_4

    if (msg->data[CAN_MSG_GENERIC_STATE_SIGNATURE_BYTE] == CAN_SIGNATURE_MSC19_5)
    {
        switch (msg->id)
        {
        case CAN_MSG_MSC19_5_STATE_ID:
#ifdef USART_ON
            VERBOSE_MSG_CAN_APP(usart_send_string(" got a state msg from MSC19_5: "));
#endif
            VERBOSE_MSG_CAN_APP(can_app_print_msg(msg));
            // can_app_extractor_msc19_5_state(msg);
            break;

        case CAN_MSG_MSC19_5_ADC_ID:
#ifdef USART_ON
            VERBOSE_MSG_CAN_APP(usart_send_string(" got a adc msg from MSC19_5"));
#endif
            VERBOSE_MSG_CAN_APP(can_app_print_msg(msg));
            can_app_extractor_msc19_5_adc(msg);
            break;

        default:
#ifdef USART_ON
            VERBOSE_MSG_CAN_APP(usart_send_string(" got a unknown msg from MSC19_5"));
#endif
            VERBOSE_MSG_CAN_APP(can_app_print_msg(msg));
            break;
        }
    } // CAN_SIGNATURE_MSC19_5

    if (msg->data[CAN_MSG_GENERIC_STATE_SIGNATURE_BYTE] == CAN_SIGNATURE_MT19)
    {
        switch (msg->id)
        {
        case CAN_MSG_MT19_STATE_ID:
#ifdef USART_ON
            VERBOSE_MSG_CAN_APP(usart_send_string(" got a state msg from MSC19_5: "));
#endif
            VERBOSE_MSG_CAN_APP(can_app_print_msg(msg));
            // can_app_extractor_mt19_state(msg);
            break;

        case CAN_MSG_MT19_RPM_ID:
#ifdef USART_ON
            VERBOSE_MSG_CAN_APP(usart_send_string(" got a adc msg from MSC19_5"));
#endif
            VERBOSE_MSG_CAN_APP(can_app_print_msg(msg));
            can_app_extractor_mt19_rpm(msg);
            break;

        default:
#ifdef USART_ON
            VERBOSE_MSG_CAN_APP(usart_send_string(" got a unknown msg from MSC19_5"));
#endif
            VERBOSE_MSG_CAN_APP(can_app_print_msg(msg));
            break;
        }
    } // CAN_SIGNATURE_MT19

    if (msg->data[CAN_MSG_GENERIC_STATE_SIGNATURE_BYTE] == CAN_SIGNATURE_MAM19)
    {
        switch (msg->id)
        {
        case CAN_MSG_MAM19_STATE_ID:
#ifdef USART_ON
            VERBOSE_MSG_CAN_APP(usart_send_string(" got a state msg from MAM19: "));
#endif
            VERBOSE_MSG_CAN_APP(can_app_print_msg(msg));
            // can_app_extractor_mam17_state(msg);
            error_flags.no_communication_with_mam = 0;

            break;

        case CAN_MSG_MAM19_MOTOR_ID:
#ifdef USART_ON
            VERBOSE_MSG_CAN_APP(usart_send_string(" got a motor msg from MAM19: "));
#endif
            VERBOSE_MSG_CAN_APP(can_app_print_msg(msg));
            error_flags.no_communication_with_mam = 0;
            break;

        default:
#ifdef USART_ON
            VERBOSE_MSG_CAN_APP(usart_send_string(" got a unknown msg from MAM19: "));
#endif
            VERBOSE_MSG_CAN_APP(can_app_print_msg(msg));
            break;
        }
    } // CAN_SIGNATURE_MAM19

    /* MCC19 */
    if (msg->data[CAN_MSG_GENERIC_STATE_SIGNATURE_BYTE] == CAN_SIGNATURE_MCC19_1)
    {
        if (msg->id == CAN_MSG_MCC19_1_MEASUREMENTS_ID)
        {
#ifdef USART_ON
            VERBOSE_MSG_CAN_APP(usart_send_string(" got an output voltage msg from MCC19_1: "));
#endif
            VERBOSE_MSG_CAN_APP(can_app_print_msg(msg));
            // error_flags.no_communication_with_mam = 0;
        }
    } // CAN_SIGNATURE_MCC19_1
    
    /* MDE22 */
    if (msg->data[CAN_MSG_GENERIC_STATE_SIGNATURE_BYTE] == CAN_SIGNATURE_MDE22)
    {
        switch (msg->id)
        {
        case CAN_MSG_MDE22_STATE_ID:
#ifdef USART_ON
            VERBOSE_MSG_CAN_APP(usart_send_string(" got a state msg from MDE22: "));
#endif
            VERBOSE_MSG_CAN_APP(can_app_print_msg(msg));
            // can_app_extractor_mam17_state(msg);
            error_flags.no_communication_with_mde = 0;

            break;
        
        case CAN_MSG_MDE22_STEERINGBAT_MEASUREMENTS_ID:
#ifdef USART_ON
            VERBOSE_MSG_CAN_APP(usart_send_string(" got measurements msg from MDE22: "));
#endif
            VERBOSE_MSG_CAN_APP(can_app_print_msg(msg));
            can_app_extractor_mde_measurements(msg);
            error_flags.no_communication_with_mde = 0;

            break;

        default:
#ifdef USART_ON
            VERBOSE_MSG_CAN_APP(usart_send_string(" got a unknown msg from MDE22: "));
#endif
            VERBOSE_MSG_CAN_APP(can_app_print_msg(msg));
            break;    
        }
    } // CAN_SIGNATURE_MDE22 

    /* MIC19 */
    if (msg->data[CAN_MSG_GENERIC_STATE_SIGNATURE_BYTE] == CAN_SIGNATURE_MIC19)
    {
        if (msg->id == CAN_MSG_MIC19_PUMPS_ID)
        {
#ifdef USART_ON
            VERBOSE_MSG_CAN_APP(usart_send_string(" got an output voltage msg from MCC19_1: "));
#endif
            VERBOSE_MSG_CAN_APP(can_app_print_msg(msg));
            can_app_extractor_mic19_pumps(msg);
            error_flags.no_communication_with_mic = 0;
        }
    } // CAN_SIGNATURE_MIC19
}

/**
 * @brief Manages to receive and extract specific messages from canbus
 */
inline void check_can(void)
{

    if (can_app_checks_without_mic17_msg++ >= CAN_APP_CHECKS_WITHOUT_MIC19_MSG)
    {
#ifdef USART_ON
        VERBOSE_MSG_CAN_APP(usart_send_string("too many cycles without MIC message.\n"));
#endif
        can_app_checks_without_mic17_msg = 0;
    }

    if (can_app_checks_without_msc19_1_msg++ >= CAN_APP_CHECKS_WITHOUT_MSC19_MSG)
    {
#ifdef USART_ON
        VERBOSE_MSG_CAN_APP(usart_send_string("too many cycles without MSC19_1 message.\n"));
#endif
        can_app_checks_without_msc19_1_msg = 0;
        system_flags.no_message_from_MSC19_1 = 1;
    }

    if (can_app_checks_without_msc19_2_msg++ >= CAN_APP_CHECKS_WITHOUT_MSC19_MSG)
    {
#ifdef USART_ON
        VERBOSE_MSG_CAN_APP(usart_send_string("too many cycles without MSC19_2 message.\n"));
#endif
        can_app_checks_without_msc19_2_msg = 0;
        system_flags.no_message_from_MSC19_2 = 1;
    }

    if (can_app_checks_without_msc19_3_msg++ >= CAN_APP_CHECKS_WITHOUT_MSC19_MSG)
    {
#ifdef USART_ON
        VERBOSE_MSG_CAN_APP(usart_send_string("too many cycles without MSC19_3 message.\n"));
#endif
        can_app_checks_without_msc19_3_msg = 0;
        system_flags.no_message_from_MSC19_3 = 1;
    }

    if (can_app_checks_without_msc19_4_msg++ >= CAN_APP_CHECKS_WITHOUT_MSC19_MSG)
    {
#ifdef USART_ON
        VERBOSE_MSG_CAN_APP(usart_send_string("too many cycles without MSC19_4 message.\n"));
#endif
        can_app_checks_without_msc19_4_msg = 0;
        system_flags.no_message_from_MSC19_4 = 1;
    }

    if (can_app_checks_without_msc19_5_msg++ >= CAN_APP_CHECKS_WITHOUT_MSC19_MSG)
    {
#ifdef USART_ON
        VERBOSE_MSG_CAN_APP(usart_send_string("too many cycles without MSC19_5 message.\n"));
#endif
        can_app_checks_without_msc19_5_msg = 0;
        system_flags.no_message_from_MSC19_5 = 1;
    }

    if (can_app_checks_without_mt19++ >= CAN_APP_CHECKS_WITHOUT_MT19_MSG)
    {
#ifdef USART_ON
        VERBOSE_MSG_CAN_APP(usart_send_string("too many cycles without MT19 message.\n"));
#endif
        can_app_checks_without_mt19 = 0;
        system_flags.no_message_from_MT19 = 1;
    }

    if (can_app_checks_without_mam_msg++ >= CAN_APP_CHECKS_WITHOUT_MAM_MSG)
    {
#ifdef USART_ON
        VERBOSE_MSG_CAN_APP(usart_send_string("too many cycles without MAM19 message.\n"));
#endif
        can_app_checks_without_mam_msg = 0;
        error_flags.no_communication_with_mam = 1;
    }

    if (can_app_checks_without_mde_msg++ >= CAN_APP_CHECKS_WITHOUT_MDE_MSG)
    {
#ifdef USART_ON
        VERBOSE_MSG_CAN_APP(usart_send_string("too many cycles without MDE22 message.\n"));
#endif
        can_app_checks_without_mde_msg = 0;
        error_flags.no_communication_with_mde = 1;
    }

    if (can_check_message())
    {
        can_t msg;
        if (can_get_message(&msg))
        {
            can_app_msg_extractors_switch(&msg);
        }
    }
}
