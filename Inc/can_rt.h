#ifndef CAN_RT_H
#define CAN_RT_H

#define CAN_RT_MAX_BYTES_PER_MESSAGE 8
#define CAN_RT_NUM_FILTERS_MAX 28

// CAN setup function, handles bxCAN peripheral setup, filter setup, and GPIO setup for CAN_TX/CAN_RX
// NOTE: TO BE CALLED ONCE IN APPLICATION
int32_t can_rt_setup(const uint16_t *filters, const uint16_t filter_num);

#endif // CAN_RT_H
