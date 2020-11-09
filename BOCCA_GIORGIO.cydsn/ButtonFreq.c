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
#include "ButtonFreq.h"
#include "Macro.h"
#include "project.h"
#include "ErrorCodes.h"
#include "I2C_Interface.h"
#include "stdio.h"

uint8_t ctrl_reg1;
uint8_t ctrl_reg4;
ErrorCode error;
uint8_t eeprom_value;

char message[50];
char stringa[30];

CY_ISR(Debouncer_ISR)
{
    Button_Freq(eeprom_value);
}

void Button_Freq(uint8_t EEPROM_f)
{
    switch(EEPROM_f)
    {
        case 1:
            ctrl_reg1 = LIS3DH_HR_MODE_CTRL_REG1_FREQ_10HZ;
            error = I2C_Peripheral_WriteRegister(LIS3DH_DEVICE_ADDRESS, LIS3DH_CTRL_REG1, ctrl_reg1);
        
            if (error == NO_ERROR)
            {
                sprintf(message, "CONTROL REGISTER 1 successfully written as: 0x%02X\r\n", ctrl_reg1);
                UART_Debug_PutString(message); 
            }
            else
            {
                UART_Debug_PutString("Error occurred during I2C comm to set control register 1\r\n");   
            }
            
            EEPROM_UpdateTemperature();
            EEPROM_WriteByte(DIECI, EEPROM_REGISTER);
            eeprom_value = EEPROM_ReadByte(EEPROM_REGISTER);
            sprintf(stringa, "Valore nella EEPROM: 0x%02X\r\n", eeprom_value);
            UART_Debug_PutString(stringa);
            
            break;
        
        case 10:
            ctrl_reg1 = LIS3DH_HR_MODE_CTRL_REG1_FREQ_25HZ;
            error = I2C_Peripheral_WriteRegister(LIS3DH_DEVICE_ADDRESS, LIS3DH_CTRL_REG1, ctrl_reg1);
        
            if (error == NO_ERROR)
            {
                sprintf(message, "CONTROL REGISTER 1 successfully written as: 0x%02X\r\n", ctrl_reg1);
                UART_Debug_PutString(message); 
            }
            else
            {
                UART_Debug_PutString("Error occurred during I2C comm to set control register 1\r\n");   
            }
            
             
            EEPROM_UpdateTemperature();
            EEPROM_WriteByte(VENTICINQUE, EEPROM_REGISTER);
            eeprom_value = EEPROM_ReadByte(EEPROM_REGISTER);
            sprintf(stringa, "Valore nella EEPROM: 0x%02X\r\n", eeprom_value);
            UART_Debug_PutString(stringa);
            
            break;
            
        case 25:
            ctrl_reg1 = LIS3DH_HR_MODE_CTRL_REG1_FREQ_50HZ;
            error = I2C_Peripheral_WriteRegister(LIS3DH_DEVICE_ADDRESS, LIS3DH_CTRL_REG1, ctrl_reg1);
        
            if (error == NO_ERROR)
            {
                sprintf(message, "CONTROL REGISTER 1 successfully written as: 0x%02X\r\n", ctrl_reg1);
                UART_Debug_PutString(message); 
            }
            else
            {
                UART_Debug_PutString("Error occurred during I2C comm to set control register 1\r\n");   
            }
            
            EEPROM_UpdateTemperature();
            EEPROM_WriteByte(CINQUANTA, EEPROM_REGISTER);
            eeprom_value = EEPROM_ReadByte(EEPROM_REGISTER);
            sprintf(stringa, "Valore nella EEPROM: 0x%02X\r\n", eeprom_value);
            UART_Debug_PutString(stringa);
            
            break;
        
        case 50:
            ctrl_reg1 = LIS3DH_HR_MODE_CTRL_REG1_FREQ_100HZ;
            error = I2C_Peripheral_WriteRegister(LIS3DH_DEVICE_ADDRESS, LIS3DH_CTRL_REG1, ctrl_reg1);
        
            if (error == NO_ERROR)
            {
                sprintf(message, "CONTROL REGISTER 1 successfully written as: 0x%02X\r\n", ctrl_reg1);
                UART_Debug_PutString(message); 
            }
            else
            {
                UART_Debug_PutString("Error occurred during I2C comm to set control register 1\r\n");   
            }
            
            EEPROM_UpdateTemperature();
            EEPROM_WriteByte(CENTO, EEPROM_REGISTER);
            eeprom_value = EEPROM_ReadByte(EEPROM_REGISTER);
            sprintf(stringa, "Valore nella EEPROM: 0x%02X\r\n", eeprom_value);
            UART_Debug_PutString(stringa);
            
            break;
            
        case 100:
            ctrl_reg1 = LIS3DH_HR_MODE_CTRL_REG1_FREQ_200HZ;
            error = I2C_Peripheral_WriteRegister(LIS3DH_DEVICE_ADDRESS, LIS3DH_CTRL_REG1, ctrl_reg1);
        
            if (error == NO_ERROR)
            {
                sprintf(message, "CONTROL REGISTER 1 successfully written as: 0x%02X\r\n", ctrl_reg1);
                UART_Debug_PutString(message); 
            }
            else
            {
                UART_Debug_PutString("Error occurred during I2C comm to set control register 1\r\n");   
            }
            
            EEPROM_UpdateTemperature();
            EEPROM_WriteByte(DUECENTO, EEPROM_REGISTER);
            eeprom_value = EEPROM_ReadByte(EEPROM_REGISTER);
            sprintf(stringa, "Valore nella EEPROM: 0x%02X\r\n", eeprom_value);
            UART_Debug_PutString(stringa);
            
            break;
            
        case 200:
            ctrl_reg1 = LIS3DH_HR_MODE_CTRL_REG1_FREQ_1HZ;
            error = I2C_Peripheral_WriteRegister(LIS3DH_DEVICE_ADDRESS, LIS3DH_CTRL_REG1, ctrl_reg1);
        
            if (error == NO_ERROR)
            {
                sprintf(message, "CONTROL REGISTER 1 successfully written as: 0x%02X\r\n", ctrl_reg1);
                UART_Debug_PutString(message); 
            }
            else
            {
                UART_Debug_PutString("Error occurred during I2C comm to set control register 1\r\n");   
            }
            
            EEPROM_UpdateTemperature();
            EEPROM_WriteByte(UN0, EEPROM_REGISTER);
            eeprom_value = EEPROM_ReadByte(EEPROM_REGISTER);
            sprintf(stringa, "Valore nella EEPROM: 0x%02X\r\n", eeprom_value);
            UART_Debug_PutString(stringa);
            
            break;
        
        default:
            UART_Debug_PutString("Error occurred during I2C comm to set control register 1\r\n");
            break;
    }
}
/* [] END OF FILE */
