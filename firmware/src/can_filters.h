/**
 * @file can_filters.h
 *
 * @defgroup CANAPP    Filters for can application
 *
 * @brief Filters for canbus application
 *
 */

#ifndef CAN_FILTERS_H
#define CAN_FILTERS_H

#include "conf.h"
#include "can_ids.h"

// -----------------------------------------------------------------------------
/** Set filters and masks.
 *
 * The filters are divided in two groups:
 *
 * Group 0: Filter 0 and 1 with corresponding mask 0.
 * Group 1: Filter 2, 3, 4 and 5 with corresponding mask 1.
 *
 * If a group mask is set to 0, the group will receive all messages.
 *
 * If you want to receive ONLY 11 bit identifiers, set your filters
 * and masks as follows:
 *
 *  uint8_t can_filter[] PROGMEM = {
 *      // Group 0
 *      MCP2515_FILTER(0),              // Filter 0
 *      MCP2515_FILTER(0),              // Filter 1
 *
 *      // Group 1
 *      MCP2515_FILTER(0),              // Filter 2
 *      MCP2515_FILTER(0),              // Filter 3
 *      MCP2515_FILTER(0),              // Filter 4
 *      MCP2515_FILTER(0),              // Filter 5
 *
 *      MCP2515_FILTER(0),              // Mask 0 (for group 0)
 *      MCP2515_FILTER(0),              // Mask 1 (for group 1)
 *  };
 *
 *
 * If you want to receive ONLY 29 bit identifiers, set your filters
 * and masks as follows:
 *
 * \code
 *  uint8_t can_filter[] PROGMEM = {
 *      // Group 0
 *      MCP2515_FILTER_EXTENDED(0),     // Filter 0
 *      MCP2515_FILTER_EXTENDED(0),     // Filter 1
 *
 *      // Group 1
 *      MCP2515_FILTER_EXTENDED(0),     // Filter 2
 *      MCP2515_FILTER_EXTENDED(0),     // Filter 3
 *      MCP2515_FILTER_EXTENDED(0),     // Filter 4
 *      MCP2515_FILTER_EXTENDED(0),     // Filter 5
 *
 *      MCP2515_FILTER_EXTENDED(0),     // Mask 0 (for group 0)
 *      MCP2515_FILTER_EXTENDED(0),     // Mask 1 (for group 1)
 *  };
 * \endcode
 *
 * If you want to receive both 11 and 29 bit identifiers, set your filters
 * and masks as follows:
 */


#if CAN_SIGNATURE_SELF == CAN_SIGNATURE_MVC19_1
const uint8_t can_filter[] PROGMEM =
{
    // Group 0
    MCP2515_FILTER(CAN_MSG_MSC19_1_ADC_ID),     // Filter 1
    MCP2515_FILTER(CAN_MSG_MSC19_1_STATE_ID),   // Filter 0
    
    // Group 1
    MCP2515_FILTER(CAN_MSG_MSC19_2_ADC_ID),     // Filter 3
    MCP2515_FILTER(CAN_MSG_MSC19_2_STATE_ID),   // Filter 2
    MCP2515_FILTER(CAN_MSG_MSC19_3_ADC_ID),     // Filter 5
    MCP2515_FILTER(CAN_MSG_MSC19_3_STATE_ID),   // Filter 4

    MCP2515_FILTER(0b11111111),             // Mask 0 (for group 0)
    MCP2515_FILTER(0b11111111),             // Mask 1 (for group 1)
};
#elif CAN_SIGNATURE_SELF == CAN_SIGNATURE_MVC19_2
const uint8_t can_filter[] PROGMEM =
{
    // Group 0
    MCP2515_FILTER(CAN_MSG_MSC19_4_ADC_ID),     // Filter 1
    MCP2515_FILTER(CAN_MSG_MSC19_4_STATE_ID),   // Filter 0
    
    MCP2515_FILTER(CAN_MSG_MSC19_5_ADC_ID),     // Filter 1
    MCP2515_FILTER(CAN_MSG_MSC19_5_STATE_ID),   // Filter 0
    
    // Group 1
    MCP2515_FILTER(CAN_MSG_MDE22_STEERINGBAT_MEASUREMENTS_ID),     // Filter 1
    MCP2515_FILTER(CAN_MSG_MDE22_STATE_ID),   // Filter 0

    MCP2515_FILTER(CAN_MSG_MIC19_PUMPS_ID),     // Filter 1

    MCP2515_FILTER(0b11111111),             // Mask 0 (for group 0)
    MCP2515_FILTER(0b11111111),             // Mask 1 (for group 1)
};
#endif

#endif /* ifndef CAN_FILTERS_H */
