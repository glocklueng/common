// Waterloo Hybrid 2016

#include <stdio.h>
#include <string.h>

#include "stm32f0xx_hal.h"

#include "pins_common.h"

UART_HandleTypeDef huart;

#ifdef USE_NUCLEO
#define UART_BAUD_RATE (115200)
#define DATA_SEND_TIMEOUT (100)
#else
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

    GPIO_InitStruct.Pin = UART_RX | UART_TX;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
#ifdef USE_NUCLEO
    GPIO_InitStruct.Alternate = GPIO_AF1_USART2;
#else    
    GPIO_InitStruct.Alternate = GPIO_AF4_USART3;
#endif
    HAL_GPIO_Init(UART_PORT, &GPIO_InitStruct);

#ifdef USE_NUCLEO
    huart.Instance = USART2;
#else
    huart.Instance = USART3;
#endif
    huart.Init.BaudRate = UART_BAUD_RATE;
    huart.Init.WordLength = UART_WORDLENGTH_8B;
    huart.Init.StopBits = UART_STOPBITS_1;
    huart.Init.Parity = UART_PARITY_NONE;
    huart.Init.Mode = UART_MODE_TX_RX;
    huart.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart.Init.OverSampling = UART_OVERSAMPLING_16;
    huart.Init.OneBitSampling = UART_ONEBIT_SAMPLING_DISABLED;
    huart.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
    HAL_UART_Init(&huart);
}

// Function to enable printf for debugging
int _write(int file, char* data, int len) {
    HAL_UART_Transmit(&huart, (uint8_t*)data, len, DATA_SEND_TIMEOUT);
    return len;
}

