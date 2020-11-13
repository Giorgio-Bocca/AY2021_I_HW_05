/* ========================================
 * Nel file avviene la lettura dei dati relativi ai tre assi, 
 * la conversione in m/sec^2 e la preparazione dei pacchetti di byte
 * da inviare tramite UART al Bridge Control Panel per essere plottati.
 * La lettura è scandita in modo preciso attraverso la generazione di interrupt
 * sincronizzate con l'Output Data Rate corrente.
 * ========================================
*/
#include "project.h"
#include "I2C_Interface.h"
#include "stdio.h"
#include "Macro.h"
#include "InterruptRoutines.h"

ErrorCode error;

uint8_t flag_data_processing=0; //variabile usata per indicare quando il bit ZYXDA è a 1, cioè quando i dati dei 3 assi sono pronti
uint8_t flag_status_register_ok=0; //variabile usata per indicare se la lettura dello status register è avvenuta correttamente
uint8_t status_register; //variabile contenente i valori di configurazione dello status register

//VARIABILI CONTENENTI I DATI LETTI (2 REGISTRI DA 8 BIT PER CIASCUN ASSE) 
//RELATIVI AI 3 ASSI E RICOMPOSTI 
int16_t Out_X_axis;
uint8_t X_axis_Data[2];

int16_t Out_Y_axis;
uint8_t Y_axis_Data[2];

int16_t Out_Z_axis;
uint8_t Z_axis_Data[2];

//VARIABILI CONTENENTI IL VALORE CONVERTITO IN m/sec^2
float Out_X_acc;
float Out_Y_acc;
float Out_Z_acc;

int16 trick = 1000; //variabile usata per spostare a dx la virgola di 3 cifre --> nel BCP,
                    //settando nel pannello di configurazione una scala di 0.001, è poi possibile 
                    //riportare il dato al valore corretto
float gravity_acc = 9.81; //1 g = 9.81 m/sec^2

CY_ISR(Custom_TIMER_ISR)
{ 
    Timer_ReadStatusRegister();
    
    if(flag_data_processing == 0)
    {
        //LETTURA DELLO STATUS REGISTER 
        error = I2C_Peripheral_ReadRegister(LIS3DH_DEVICE_ADDRESS,LIS3DH_STATUS_REG,&status_register);
        
        if (error == NO_ERROR)
        {
            flag_status_register_ok = 1;
        }
        else
        {
            UART_Debug_PutString("Error occurred during I2C comm to read status register\r\n"); 
            flag_status_register_ok = 0;
        }
        
        if(flag_status_register_ok == 1)
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
        
        //LETTURA DEI DATI DAI RISPETTIVI REGISTRI, CONVERSIONE IN m/sec^2 E CREAZIONE DEL PACCHETTO DI BYTES DA INVIARE AL BCC
        if(flag_data_processing == 1)
        { 
            error = I2C_Peripheral_ReadRegister(LIS3DH_DEVICE_ADDRESS,LIS3DH_OUT_X_L,&X_axis_Data[0]);
            error = I2C_Peripheral_ReadRegister(LIS3DH_DEVICE_ADDRESS,LIS3DH_OUT_X_H,&X_axis_Data[1]);
            error = I2C_Peripheral_ReadRegister(LIS3DH_DEVICE_ADDRESS,LIS3DH_OUT_Y_L,&Y_axis_Data[0]);
            error = I2C_Peripheral_ReadRegister(LIS3DH_DEVICE_ADDRESS,LIS3DH_OUT_Y_H,&Y_axis_Data[1]);
            error = I2C_Peripheral_ReadRegister(LIS3DH_DEVICE_ADDRESS,LIS3DH_OUT_Z_L,&Z_axis_Data[0]);
            error = I2C_Peripheral_ReadRegister(LIS3DH_DEVICE_ADDRESS,LIS3DH_OUT_Z_H,&Z_axis_Data[1]);
            
            if (error == NO_ERROR)
            {
                //Il >>4 dipende dalla High Resolution Mode con cui vengono forniti i dati, in formato da 12 bits
                Out_X_axis = (int16)((X_axis_Data[0] | (X_axis_Data[1]<<8)))>>4;
                Out_Y_axis = (int16)((Y_axis_Data[0] | (Y_axis_Data[1]<<8)))>>4;
                Out_Z_axis = (int16)((Z_axis_Data[0] | (Z_axis_Data[1]<<8)))>>4; 
                
                //L'intervallo di dati selezionato è quello [-2g +2g] tramite i bits FS = 00 settati
                //nel control register 4, con una sensibilità pari a 1 mg/digit.
                
                //Out_X_acc = (Out_X_axis*gravity_acc);
                //Out_X_axis = (int16) (Out_X_acc*trick);
                DataBuffer[1] = (int8_t) (Out_X_axis & 0xFF);
                DataBuffer[2] = (int8_t) (Out_X_axis >> 8);
                
                //Out_Y_acc = (Out_Y_axis*gravity_acc);
                //Out_Y_axis = (int16) (Out_Y_acc*trick);
                DataBuffer[3] = (int8_t) (Out_Y_axis & 0xFF);
                DataBuffer[4] = (int8_t) (Out_Y_axis >> 8);
                
                //Out_Z_acc = (Out_Z_axis*gravity_acc);   
                //Out_Z_axis = (int16) (Out_Z_acc*trick);
                DataBuffer[5] = (int8_t) (Out_Z_axis & 0xFF);
                DataBuffer[6] = (int8_t) (Out_Z_axis >> 8);
               
                PacketReadyFlag = 1;
                flag_data_processing = 0;
            }
            else
            {
                UART_Debug_PutString("Error occurred during I2C comm to read some axis registers\r\n");   
            }
        }
    }
}
/* [] END OF FILE */
