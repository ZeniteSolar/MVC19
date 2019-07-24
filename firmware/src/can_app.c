#include "can_app.h"

/**
 * @brief Prints a can message via usart
 */
inline void can_app_print_msg(can_t *msg)
{
#ifdef USART_ON
    usart_send_string("ID: ");
    usart_send_uint16(msg->id);
    usart_send_string(". D: ");

    for(uint8_t i = 0; i < msg->length; i++){
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
 /*                                           
    if(can_app_send_state_clk_div++ >= CAN_APP_SEND_STATE_CLK_DIV){
#ifdef USART_ON
        VERBOSE_MSG_CAN_APP(usart_send_string("state msg was sent.\n"));
#endif
        can_app_send_state();
        can_app_send_state_clk_div = 0;
    }

*/  
}

inline void can_app_send_state(void)
{
    can_t msg;
    msg.id                                  = CAN_FILTER_MSG_MAM17_STATE;
    msg.length                              = CAN_LENGTH_MSG_STATE;
    msg.flags.rtr = 0;

    msg.data[CAN_SIGNATURE_BYTE]            = CAN_SIGNATURE_SELF;
    msg.data[CAN_STATE_MSG_STATE_BYTE]      = (uint8_t) state_machine;
    msg.data[CAN_STATE_MSG_ERROR_BYTE]      = error_flags.all;

    can_send_message(&msg);
#ifdef VERBOSE_MSG_CAN_APP
    VERBOSE_MSG_CAN_APP(can_app_print_msg(&msg));
#endif
}


void can_app_extractor_msc19_1_state(can_t *msg)
{
    if(msg->data[CAN_SIGNATURE_BYTE] == CAN_SIGNATURE_MSC19_1){
        if(msg->data[CAN_STATE_MSG_ERROR_BYTE]){
            //ERROR!!!
        }
    }

}

void can_app_extractor_msc19_2_state(can_t *msg)
{
    if(msg->data[CAN_SIGNATURE_BYTE] == CAN_SIGNATURE_MSC19_2){
        if(msg->data[CAN_STATE_MSG_ERROR_BYTE]){
            //ERROR!!!
        }
    }

}

void can_app_extractor_msc19_3_state(can_t *msg)
{
    if(msg->data[CAN_SIGNATURE_BYTE] == CAN_SIGNATURE_MSC19_3){
        if(msg->data[CAN_STATE_MSG_ERROR_BYTE]){
            //ERROR!!!
        }
    }
}

void can_app_extractor_msc19_4_state(can_t *msg)
{
    if(msg->data[CAN_SIGNATURE_BYTE] == CAN_SIGNATURE_MSC19_4){
        if(msg->data[CAN_STATE_MSG_ERROR_BYTE]){
            //ERROR!!!
        }
    }
}

void can_app_extractor_msc19_1_voltage(can_t *msg)
{
    if(msg->data[CAN_SIGNATURE_BYTE] == CAN_SIGNATURE_MSC19_1){
        #ifdef CAN_DEPENDENT
        voltmeter_errors.no_message_from_MSC19_1 = 0;
        can_app_checks_without_msc19_1_msg = 0;
        #endif
         
        HIGH_LOW(battery_voltage.main, msg->data[
            CAN_MSG_MSC19_ADC_AVG_BYTE_H], msg->data[
            CAN_MSG_MSC19_ADC_AVG_BYTE_L] ); 
    }
}

void can_app_extractor_msc19_2_voltage(can_t *msg)
{
    if(msg->data[CAN_SIGNATURE_BYTE] == CAN_SIGNATURE_MSC19_2){
        #ifdef CAN_DEPENDENT
        can_app_checks_without_msc19_2_msg = 0;
        voltmeter_errors.no_message_from_MSC19_2 = 0;
        #endif
         
        HIGH_LOW(battery_voltage.aux, msg->data[
            CAN_MSG_MSC19_ADC_AVG_BYTE_H], msg->data[
            CAN_MSG_MSC19_ADC_AVG_BYTE_L] );  
    }
}

void can_app_extractor_msc19_3_voltage(can_t *msg)
{
    if(msg->data[CAN_SIGNATURE_BYTE] == CAN_SIGNATURE_MSC19_3)
    {
        #ifdef CAN_DEPENDENT
        can_app_checks_without_msc19_3_msg = 0;
        voltmeter_errors.no_message_from_MSC19_3 = 0;
        #endif

        HIGH_LOW(battery_voltage.extra, msg->data[
            CAN_MSG_MSC19_ADC_AVG_BYTE_H], msg->data[
            CAN_MSG_MSC19_ADC_AVG_BYTE_L] );
    }
}

void can_app_extractor_msc19_4_data(can_t *msg)
{
    if(msg->data[CAN_SIGNATURE_BYTE] == CAN_SIGNATURE_MSC19_4)
    {
        #ifdef CAN_DEPENDENT
        can_app_checks_without_msc19_4_msg = 0;
        voltmeter_errors.no_message_from_MSC19_4 = 0;
        #endif

        HIGH_LOW(battery_current.in, msg->data[
            CAN_MSG_MSC19_ADC_AVG_BYTE_H], msg->data[
            CAN_MSG_MSC19_ADC_AVG_BYTE_L] );
    }
}

/**
 * @brief redirects a specific message extractor to a given message
 * @param *msg pointer to the message to be extracted
 */
inline void can_app_msg_extractors_switch(can_t *msg)
{
    VERBOSE_MSG_DISPLAY_TEST(usart_send_string("\nextractor"));
    
    if(msg->data[CAN_SIGNATURE_BYTE] == CAN_SIGNATURE_MSC19_1){
        switch(msg->id){
            case CAN_FILTER_MSG_MSC19_STATE:
            #ifdef USART_ON
                VERBOSE_MSG_CAN_APP(usart_send_string(" got a state msg from MSC19_1: "));
            #endif
                VERBOSE_MSG_CAN_APP(can_app_print_msg(msg));
                can_app_extractor_msc19_1_state(msg);
                break;

            case CAN_FILTER_MSG_MSC19_ADC:
            #ifdef USART_ON
                VERBOSE_MSG_CAN_APP(usart_send_string(" got a adc msg from MSC19_1: "));
            #endif
                VERBOSE_MSG_CAN_APP(can_app_print_msg(msg));
                can_app_extractor_msc19_1_voltage(msg);
                break;

            default:
            #ifdef USART_ON
                VERBOSE_MSG_CAN_APP(usart_send_string(" got a unknown msg: "));
            #endif
                VERBOSE_MSG_CAN_APP(can_app_print_msg(msg));
                break;
        }
    } // CAN_SIGNATURE_MSC19_1
    
    if(msg->data[CAN_SIGNATURE_BYTE] == CAN_SIGNATURE_MSC19_2){
        switch(msg->id){
            case CAN_FILTER_MSG_MSC19_STATE:
            #ifdef USART_ON
                VERBOSE_MSG_CAN_APP(usart_send_string(" got a state msg from MSC19_2: "));
            #endif
                VERBOSE_MSG_CAN_APP(can_app_print_msg(msg));
                can_app_extractor_msc19_2_state(msg);
                break;

            case CAN_FILTER_MSG_MSC19_ADC:
            #ifdef USART_ON
                VERBOSE_MSG_CAN_APP(usart_send_string(" got a adc msg from MSC19_2: "));
            #endif
                VERBOSE_MSG_CAN_APP(can_app_print_msg(msg));
                can_app_extractor_msc19_2_voltage(msg);
                break;

            default:
            #ifdef USART_ON
                VERBOSE_MSG_CAN_APP(usart_send_string(" got a unknown msg: "));
            #endif
                VERBOSE_MSG_CAN_APP(can_app_print_msg(msg));
                break;
        }
    } // CAN_SIGNATURE_MSC19_2

    if(msg->data[CAN_SIGNATURE_BYTE] == CAN_SIGNATURE_MSC19_3){
        switch(msg->id)
        {
            case CAN_FILTER_MSG_MSC19_STATE:
            #ifdef USART_ON
                VERBOSE_MSG_CAN_APP(usart_send_string(" got a state msg from MSC19_3: "));
            #endif
                VERBOSE_MSG_CAN_APP(can_app_print_msg(msg));
                can_app_extractor_msc19_3_state(msg);
                break;

            case CAN_FILTER_MSG_MSC19_ADC:
            #ifdef USART_ON
                VERBOSE_MSG_CAN_APP(usart_send_string(" got a adc msg from MSC19_3"));
            #endif
                VERBOSE_MSG_CAN_APP(can_app_print_msg(msg));
                can_app_extractor_msc19_3_voltage(msg);
                break;

            default:
            #ifdef USART_ON
                VERBOSE_MSG_CAN_APP(usart_send_string(" got a unknown msg from MSC19_3"));
            #endif
                VERBOSE_MSG_CAN_APP(can_app_print_msg(msg));
                break;
        }
    } // CAN_SIGNATURE_MSC19_3
        
    if(msg->data[CAN_SIGNATURE_BYTE] == CAN_SIGNATURE_MSC19_4){
        switch(msg->id)
        {
            case CAN_FILTER_MSG_MSC19_STATE:
            #ifdef USART_ON
                VERBOSE_MSG_CAN_APP(usart_send_string(" got a state msg from MSC19_4: "));
            #endif
                VERBOSE_MSG_CAN_APP(can_app_print_msg(msg));
                can_app_extractor_msc19_4_state(msg);
                break;

            case CAN_FILTER_MSG_MSC19_ADC:
            #ifdef USART_ON
                VERBOSE_MSG_CAN_APP(usart_send_string(" got a adc msg from MSC19_4"));
            #endif
                VERBOSE_MSG_CAN_APP(can_app_print_msg(msg));
                can_app_extractor_msc19_4_data(msg);
                break;

            default:
            #ifdef USART_ON
                VERBOSE_MSG_CAN_APP(usart_send_string(" got a unknown msg from MSC19_4"));
            #endif
                VERBOSE_MSG_CAN_APP(can_app_print_msg(msg));
                break;
        }
    } // CAN_SIGNATURE_MSC19_3
}

/**
 * @brief Manages to receive and extract specific messages from canbus
 */
inline void check_can(void)
{
    // If no messages is received from mic17 for
    // CAN_APP_CHECKS_WITHOUT_MIC17_MSG cycles, than it go to a specific error state. 
    //VERBOSE_MSG_CAN_APP(usart_send_string("checks: "));
    //VERBOSE_MSG_CAN_APP(usart_send_uint16(can_app_checks_without_mic17_msg));


#ifdef CAN_DEPENDENT
    if(can_app_checks_without_msc19_1_msg++ >= CAN_APP_CHECKS_WITHOUT_MSC19_MSG)
    {
#ifdef USART_ON
        VERBOSE_MSG_CAN_APP(usart_send_string("too many cycles without MSC19_1 message.\n"));
#endif
        can_app_checks_without_msc19_1_msg = 0;
        voltmeter_errors.no_message_from_MSC19_1 = 1;
    }

    if(can_app_checks_without_msc19_2_msg++ >= CAN_APP_CHECKS_WITHOUT_MSC19_MSG)
    {
#ifdef USART_ON
        VERBOSE_MSG_CAN_APP(usart_send_string("too many cycles without MSC19_2 message.\n"));
#endif
        can_app_checks_without_msc19_2_msg = 0;
        voltmeter_errors.no_message_from_MSC19_2 = 1;
    }

    if(can_app_checks_without_msc19_3_msg++ >= CAN_APP_CHECKS_WITHOUT_MSC19_MSG)
    {
#ifdef USART_ON
        VERBOSE_MSG_CAN_APP(usart_send_string("too many cycles without MSC19_3 message.\n"));
#endif
        can_app_checks_without_msc19_3_msg = 0;
        voltmeter_errors.no_message_from_MSC19_3 = 1;
    }
    
    if(can_app_checks_without_msc19_4_msg++ >= CAN_APP_CHECKS_WITHOUT_MSC19_MSG)
    {
#ifdef USART_ON
        VERBOSE_MSG_CAN_APP(usart_send_string("too many cycles without MSC19_4 message.\n"));
#endif
        can_app_checks_without_msc19_4_msg = 0;
        voltmeter_errors.no_message_from_MSC19_4 = 1;
    }

    if(can_app_checks_without_msc19_5_msg++ >= CAN_APP_CHECKS_WITHOUT_MSC19_MSG)
    {
#ifdef USART_ON
        VERBOSE_MSG_CAN_APP(usart_send_string("too many cycles without MSC19_5 message.\n"));
#endif
        can_app_checks_without_msc19_5_msg = 0;
        voltmeter_errors.no_message_from_MSC19_5 = 1;
    }

#endif

    if(can_check_message()){
    #ifdef LED_ON
       // cpl_led(LED1);
    #endif
        can_t msg;
        if(can_get_message(&msg)){
            can_app_msg_extractors_switch(&msg);
        }
    }
}
