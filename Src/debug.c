// Waterloo Hybrid 2016

#include <stdio.h>
#include <string.h>

#include "stm32f0xx_hal.h"

#include "pins_common.h"

#ifdef USE_NUCLEO
UART_HandleTypeDef huart2;
#define UART_BAUD_RATE (115200)
#define DATA_SEND_TIMEOUT (100)
#else
UART_HandleTypeDef huart3;
#define UART_BAUD_RATE (460800)
#define DATA_SEND_TIMEOUT (100)
#endif


void debug_init(void) {
    /* Initialize the GPIO pins in UART alternate function
     * Note: This needs to be done before initializing the UART peripheral
     */
    GPIO_InitTypeDef GPIO_InitStruct;
#ifdef USE_NUCLEO
    __HAL_RCC_USART2_CLK_ENABLE();
#else
    __HAL_RCC_USART3_CLK_ENABLE();
#endif

    /* (nucleo) USART2 GPIO config:
     PA2 -> USART2_TX
     PA3 -> USART2_RX
     */

    /** (procboard) USART3 GPIO Configuration
      PB10    ------> USART3_TX
      PB11    ------> USART3_RX
      */

#ifdef USE_NUCLEO
    GPIO_InitStruct.Pin = GPIO_PIN_2 | GPIO_PIN_3;
#else
    GPIO_InitStruct.Pin = UART_RX | UART_TX;
#endif
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
#ifdef USE_NUCLEO
    GPIO_InitStruct.Alternate = GPIO_AF1_USART2;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
#else    
    GPIO_InitStruct.Alternate = GPIO_AF4_USART3;
    HAL_GPIO_Init(UART_PORT, &GPIO_InitStruct);
#endif

#ifdef USE_NUCLEO
    huart2.Instance = USART2;
    huart2.Init.BaudRate = UART_BAUD_RATE;
    huart2.Init.WordLength = UART_WORDLENGTH_8B;
    huart2.Init.StopBits = UART_STOPBITS_1;
    huart2.Init.Parity = UART_PARITY_NONE;
    huart2.Init.Mode = UART_MODE_TX_RX;
    huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart2.Init.OverSampling = UART_OVERSAMPLING_16;
    huart2.Init.OneBitSampling = UART_ONEBIT_SAMPLING_DISABLED;
    huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
    HAL_UART_Init(&huart2);
#else
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
#endif
}

// Function to enable printf for debugging
int _write(int file, char* data, int len) {
#ifdef USE_NUCLEO
    HAL_UART_Transmit(&huart2, (uint8_t*)data, len, DATA_SEND_TIMEOUT);
#else
    HAL_UART_Transmit(&huart3, (uint8_t*)data, len, DATA_SEND_TIMEOUT);
#endif
    return len;
}

