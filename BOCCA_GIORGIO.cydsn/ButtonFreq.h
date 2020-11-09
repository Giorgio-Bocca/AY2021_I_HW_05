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
#ifndef __BUTTON_FREQ_H
    #define __BUTTON_FREQ_H
    
    #include "project.h"
    
    CY_ISR_PROTO(Debouncer_ISR);
    
    void Button_Freq(uint8_t EEPROM_f);
    
#endif

/* [] END OF FILE */
