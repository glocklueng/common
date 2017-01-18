// Waterloo Hybrid 2016

#include <stdio.h>
#include <string.h>

#include "stm32f0xx_hal.h"

#include "pins_common.h"

UART_HandleTypeDef huart3;

#define UART_BAUD_RATE (230400)
#define DATA_SEND_TIMEOUT (100)

void debug_init() {
    huart3.Instance = USART3;
    huart3.Init.BaudRate = UART_BAUD_RATE;
    huart3.Init.WordLength = UART_WORDLENGTH_8B;
    huart3.Init.StopBits = UART_STOPBITS_1;
    huart3.Init.Parity = UART_PARITY_NONE;
    huart3.Init.Mode = UART_MODE_TX;
    huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart3.Init.OverSampling = UART_OVERSAMPLING_16;
    huart3.Init.OneBitSampling = UART_ONEBIT_SAMPLING_DISABLED;
    huart3.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
    HAL_UART_Init(&huart3);
}

void HAL_UART_MspInit(UART_HandleTypeDef* huart)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    if(huart->Instance==USART3)
    {
        __HAL_RCC_USART3_CLK_ENABLE();

        /**USART3 GPIO Configuration
          PB10    ------> USART3_TX
          PB11    ------> USART3_RX
          */

        GPIO_InitStruct.Pin = UART_RX | UART_TX;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_PULLUP;
        GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
        GPIO_InitStruct.Alternate = GPIO_AF4_USART3;
        HAL_GPIO_Init(UART_PORT, &GPIO_InitStruct);
    }
}

// Function to enable printf for debugging
int _write(int file, char* data, int len) {
    HAL_UART_Transmit(&huart3, (uint8_t*)data, len, DATA_SEND_TIMEOUT);
    return len;
}

