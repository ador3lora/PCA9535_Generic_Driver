/**
 * *****************************************************************************
 * @file    pca9535_driver.c
 * @brief   16-bit I2C-bus and SMBus, low power I/O port with interrupt
 *
 * *****************************************************************************
 */

/* Includes ------------------------------------------------------------------*/

#include <stdbool.h>
#include <stddef.h>

#include "pca9535_i2c.h"
#include "pca9535_driver.h"

/* Private functions prototypes ----------------------------------------------*/

/**
 * @brief       Get register address to write according to input parameters
 * @param[in]   reg_type    Register type
 * @param[in]   port        IO0, IO1 or both
 * @param[in]   len         Number of bytes to process
 * @param[out]  reg_addr    Pointer to a variable to store the register address
 * @return
 *              - (-1): Parameter error
 *              - 0: Success
 */
static int _pca9535_get_reg_addr(   pca9535_reg_type_t reg_type,
                                    pca9535_port_t port,
                                    int len,
                                    unsigned char *reg_addr);

/* Private functions ---------------------------------------------------------*/

/* Get register address to write according to input parameters */
static int _pca9535_get_reg_addr(pca9535_reg_type_t reg_type, pca9535_port_t port, int len, unsigned char *reg_addr) {
    if (port == PCA9535_PORT_BOTH && len != 2) {
        return -1;
    } else if ((port == PCA9535_PORT_0 || port == PCA9535_PORT_1) && len != 1) {
        return -1;
    } else if (port != PCA9535_PORT_0 && port != PCA9535_PORT_1 && port != PCA9535_PORT_BOTH) {
        return -1;
    }
    switch (reg_type) {
    case PCA9535_REG_TYPE_INPUT:    *reg_addr = PCA9535_REG_INPUT_0;    break;
    case PCA9535_REG_TYPE_OUTPUT:   *reg_addr = PCA9535_REG_OUTPUT_0;   break;
    case PCA9535_REG_TYPE_POL_INV:  *reg_addr = PCA9535_REG_POL_INV_0;  break;
    case PCA9535_REG_TYPE_CONFIG:   *reg_addr = PCA9535_REG_CONFIG_0;   break;
    default: return -1;
    }
    if (port == PCA9535_PORT_1) {
        (*reg_addr)++;
    }
    return 0;
}

/* Export functions ----------------------------------------------------------*/

/* Initialize the structure of the used device with the necessary values */
int pca9535_init(pca9535_handle_t dev_hdl, pca9535_t *cfg) {
    if (dev_hdl == NULL ||
        cfg == NULL) {
        return -2;
    }
    dev_hdl->idx = cfg->idx;
    dev_hdl->addr = cfg->addr;
    dev_hdl->busy = cfg->busy;
    dev_hdl->err = cfg->err;
    return 0;
}

/* Get the value of one or a pair of IC registers */
int pca9535_get_reg(pca9535_handle_t dev_hdl, pca9535_reg_type_t reg_type, pca9535_port_t port, unsigned char *value, int len) {
    if (dev_hdl == NULL ||
        value == NULL) {
        return -2;
    }
    int ret = 0;
    unsigned char reg_addr = 0;
    if (_pca9535_get_reg_addr(reg_type, port, len, &reg_addr) != 0) {
        return -2;
    }
    while (dev_hdl->busy == true);
    dev_hdl->busy = true;
    if ((ret = pca9535_i2c_read(dev_hdl->idx, dev_hdl->addr, reg_addr, value, len)) != 0) {
        if (ret == -1) {
            dev_hdl->err = true;
            ret = -1;
        } else if (ret == -2) {
            ret = -2;
        }
    }
    dev_hdl->busy = false;
    return (int)ret;
}

/* Set the value of one or a pair of IC registers */
int pca9535_set_reg(pca9535_handle_t dev_hdl, pca9535_reg_type_t reg_type, pca9535_port_t port, unsigned char *value, int len) {
    if (dev_hdl == NULL ||
        value == NULL) {
        return -2;
    }
    int ret = 0;
    unsigned char reg_addr = 0;
    if (_pca9535_get_reg_addr(reg_type, port, len, &reg_addr) != 0) {
        return -2;
    }
    while (dev_hdl->busy == true);
    dev_hdl->busy = true;
    if ((ret = pca9535_i2c_write(dev_hdl->idx, dev_hdl->addr, reg_addr, value, len)) != 0) {
        if (ret == -1) {
            dev_hdl->err = true;
            ret = -1;
        } else if (ret == -2) {
            ret = -2;
        }
    }
    dev_hdl->busy = false;
    return (int)ret;
}
