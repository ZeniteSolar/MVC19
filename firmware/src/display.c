#include "display.h"

/**
 * @brief starts the display.
 */
void display_init()
{
    SSD1306_Init();

}

/**
 * @brief test the display
 */
void test_display()
{
    
}

/**
 * @brief sends a char
 * @param data will be sent
 */
void display_send_char(char data)
{

}

/**
 * @brief sends a char array
 * The strings are limited in 255 chars and MUST terminate with '\0'.
 */
void display_send_string(const char *s)
{
    uint8_t i = 0;  
    while(s[i] != '\0') display_send_char(s[i++]);
}


/**
 * @brief
 */
void display_goto(uint8_t x, uint8_t y)
{

}

/**
 * @brief
 */
void display_gotox(uint8_t x)
{

}

/**
 * @brief
 */
void display_gotoy(uint8_t y)
{

}

/**
 * @brief
 */
void display_movex(int8_t x)
{

}

/**
 * @brief
 */
void display_movey(int8_t y)
{

}

/**
 * @brief
 */
void display_move(int8_t x, int8_t y)
{

}


/**
* @brief sends a number in ascii.
* The number could be represent with left-filled with a defined FILL char in 
* a defined BASE. Note that the LEN is 6 because 2^16 have its maximum ascii
* size represented with 5 chars + '\0' in the end.
*/
void display_send_uint8(uint8_t num)
{
    #define LEN      4              // length of the string w/ null terminator
    #define BASE    10              // string as a decimal base
    #define FILL    '0'             // character to fill non-used algarisms.
    
    uint8_t i = LEN -1;             // index for each char of the string
    char str[LEN] = {FILL};         // ascii zero filled array
    str[i] = '\0';                  // adds string null terminator
    while(i--){
        str[i] = FILL + (num % BASE);// gets each algarism}
        num /= BASE;                // prepare the next
    }
    display_send_string(str);       // sends the string
    
    #undef LEN
    #undef BASE
    #undef FILL
}

void display_send_int8(int8_t num)
{
    #define LEN     4              // length of the string w/ null terminator
    #define BASE    10              // string as a decimal base
    #define FILL    '0'             // character to fill non-used algarisms.
    
    uint8_t i = LEN -1;             // index for each char of the string
    char str[LEN] = {FILL};         // ascii zero filled array

    if(num < 0){
        str[0] = '-';
        num = -num;
    }else{
        str[0] = '+';
    }

    str[i] = '\0';                  // adds string null terminator
    while(i--){
        str[i] = FILL + (num % BASE);// gets each algarism}
        num /= BASE;                // prepare the next
    }
    display_send_string(str);         // sends the string
    
    #undef LEN
    #undef BASE
    #undef FILL    
}

/**
 * @brief sends a number in ascii.
 * The number could be represent with left-filled with a defined FILL char in 
 * a defined BASE. Note that the LEN is 6 because 2^16 have its maximum ascii
 * size represented with 5 chars + '\0' in the end.
 */
void display_send_uint16(uint16_t num)
{
    #define LEN      6              // length of the string w/ null terminator
    #define BASE    10              // string as a decimal base
    #define FILL    '0'             // character to fill non-used algarisms.
    
    uint8_t i = LEN -1;             // index for each char of the string
    char str[LEN] = {FILL};         // ascii zero filled array
    str[i] = '\0';                  // adds string null terminator
    while(i--){
        str[i] = FILL + (num % BASE);// gets each algarism}
        num /= BASE;                // prepare the next
    }
    display_send_string(str);       // sends the string
    
    #undef LEN
    #undef BASE
    #undef FILL
}

void display_send_int16(int16_t num)
{
    #define LEN     7              // length of the string w/ null terminator
    #define BASE    10              // string as a decimal base
    #define FILL    '0'             // character to fill non-used algarisms.
    
    uint8_t i = LEN -1;             // index for each char of the string
    char str[LEN] = {FILL};         // ascii zero filled array

    if(num < 0){
        str[0] = '-';
        num = -num;
    }else{
        str[0] = '+';
    }

    str[i] = '\0';                  // adds string null terminator
    while(i--){
        str[i] = FILL + (num % BASE);// gets each algarism}
        num /= BASE;                // prepare the next
    }
    display_send_string(str);         // sends the string
    
    #undef LEN
    #undef BASE
    #undef FILL    
}

/**
 * @brief sends a number in ascii.
 * The number could be represent with left-filled with a defined FILL char in 
 * a defined BASE. Note that the LEN is 11 because 2^32 have its maximum ascii
 * size represented with 10 chars + '\0' in the end.
 */
void display_send_uint32(uint32_t num)
{
    #define LEN     11              // length of the string w/ null terminator
    #define BASE    10              // string as a decimal base
    #define FILL    '0'             // character to fill non-used algarisms.
    
    uint8_t i = LEN -1;             // index for each char of the string
    char str[LEN] = {FILL};         // ascii zero filled array
    str[i] = '\0';                  // adds string null terminator
    while(i--){
        str[i] = FILL + (num % BASE);// gets each algarism}
        num /= BASE;                // prepare the next
    }
    display_send_string(str);       // sends the string
    
    #undef LEN
    #undef BASE
    #undef FILL
}

void display_send_int32(int32_t num)
{
    #define LEN     12              // length of the string w/ null terminator
    #define BASE    10              // string as a decimal base
    #define FILL    '0'             // character to fill non-used algarisms.
    
    uint8_t i = LEN -1;             // index for each char of the string
    char str[LEN] = {FILL};         // ascii zero filled array
    char sign = ' ';

    if(num < 0){
        sign = '-';
        num = -num;
    }

    str[i] = '\0';                  // adds string null terminator
    while(i--){
        str[i] = FILL + (num % BASE);// gets each algarism}
        num /= BASE;                // prepare the next
    }

    str[0] = sign;

    display_send_string(str);         // sends the string
    
    #undef LEN
    #undef BASE
    #undef FILL    
}
 

