#include "hc06_io.h"
#include "stm32f1xx.h"
#include "stm32f1xx_hal_uart.h"

extern UART_HandleTypeDef *hc06_uart;

hc06_status hc06_io_read(
    uint8_t *const data,
    const uint8_t data_size
)
{
    return (hc06_status)HAL_UART_Receive(
        hc06_uart, data, data_size, HC06_TIMEOUT
    );
}

hc06_status hc06_io_write(
    const uint8_t *const data,
    const uint8_t data_size
)
{
    return (hc06_status)HAL_UART_Transmit(
        hc06_uart, data, data_size, HC06_TIMEOUT
    );
}

hc06_status hc06_io_set_baudrate(const uint32_t baudrate)
{
    // static const uint32_t baudrate_int[] = {
    //     1200, 2400, 4800, 9600, 19200, 38400, 
    //     57600, 115200, 230400, 460800
    // };

    HAL_UART_Abort_IT(hc06_uart);
    HAL_UART_DeInit(hc06_uart);
    hc06_uart->Init.BaudRate = baudrate;

    hc06_status status = HAL_UART_Init(hc06_uart);
    return status;
}