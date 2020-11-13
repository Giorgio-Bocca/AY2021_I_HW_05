/* ========================================
 **\file main.c
 * brief main file for project 
 * ASSIGNMENT 05: CONFIGURAZIONE, LETTURA E VISUALIZZAZIONE DEI DATI 
 * DI UN ACCELEROMETRO MEDIANTE PROTOCOLLO DI COMUNICAZIONE I2C E UART
 *
 * Il progetto prevede l'utilizzo del protocollo I2C per mettere in 
 * comunicazione il microcontrollore con un accelerometro LIS3DH.
 * L'obiettivo è quello di acquisire i dati relativi ai tre assi X, Y e Z,
 * convertirli in m/sec^2 e trasmetterli tramite comunicazione UART 
 * al BCC per la visualizzazione.
 * Per i dati è richiesta una High Resolution Mode.
 * Inoltre, deve essere possibile ciclare le frequenze dell'Output Data Rate
 * tramite la pressione del tasto presente sul microcontrollore. 
 * 
 **\author Giorgio Bocca
 * ========================================
*/

#include "project.h"
#include "I2C_Interface.h"
#include "stdio.h"
#include "Macro.h"
#include "EEPROMFreq.h"
#include "ButtonFreq.h"
#include "InterruptRoutines.h"

extern uint8_t eeprom_value; //variabile contenete il valore della frequenza da salvare nel registro della EEPROM
extern uint8_t ctrl_reg1; //variabile contenente il valore di configurazione del control register 1 (da scrivere)
extern uint8_t ctrl_reg4; //variabile contenente il valore di configurazione del control register 4 (da scrivere)
extern ErrorCode error;

extern char message[50];
extern char stringa[30];

extern uint8_t status_register; ////variabile contenente il valore di configurazione dello status register (da leggere)

int main(void)
{
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    //Inizializzazione delle periferiche
    I2C_Peripheral_Start();
    UART_Debug_Start();
    EEPROM_Start();
    Timer_Start();
    
    //Inizializzazione delle ISR
    isr_Timer_StartEx(Custom_TIMER_ISR);
    Debouncer_isr_StartEx(Debouncer_ISR);
    
    CyDelay(5); //"The boot procedure is complete about 5 milliseconds after device power-up." 
    
    DataBuffer[0] = 0xA0; //Header byte
    DataBuffer[TRANSMIT_BUFFER_SIZE-1] = 0xC0; //Tail byte
    
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
    
    //Leggo il valore della frequenza contenuto nella EEPROM
    eeprom_value = EEPROM_ReadByte(EEPROM_REGISTER);
    sprintf(stringa, "Valore nella EEPROM: %d Hz\r\n", eeprom_value);
    UART_Debug_PutString(stringa);   
    
    //Configuro l'ODR a seconda del valore di frequenza letto dalla EEPROM
    EEPROM_Startup_Freq(eeprom_value);
    
    /* Enable global interrupts. */
    CyGlobalIntEnable;
      
    for(;;)
    {   
        if(PacketReadyFlag == 1)
        {
            //Send out the data
            UART_Debug_PutArray(DataBuffer, TRANSMIT_BUFFER_SIZE);
            PacketReadyFlag = 0;
        }
    }
}
/* [] END OF FILE */
