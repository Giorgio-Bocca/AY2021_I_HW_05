/* ========================================
 * File contenente tutte le Macro utilizzate nel programma
 * ========================================
*/
#ifndef __MACRO_H
    #define __MACRO_H
    
    /**
    *   \brief 7-bit I2C address of the slave device.
    */
    #define LIS3DH_DEVICE_ADDRESS 0x18

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
    *    on Control register 1 based on the Data Output Rate selected   
    */
    #define LIS3DH_HR_MODE_CTRL_REG1_FREQ_1HZ 0x17
    #define LIS3DH_HR_MODE_CTRL_REG1_FREQ_10HZ 0x27
    #define LIS3DH_HR_MODE_CTRL_REG1_FREQ_25HZ 0x37
    #define LIS3DH_HR_MODE_CTRL_REG1_FREQ_50HZ 0x47
    #define LIS3DH_HR_MODE_CTRL_REG1_FREQ_100HZ 0x57
    #define LIS3DH_HR_MODE_CTRL_REG1_FREQ_200HZ 0x67

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
    *   \brief Address of the X axis output LSB register
    */
    #define LIS3DH_OUT_X_L 0x28

    /**
    *   \brief Address of the X axis output MSB register
    */
    #define LIS3DH_OUT_X_H 0x29
    
    /**
    *   \brief Address of the Y axis output LSB register
    */
    #define LIS3DH_OUT_Y_L 0x2A

    /**
    *   \brief Address of the Y axis output MSB register
    */
    #define LIS3DH_OUT_Y_H 0x2B
    
    /**
    *   \brief Address of the Z axis output LSB register
    */
    #define LIS3DH_OUT_Z_L 0x2C

    /**
    *   \brief Address of the Z axis output MSB register
    */
    #define LIS3DH_OUT_Z_H 0x2D
    
    
    /**
    *   \brief Address of the "startup" register of the EEPROM
    */
    #define EEPROM_REGISTER 0x00
    
    /**
    *   \brief Hex value to write in the "startup" register 
    *    of the EEPROM based on the Data Output Rate selected   
    */
    #define UN0 0x01
    #define DIECI 0x0A
    #define VENTICINQUE 0x19
    #define CINQUANTA 0x32
    #define CENTO 0x64
    #define DUECENTO 0xC8
    
#endif
/* [] END OF FILE */
