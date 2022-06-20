#include "main.h"

// F1031V Mass Air Flow Sensor
#define F1031V_SLOPE 36.463 
#define F1031V_INTERCEPT 18.036

void F1031V()
{
    // Poll ADC
    if (ADCSRA &= ~(1 << 6))
    {
        uint16_t F1031V_x;
        uint16_t F1031V_y;
        uint8_t* BUFPTR;
        char BUFFER[16];
        
        BUFPTR = &BUFFER;
        
        F1031V_x = ADC; // 10-bit value

        // Convert to V and solve for y
        F1031V_x = F1031V_x / 1023 * 5;
        F1031V_y = (F1031V_SLOPE*F1031V_x)-F1031V_INTERCEPT; 

        // Clear LCD
        LCD_CMD(0x01);

        // Report flow and Vin to ADC via LCD
        itoa(F1031V_y, BUFFER, 10); // y
        LCD_STR(BUFPTR);

        memcpy(BUFFER, " L/min (STP)", 16);
        LCD_STR(BUFPTR);

        LCD_CMD(0xC0); // Next line

        itoa(F1031V_x, BUFFER, 10); // x
        LCD_STR(BUFPTR);

        memcpy(BUFFER, "V (A0)", 16);
        LCD_STR(BUFPTR);
    }
}
