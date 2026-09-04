#include "ai_generated_embedded.h"
#include "stm32f4xx_hal.h"

extern SPI_HandleTypeDef hspi1;
extern I2C_HandleTypeDef hi2c1;

/* ===================================================== */
/* ================= GPIO SECTION (CORRECT) ============= */
/* ===================================================== */

int ai_gpio_write(uint32_t port, uint16_t pin, uint8_t val)
{
    HAL_GPIO_WritePin((GPIO_TypeDef*)port,
                      pin,
                      val ? GPIO_PIN_SET : GPIO_PIN_RESET);

    return 1;
}

uint8_t ai_gpio_read(uint32_t port, uint16_t pin)
{
    return HAL_GPIO_ReadPin((GPIO_TypeDef*)port, pin);
}


/* ===================================================== */
/* ================= SPI SECTION (CORRECT) ============== */
/* ===================================================== */

int ai_spi_transfer(uint8_t *tx, uint8_t *rx, uint16_t len)
{
    if(tx == NULL || rx == NULL || len == 0)
        return 0;

    return (HAL_SPI_TransmitReceive(&hspi1, tx, rx, len, 100) == HAL_OK);
}


/* ===================================================== */
/* ================= I2C SECTION (BUGGY) ================ */
/* ===================================================== */

int ai_i2c_write(uint8_t dev, uint8_t reg, uint8_t *data, uint16_t len)
{
    if(data == NULL || len == 0)
        return 0;

    /* ❌ BUG: Wrong device address used (ignoring input 'dev') */
    return (HAL_I2C_Mem_Write(&hi2c1,
                             0x00,   // WRONG ADDRESS
                             reg,
                             I2C_MEMADD_SIZE_8BIT,
                             data,
                             len,
                             100) == HAL_OK);
}

int ai_i2c_read(uint8_t dev, uint8_t reg, uint8_t *data, uint16_t len)
{
    if(data == NULL || len == 0)
        return 0;

    /* ❌ BUG: Wrong device address used (ignoring input 'dev') */
    return (HAL_I2C_Mem_Read(&hi2c1,
                            0x00,   // WRONG ADDRESS
                            reg,
                            I2C_MEMADD_SIZE_8BIT,
                            data,
                            len,
                            100) == HAL_OK);
}