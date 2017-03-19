#include <stm32f0xx.h>
#include "stm32f0xx_hal.h"
#include "stdint.h"

#include "pins_common.h"
#include "can_rt.h"
#include "assert.h"
#include "uart.h"

static int32_t can_rt_addfilterids(const uint16_t *filters, const uint16_t filter_num);

int32_t can_rt_setup(const uint16_t *filters, const uint16_t filter_num)
{
    // Assert paramaters
    if(c_assert(filters) || c_assert(filter_num < CAN_RT_NUM_FILTERS_MAX))
    {
        return 1;
    }

    // CAN GPIO Configuration: PB8=CAN_RX, PB9=CAN_TX
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.Pin = GPIO_PIN_8 | GPIO_PIN_9;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF4_CAN;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    // Enable bxCAN peripheral clock
    __CAN_CLK_ENABLE();

    // Reset bxCAN resisters
    CAN->MCR = (uint32_t)0;
    CAN->BTR = (uint32_t)0;

    // Enter bxCAN initialization mode
    CAN->MCR |= CAN_MCR_INRQ;

    // Wait for hardware to enter initialization mode
    while((CAN->MSR & CAN_MSR_INAK) != CAN_MSR_INAK);

    // Exit sleep mode
    CAN->MCR &= ~CAN_MCR_SLEEP;

    // Time Triggered operation disabled
    CAN->MCR &= ~CAN_MCR_TTCM;

    // Automatic Bus-Off Management enabled
    CAN->MCR |= CAN_MCR_ABOM;

    // Auto Wake Up enabled
    CAN->MCR |= CAN_MCR_AWUM;

    // No automatic retransmission disabled (i.e. retransmission enabled, cuz double negative)
    CAN->MCR &= ~CAN_MCR_NART;

    // Receive Fifo Locked Mode disabled, we will lose older mesages in case of overrun
    CAN->MCR &= ~CAN_MCR_RFLM;

    // Transmit FIFO priority = 1, driven by request order (chronologically)
    CAN->MCR |= CAN_MCR_TXFP;

    // Set prescaler and sampling points for 500KHz baud at 48MHz peripheral clock
    CAN->BTR |= 6;

    // Resynchonization Jump Width = 1 Time Quanta (TQ)
    CAN->BTR |= CAN_SJW_1TQ;

    // Bit Segment 1 = 12 TQ
    CAN->BTR |= CAN_BS1_12TQ; 

    // Bit Segment 2 = 3 TQ
    CAN->BTR |= CAN_BS2_3TQ; 
    
    // Set loopback mode for testing, has to be disabled later
    CAN->BTR |= CAN_BTR_LBKM;

    // Switch hardware to normal mode and wait for acknowledge
    CAN->MCR &=~ CAN_MCR_INRQ;

    while ((CAN->MSR & CAN_MSR_INAK) == CAN_MSR_INAK);

    // Add test filter and send packet through mailmox 0
    const uint16_t test_filters[] = {0x575};
    const uint8_t test_packet[] = {0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1};
    if(can_rt_addfilterids(test_filters, 1))
    {
        return 1;
    }

    while((CAN->TSR & CAN_TSR_TME0) != CAN_TSR_TME0);
    
    // Set size of transmission
    CAN->sTxMailBox[0].TDTR = (uint32_t)(8);

    // Put data into mailbox 0
    CAN->sTxMailBox[0].TDLR = (uint32_t)test_packet[0] | (test_packet[1] << 8) | (test_packet[2] << 16) | (test_packet[3] << 24);
    CAN->sTxMailBox[0].TDHR = (uint32_t)test_packet[4] | (test_packet[5] << 8) | (test_packet[6] << 16) | (test_packet[7] << 24);

    // Set the identifier, it's the upper 11 bits, so have to shift left by 21, and request transmission
    CAN->sTxMailBox[0].TIR = (uint32_t)(test_filters[0] << 21 | CAN_TI0R_TXRQ);

    // Wait for FIFO0 to have the received packet
    while((CAN->RF0R & CAN_RF0R_FMP0) == 0);

    // Compare received identitier to what we sent
    if(((CAN->sFIFOMailBox[0].RIR & CAN_RI0R_STID) >> 21) != test_filters[0])
    {
        return 1;
    }

    // Compare received bytes to what we set
    if( CAN->sFIFOMailBox[0].RDLR != ((uint32_t)test_packet[0] | (test_packet[1] << 8) | (test_packet[2] << 16) | (test_packet[3] << 24)) ||
        CAN->sFIFOMailBox[0].RDHR != ((uint32_t)test_packet[4] | (test_packet[5] << 8) | (test_packet[6] << 16) | (test_packet[7] << 24)))
    {
        return 1;
    }

    // Release the fifo message
    CAN->RF0R |= CAN_RF0R_RFOM0;

    // Wait for release
    while(CAN->RF0R | CAN_RF0R_RFOM0);

    // Go to bxCAN init mode again and wait for acknowledge
    CAN->MCR |= CAN_MCR_INRQ;
    while((CAN->MSR & CAN_MSR_INAK) != CAN_MSR_INAK);

    // Disable the loopback mode so we can actulally receive external messages
    CAN->BTR |= CAN_BTR_LBKM;

    // Go to bxCAN normal mode and wait for acknowledge
    CAN->MCR &= CAN_MCR_INRQ;
    while ((CAN->MSR & CAN_MSR_INAK) == CAN_MSR_INAK);

    // Add the filters
    return can_rt_addfilterids(filters, filter_num);
}

