/* ========================================
 *
 *
 *
 * ========================================
*/
#include "project.h"
#include "I2C_Interface.h"
#include "stdio.h"
#include "Macro.h"
#include "EEPROMFreq.h"
#include "ButtonFreq.h"
#include "InterruptRoutines.h"

extern uint8_t eeprom_value;
extern uint8_t ctrl_reg1;
extern uint8_t ctrl_reg4;
extern ErrorCode error;

extern char message[50];
extern char stringa[30];

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    I2C_Peripheral_Start();
    UART_Debug_Start();
    EEPROM_Start();
    Timer_Start();
    isr_Timer_StartEx(Custom_TIMER_ISR);
    Debouncer_isr_StartEx(Debouncer_ISR);
    
    CyDelay(5); //"The boot procedure is complete about 5 milliseconds after device power-up."  

    // Check which devices are present on the I2C bus
    for (int i = 0 ; i < 128; i++)
    {
        if (I2C_Peripheral_IsDeviceConnected(i))
        {
            // print out the address is hex format
            sprintf(message, "Device 0x%02X is connected\r\n", i);
            UART_Debug_PutString(message); 
        }
        
    }
   
    eeprom_value = EEPROM_ReadByte(EEPROM_REGISTER);
    sprintf(stringa, "Valore nella EEPROM: %d Hz\r\n", eeprom_value);
    UART_Debug_PutString(stringa);   
    
    EEPROM_Startup_Freq(eeprom_value);
      
    for(;;)
    { 
    }
}

/* [] END OF FILE */
