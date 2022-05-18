/**
 * *****************************************************************************
 * @file    pca9535_i2c.h
 * @brief   Hardware abstraction layer
 *
 * *****************************************************************************
 */

/* Define to prevent recursive inclusion */
#ifndef PCA9535_HAL_H__
#define PCA9535_HAL_H__

/* Includes ------------------------------------------------------------------*/

/* Export constants ----------------------------------------------------------*/

#define PCA9535_USED_NUM    1U

/* Export functions prototypes -----------------------------------------------*/

/**
 * @brief       Get data from I/O port expander
 * @param[in]   dev_idx     Device index on the board from 0 to
 *              PCA9535_USED_NUM - 1
 * @param[in]   dev_addr    Target device address
 * @param[in]   reg_addr    Target register address
 * @param[out]  dest        Buffer for storing data received from the device
 * @param[in]   len         Data buffer length in bytes
 * @return
 *              - (-2): Parameter error
 *              - (-1): Bus error
 *              - 0: Success
 */
int pca9535_i2c_read(   unsigned int dev_idx,
                        unsigned int dev_addr,
                        unsigned char reg_addr,
                        unsigned char *dest,
                        unsigned int len);

/**
 * @brief       Send data to I/O port expander
 * @param[in]   dev_idx     Device index on the board from 0 to
 *              PCA9535_USED_NUM - 1
 * @param[in]   dev_addr    Target device address
 * @param[in]   reg_addr    Target register address
 * @param[in]   src         Buffer containing data to send
 * @param[in]   len         Data buffer length in bytes
 * @return
 *              - (-2): Parameter error
 *              - (-1): HW error
 *              - 0: Success
 */
int pca9535_i2c_write(  unsigned int dev_idx,
                        unsigned int dev_addr,
                        unsigned char reg_addr,
                        unsigned char *src,
                        unsigned int len);

#endif  /* PCA9535_HAL_H__ */