static int32_t can_rt_addfilterids(const uint16_t *filters, const uint16_t filter_num)
{
    // Filter index in for-loop
    uint32_t fi = 0;

    // Enter filter initialization mode
    CAN->FMR |= CAN_FMR_FINIT;

    // Deactivate all banks so we can set the filters (FACTx=0). NOTE: don't use CAN_FA1R_FACT, has wrong bits from STM32F4
    CAN->FA1R &= ~(uint32_t)0x3FFF;
    
    // Filter scale for all banks: 4 IDs per bank (FSCx=0). NOTE: don't use CAN_FS1R_FSC
    CAN->FS1R &= ~(uint32_t)0x3FFF;

    // Identifier List Mask for all banks (FBMx=0). NOTE: don't use CAN_FM1R_FBM
    CAN->FM1R &= ~(uint32_t)0x3FFF;

    // All banks use FIFO0 (FFAx=0). NOTE: don't use CAN_FFA1R_FFA
    CAN->FFA1R &= ~(uint32_t)0x3FFF;
    
    // Reset all registers to safe values that will only match IDs of 0
    for(fi = 0; fi < 28; fi++)
    {
        CAN->sFilterRegister[fi].FR1 = (uint32_t)(0xFFFF0000);
        CAN->sFilterRegister[fi].FR2 = (uint32_t)(0xFFFF0000);
    }

    // Add the filters
    for(fi = 0; fi < filter_num; fi++)
    {
        // Calculate bank i [0:27]
        uint32_t i = fi / 2;

        // Calculate bank register x [1:2]
        uint32_t x = fi % 2 + 1;

        // For each filter, set the filter value, and activate the appropriate bank
        // Bits 31:16 are mask
        // Bits 15:0 are ID
        if(x == 1)
        {
            CAN->sFilterRegister[i].FR1 = (uint32_t)(0xFFFF0000 | ((uint32_t)filters[fi] << 5));
        }
        else if(x == 2)
        {
            CAN->sFilterRegister[i].FR2 = (uint32_t)(0xFFFF0000 | ((uint32_t)filters[fi] << 5));
        }
        else
        {
            return 1;
        }

        // Activate bank
        CAN->FA1R |= (uint32_t)(1 << i);
    }
    

    // Exit filter initialization mode
    CAN->FMR &= ~CAN_FMR_FINIT;
    
    return 0;
}

int32_t can_rt_tx(const uint16_t id, const uint8_t *data, const uint8_t length)
{
    return 0;
}

int32_t can_rt_rx(uint8_t *data[CAN_RT_MAX_BYTES_PER_MESSAGE], uint8_t *num_messages)
{
   return 0; 
}
