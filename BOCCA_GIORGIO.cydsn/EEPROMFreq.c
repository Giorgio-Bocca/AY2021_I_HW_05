/* ========================================
 * File contenente la funzione utilizzata per configurare l'ODR
 * dell'accelerometro nel control register 1 in base al
 * valore precedentemente letto nello "startup" register della EEPROM. 
 * Viene inoltre configurata la High Resolution Mode
 * mediante scrittura a 1 del bit HR nel control register 4 e 
 * a 0 del bit LPen nel control register 1. 
 * ========================================
*/
#include "EEPROMFreq.h"
#include "Macro.h"
#include "project.h"
#include "ErrorCodes.h"
#include "I2C_Interface.h"
#include "stdio.h"

uint8_t ctrl_reg1;
uint8_t ctrl_reg4;
ErrorCode error;

extern uint16_t p; //variabile contenente il periodo del timer, da settare ogni volta 
                   //a seconda della ODR selezionata 
char message[50];

void EEPROM_Startup_Freq(uint8_t EEPROM_f)
{
    //CONFIGURAZIONE DEL CONTROL REGISTER 1
    switch(EEPROM_f)
    {
        case 1:
            ctrl_reg1 = LIS3DH_HR_MODE_CTRL_REG1_FREQ_1HZ;
            error = I2C_Peripheral_WriteRegister(LIS3DH_DEVICE_ADDRESS, LIS3DH_CTRL_REG1, ctrl_reg1);
        
            if (error == NO_ERROR)
            {
                sprintf(message, "CONTROL REGISTER 1 successfully written as: 0x%02X\r\n", ctrl_reg1);
                UART_Debug_PutString(message); 
                p = 1000; //1 Hz --> 1000 msec = 1 sec 
                Timer_WritePeriod(p); //setto il periodo pari a 1 sec
            }
            else
            {
                UART_Debug_PutString("Error occurred during I2C comm to set control register 1\r\n");   
            }
            break;
        
        case 10:
            ctrl_reg1 = LIS3DH_HR_MODE_CTRL_REG1_FREQ_10HZ;
            error = I2C_Peripheral_WriteRegister(LIS3DH_DEVICE_ADDRESS, LIS3DH_CTRL_REG1, ctrl_reg1);
        
            if (error == NO_ERROR)
            {
                sprintf(message, "CONTROL REGISTER 1 successfully written as: 0x%02X\r\n", ctrl_reg1);
                UART_Debug_PutString(message); 
                p = 100; //10 Hz --> 100 msec = 0.1 sec
                Timer_WritePeriod(p); //setto il periodo pari a 0.1 sec
            }
            else
            {
                UART_Debug_PutString("Error occurred during I2C comm to set control register 1\r\n");   
            }
            break;
            
        case 25:
            ctrl_reg1 = LIS3DH_HR_MODE_CTRL_REG1_FREQ_25HZ;
            error = I2C_Peripheral_WriteRegister(LIS3DH_DEVICE_ADDRESS, LIS3DH_CTRL_REG1, ctrl_reg1);
        
            if (error == NO_ERROR)
            {
                sprintf(message, "CONTROL REGISTER 1 successfully written as: 0x%02X\r\n", ctrl_reg1);
                UART_Debug_PutString(message); 
                p = 40; //25 Hz --> 40 msec = 0.04 sec
                Timer_WritePeriod(p); //setto il periodo pari a 0.04 sec
            }
            else
            {
                UART_Debug_PutString("Error occurred during I2C comm to set control register 1\r\n");   
            }
            break;
        
        case 50:
            ctrl_reg1 = LIS3DH_HR_MODE_CTRL_REG1_FREQ_50HZ;
            error = I2C_Peripheral_WriteRegister(LIS3DH_DEVICE_ADDRESS, LIS3DH_CTRL_REG1, ctrl_reg1);
        
            if (error == NO_ERROR)
            {
                sprintf(message, "CONTROL REGISTER 1 successfully written as: 0x%02X\r\n", ctrl_reg1);
                UART_Debug_PutString(message); 
                p = 20; //50 Hz --> 20 msec = 0.02 sec
                Timer_WritePeriod(p); //setto il periodo pari a 0.02 sec
            }
            else
            {
                UART_Debug_PutString("Error occurred during I2C comm to set control register 1\r\n");   
            }
            break;
            
        case 100:
            ctrl_reg1 = LIS3DH_HR_MODE_CTRL_REG1_FREQ_100HZ;
            error = I2C_Peripheral_WriteRegister(LIS3DH_DEVICE_ADDRESS, LIS3DH_CTRL_REG1, ctrl_reg1);
        
            if (error == NO_ERROR)
            {
                sprintf(message, "CONTROL REGISTER 1 successfully written as: 0x%02X\r\n", ctrl_reg1);
                UART_Debug_PutString(message); 
                p = 10; //100 Hz --> 10 msec = 0.01 sec
                Timer_WritePeriod(p); //setto il periodo pari a 0.01 sec
            }
            else
            {
                UART_Debug_PutString("Error occurred during I2C comm to set control register 1\r\n");   
            }
            break;
            
        case 200:
            ctrl_reg1 = LIS3DH_HR_MODE_CTRL_REG1_FREQ_200HZ;
            error = I2C_Peripheral_WriteRegister(LIS3DH_DEVICE_ADDRESS, LIS3DH_CTRL_REG1, ctrl_reg1);
        
            if (error == NO_ERROR)
            {
                sprintf(message, "CONTROL REGISTER 1 successfully written as: 0x%02X\r\n", ctrl_reg1);
                UART_Debug_PutString(message); 
                p = 5; //200 Hz --> 5 msec = 0.005 sec
                Timer_WritePeriod(p); //setto il periodo pari a 0.005 sec
            }
            else
            {
                UART_Debug_PutString("Error occurred during I2C comm to set control register 1\r\n");   
            }
            break;
        
        default:
            UART_Debug_PutString("Error occurred during I2C comm to set control register 1\r\n");
            break;
    }
    
    //CONFIGURAZIONE DEL CONTROL REGISTER 4 
    ctrl_reg4 = LIS3DH_HR_MODE_CTRL_REG4;
    error = I2C_Peripheral_WriteRegister(LIS3DH_DEVICE_ADDRESS, LIS3DH_CTRL_REG4, ctrl_reg4);
    
    if (error == NO_ERROR)
    {
        sprintf(message, "CTRL REGISTER 4: 0x%02X\r\n", ctrl_reg4);
        UART_Debug_PutString(message); 
    }
    else
    {
        UART_Debug_PutString("Error occurred during I2C comm to write CTRL REG 4\r\n");   
    }
}
/* [] END OF FILE */
