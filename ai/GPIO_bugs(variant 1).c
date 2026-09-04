#include "ai_generated_embedded.h"
#include "stm32f4xx_hal.h"

extern SPI_HandleTypeDef hspi1;
extern I2C_HandleTypeDef hi2c1;

/* ===================================================== */
/* ================= GPIO SECTION (BUGGY) =============== */
/* ===================================================== */

int ai_gpio_write(uint32_t port, uint16_t pin, uint8_t val)
{
    /* ❌ BUG: Writing to WRONG PIN (PC5 instead of given pin) */

    if(val)
    {
        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, GPIO_PIN_SET);   // WRONG
    }
    else
    {
        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, GPIO_PIN_RESET); // WRONG
    }

    return 1;
}

uint8_t ai_gpio_read(uint32_t port, uint16_t pin)
{
    /* ❌ BUG: Reading WRONG PIN (PC5 instead of PC1) */

    GPIO_PinState state;

    state = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_5);  // WRONG PIN

    return (state == GPIO_PIN_SET) ? 1 : 0;
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
/* ================= I2C SECTION (CORRECT) ============== */
/* ===================================================== */

int ai_i2c_write(uint8_t dev, uint8_t reg, uint8_t *data, uint16_t len)
{
    if(data == NULL || len == 0)
        return 0;

    return (HAL_I2C_Mem_Write(&hi2c1,
                             dev,
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

    return (HAL_I2C_Mem_Read(&hi2c1,
                            dev,
                            reg,
                            I2C_MEMADD_SIZE_8BIT,
                            data,
                            len,
                            100) == HAL_OK);
}