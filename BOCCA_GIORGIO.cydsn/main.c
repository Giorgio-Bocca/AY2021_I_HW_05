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

extern uint8_t eeprom_value;
extern uint8_t ctrl_reg1;
extern uint8_t ctrl_reg4;
extern ErrorCode error;

extern char message[50];
extern char stringa[30];

float gravity_acc = 9.81;

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    I2C_Peripheral_Start();
    UART_Debug_Start();
    EEPROM_Start();
    
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
    
    /*
    uint8_t flag_data_processing = 0;
    uint8_t flag_status_ok = 0;
    uint8_t status_register;
    
    int16_t Out_X_axis;
    uint8_t X_axis_Data[2];
    float X_axis_acc;
    
    int16_t Out_Y_axis;
    uint8_t Y_axis_Data[2];
    float Y_axis_acc;
    
    int16_t Out_Z_axis;
    uint8_t Z_axis_Data[2];
    float Z_axis_acc;
    */
    for(;;)
    { 
        /*
        error = I2C_Peripheral_ReadRegister(LIS3DH_DEVICE_ADDRESS,LIS3DH_STATUS_REG,&status_register);
    
        if (error == NO_ERROR)
        {
            //sprintf(message, "STATUS REGISTER: 0x%02X\r\n", status_register);
            //UART_Debug_PutString(message);
            flag_status_ok = 1;
        }
        else
        {
            //UART_Debug_PutString("Error occurred during I2C comm to read status register\r\n"); 
            flag_status_ok = 0;
        }
        
        if(flag_status_ok == 1)
        {
            if( (status_register & (1<<3)) == 0 ) //se il bit ZYXDA dello status register è uguale a 0
            {                                     //non faccio nulla perchè i 3 valori non sono ancora pronti
                flag_data_processing = 0;
            }
            else
            { 
                flag_data_processing = 1;
            }
        }
        
        if(flag_data_processing == 1)
        {
            if( (status_register & (1<<7)) == 1 ) //se il bit ZYXOR dello status register è uguale a 1
            {                                     //vuol dire che la frequenza di lettura non è adeguata
                UART_Debug_PutString("Some data have been overwritten");
            }
            else
            {
                error = I2C_Peripheral_ReadRegister(LIS3DH_DEVICE_ADDRESS,LIS3DH_OUT_X_L,&X_axis_Data[0]);
                error = I2C_Peripheral_ReadRegister(LIS3DH_DEVICE_ADDRESS,LIS3DH_OUT_X_H,&X_axis_Data[1]);
        
                if (error == NO_ERROR)
                {
                    Out_X_axis = (int16)((X_axis_Data[0] | (X_axis_Data[1]<<8)))>>4;
                    X_axis_acc = Out_X_axis * gravity_acc;
                    sprintf(message, "X axis value : %d\r\n", Out_X_axis);
                    UART_Debug_PutString(message);
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
                    Y_axis_acc = Out_Y_axis * gravity_acc;
                    sprintf(message, "Y axis value : %d\r\n", Out_Y_axis);
                    UART_Debug_PutString(message);
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
                    Z_axis_acc = Out_Z_axis * gravity_acc;
                    sprintf(message, "Z axis value : %d\r\n", Out_Z_axis);
                    UART_Debug_PutString(message);
                    
                }
                else
                {
                    UART_Debug_PutString("Error occurred during I2C comm to read Z axis register\r\n");   
                }
            }
        }*/
    }
}

/* [] END OF FILE */
