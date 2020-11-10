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
#include "EEPROMFreq.h"
#include "Macro.h"
#include "project.h"
#include "ErrorCodes.h"
#include "I2C_Interface.h"
#include "stdio.h"
#include "InterruptRoutines.h"

uint8_t ctrl_reg1;
uint8_t ctrl_reg4;
ErrorCode error;

extern uint16_t p;

char message[50];

void EEPROM_Startup_Freq(uint8_t EEPROM_f)
{
    switch(EEPROM_f)
    {
        case 1:
            ctrl_reg1 = LIS3DH_HR_MODE_CTRL_REG1_FREQ_1HZ;
            error = I2C_Peripheral_WriteRegister(LIS3DH_DEVICE_ADDRESS, LIS3DH_CTRL_REG1, ctrl_reg1);
        
            if (error == NO_ERROR)
            {
                sprintf(message, "CONTROL REGISTER 1 successfully written as: 0x%02X\r\n", ctrl_reg1);
                UART_Debug_PutString(message); 
                p = 1000;
                Timer_WritePeriod(p);
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
                p = 100;
                Timer_WritePeriod(p);
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
                p = 40;
                Timer_WritePeriod(p);
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
                p = 20;
                Timer_WritePeriod(p);
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
                p = 10;
                Timer_WritePeriod(p);
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
                p = 5;
                Timer_WritePeriod(p);
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
