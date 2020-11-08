/* ========================================
 *
 *
 *
 * ========================================
*/
#include "project.h"
#include "I2C_Interface.h"
#include "stdio.h"

uint8_t eeprom_value;
uint8_t ctrl_reg1;
uint8_t ctrl_reg4;
ErrorCode error;

/**
*   \brief 7-bit I2C address of the slave device.
*/
#define LIS3DH_DEVICE_ADDRESS 0x18

/**
*   \brief Address of the WHO AM I register
*/
#define LIS3DH_WHO_AM_I_REG_ADDR 0x0F

/**
*   \brief Address of the Status register
*/
#define LIS3DH_STATUS_REG 0x27

/**
*   \brief Address of the Control register 1
*/
#define LIS3DH_CTRL_REG1 0x20

/**
*   \brief Hex value to set High Resolution Mode to the accelerator 
*    on Control register 1 based on the Data Rate selected   
*/
#define LIS3DH_HR_MODE_CTRL_REG1_FREQ_1HZ 0x17
#define LIS3DH_HR_MODE_CTRL_REG1_FREQ_10HZ 0x27
#define LIS3DH_HR_MODE_CTRL_REG1_FREQ_25HZ 0x37
#define LIS3DH_HR_MODE_CTRL_REG1_FREQ_50HZ 0x47
#define LIS3DH_HR_MODE_CTRL_REG1_FREQ_100HZ 0x57
#define LIS3DH_HR_MODE_CTRL_REG1_FREQ_200HZ 0x67

/**
*   \brief Address of the Temperature Sensor Configuration register
*/
#define LIS3DH_TEMP_CFG_REG 0x1F

/**
*   \brief Address of the Control register 4
*/
#define LIS3DH_CTRL_REG4 0x23

/**
*   \brief Hex value to set High Resolution Mode to the accelerator 
*    on Control register 4  
*/
#define LIS3DH_HR_MODE_CTRL_REG4 0x88

/**
*   \brief Address of the ADC output LSB register
*/
#define LIS3DH_OUT_ADC_3L 0x0C

/**
*   \brief Address of the ADC output MSB register
*/
#define LIS3DH_OUT_ADC_3H 0x0D

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    I2C_Peripheral_Start();
    UART_Debug_Start();
    EEPROM_Start();
    
    CyDelay(5); //"The boot procedure is complete about 5 milliseconds after device power-up."
    
    // String to print out messages on the UART
    char message[50];
    char stringa[30];

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
    
    EEPROM_UpdateTemperature();
    EEPROM_WriteByte(0xC8, 0x00); //0xC8 = 200 in base decimale
    eeprom_value = EEPROM_ReadByte(0x00);
    sprintf(stringa, "Valore nella EEPROM: 0x%02X\r\n", eeprom_value);
    UART_Debug_PutString(stringa);
    
    switch(eeprom_value)
    {
        case 1:
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
            break;
        
        case 10:
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
            break;
            
        case 25:
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
            break;
        
        case 50:
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
            break;
            
        case 100:
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
            break;
            
        case 200:
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
    
    for(;;)
    {
        /* Place your application code here. */
    }
}

/* [] END OF FILE */
