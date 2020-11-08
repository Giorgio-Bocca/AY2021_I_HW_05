/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "project.h"

uint8_t eeprom_value;
uint8_t sampling_freq;

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    EEPROM_Start();
    
    eeprom_value = EEPROM_ReadByte(0x00);
    
    EEPROM_UpdateTemperature();
    EEPROM_WriteByte(0x64, 0x00); //0x64 = 100 in base decimale
    eeprom_value = EEPROM_ReadByte(0x00);

    for(;;)
    {
        /* Place your application code here. */
    }
}

/* [] END OF FILE */
