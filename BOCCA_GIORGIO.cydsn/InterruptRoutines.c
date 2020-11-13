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
#include "I2C_Interface.h"
#include "stdio.h"
#include "Macro.h"
#include "InterruptRoutines.h"

ErrorCode error;

char message[50];

uint8_t flag_data_processing=0;
uint8_t flag_status_ok=0;
uint8_t status_register;

int16_t Out_X_axis;
uint8_t X_axis_Data[2];

int16_t Out_Y_axis;
uint8_t Y_axis_Data[2];

int16_t Out_Z_axis;
uint8_t Z_axis_Data[2];

float Out_X_acc;
float Out_Y_acc;
float Out_Z_acc;

int16 trick = 1000;
float gravity_acc = 9.81;

CY_ISR(Custom_TIMER_ISR)
{ 
    Timer_ReadStatusRegister();
    
    if(flag_data_processing == 0)
    {
        error = I2C_Peripheral_ReadRegister(LIS3DH_DEVICE_ADDRESS,LIS3DH_STATUS_REG,&status_register);
        
        if (error == NO_ERROR)
        {
            
            flag_status_ok = 1;
        }
        else
        {
            UART_Debug_PutString("Error occurred during I2C comm to read status register\r\n"); 
            flag_status_ok = 0;
        }
        
        if(flag_status_ok == 1)
        {
            if((status_register & 0x08) == 0x00) //se il bit ZYXDA dello status register è uguale a 0
            {                                    //non faccio nulla perchè i 3 valori non sono ancora pronti
                flag_data_processing = 0;
            }
            else
            { 
                flag_data_processing = 1;
            }
        }
        
        if(flag_data_processing == 1)
        { 
            error = I2C_Peripheral_ReadRegister(LIS3DH_DEVICE_ADDRESS,LIS3DH_OUT_X_L,&X_axis_Data[0]);
            error = I2C_Peripheral_ReadRegister(LIS3DH_DEVICE_ADDRESS,LIS3DH_OUT_X_H,&X_axis_Data[1]);

            if (error == NO_ERROR)
            {
                Out_X_axis = (int16)((X_axis_Data[0] | (X_axis_Data[1]<<8)))>>4;
                
                //Out_X_acc = (Out_X_axis*gravity_acc)/1024;
                //Out_X_axis = (int16) (Out_X_acc*trick);
                DataBuffer[1] = (int8_t) (Out_X_axis & 0xFF);
                DataBuffer[2] = (int8_t) (Out_X_axis >> 8);
            }
            else
            {
                UART_Debug_PutString("Error occurred during I2C comm to read X axis register\r\n");   
            }

            error = I2C_Peripheral_ReadRegister(LIS3DH_DEVICE_ADDRESS,LIS3DH_OUT_Y_L,&Y_axis_Data[0]);
            error = I2C_Peripheral_ReadRegister(LIS3DH_DEVICE_ADDRESS,LIS3DH_OUT_Y_H,&Y_axis_Data[1]);

            if (error == NO_ERROR)
            {
                Out_Y_axis = (int16)((Y_axis_Data[0] | (Y_axis_Data[1]<<8)))>>4;
                
                //Out_Y_acc = (Out_Y_axis*gravity_acc)/1024;
                //Out_Y_axis = (int16) (Out_Y_acc*trick);
                DataBuffer[3] = (int8_t) (Out_Y_axis & 0xFF);
                DataBuffer[4] = (int8_t) (Out_Y_axis >> 8);
            }
            else
            {
                UART_Debug_PutString("Error occurred during I2C comm to read Y axis register\r\n");   
            }

            error = I2C_Peripheral_ReadRegister(LIS3DH_DEVICE_ADDRESS,LIS3DH_OUT_Z_L,&Z_axis_Data[0]);
            error = I2C_Peripheral_ReadRegister(LIS3DH_DEVICE_ADDRESS,LIS3DH_OUT_Z_H,&Z_axis_Data[1]);

            if (error == NO_ERROR)
            {
                Out_Z_axis = (int16)((Z_axis_Data[0] | (Z_axis_Data[1]<<8)))>>4;
                
                //Out_Z_acc = (Out_Z_axis*gravity_acc)/1024;   
                //Out_Z_axis = (int16) (Out_Z_acc*trick);
                DataBuffer[5] = (int8_t) (Out_Z_axis & 0xFF);
                DataBuffer[6] = (int8_t) (Out_Z_axis >> 8);              
            }
            else
            {
                UART_Debug_PutString("Error occurred during I2C comm to read Z axis register\r\n");   
            }
                     
            PacketReadyFlag = 1;
            flag_data_processing = 0;
        }
    }
}
/* [] END OF FILE */
