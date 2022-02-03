/**
 * *****************************************************************************
 * @file	pca9535_i2c.c
 * @brief	Hardware abstraction layer
 *
 * *****************************************************************************
 */

/* Includes ------------------------------------------------------------------*/

#include <string.h>

#include "pca9535_i2c.h"

/* Export functions ----------------------------------------------------------*/

/* Get data from I/O port expander */
int pca9535_i2c_read(unsigned int dev_idx, unsigned int dev_addr, unsigned char reg_addr, unsigned char *dest, unsigned int len) {
	if (dev_idx >= PCA9535_USED_NUM ||
		dest == NULL) {
		return -2;
	}
	/*------------------------------------------------------------------------*/
	/* Specify a custom I2C read function here -------------------------------*/
	/* The function must return a value (-1) in case of a hardware error -----*/
	/*------------------------------------------------------------------------*/
	return 0;
}

/* Send data to I/O port expander */
int pca9535_i2c_write(unsigned int dev_idx, unsigned int dev_addr, unsigned char reg_addr, unsigned char *src, unsigned int len) {
	if (dev_idx >= PCA9535_USED_NUM ||
		src == NULL) {
		return -2;
	}
	/*------------------------------------------------------------------------*/
	/* Specify a custom I2C write function here ------------------------------*/
	/* The function must return a value (-1) in case of a hardware error -----*/
	/*------------------------------------------------------------------------*/
	return 0;
}
