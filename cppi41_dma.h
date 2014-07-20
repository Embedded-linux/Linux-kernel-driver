File path: drivers/usb/musb/cppi41_dma.h
File name: cppi41_dma.h

cppi41_dma definitions 


u8 bd_intr_ctrl;
 	u8 rx_dma_mode;
 	u8 rx_inf_mode;
+	u8 sched_tbl_ctrl;
 	u32 version;
 };
 
 
 This structure is defined in 
 
 /**
 * struct usb_cppi41_info - CPPI 4.1 USB implementation details
 * @dma_block:  DMA block number
 * @ep_dma_ch:  DMA channel numbers used for EPs 1 .. Max_EP
 * @q_mgr:  queue manager number
 * @num_tx_comp_q: number of the Tx completion queues
 * @num_rx_comp_q: number of the Rx queues
 * @tx_comp_q:  pointer to the list of the Tx completion queue numbers
 * @rx_comp_q:  pointer to the list of the Rx queue numbers
 */
struct usb_cppi41_info {
    u8 dma_block;
    u8 ep_dma_ch[USB_CPPI41_NUM_CH];
    u8 q_mgr;
    u8 num_tx_comp_q;
    u8 num_rx_comp_q;
    u16 *tx_comp_q;
    u16 *rx_comp_q;
    u8 bd_intr_ctrl;
    u8 rx_dma_mode;
    u8 rx_inf_mode;
    u8 sched_tbl_ctrl;
    u32 version;
};
