File path: drivers/usb/musb/ti81xx.c
File name: ti81xx.c

 Texas Instruments TI81XX "usb platform glue layer"
 
 
 int __devinit cppi41_init(u8 id, u8 irq, int num_instances)
 	cppi_info->tx_comp_q = id ? tx_comp_q1 : tx_comp_q;
 	cppi_info->rx_comp_q = id ? rx_comp_q1 : rx_comp_q;
 	cppi_info->bd_intr_ctrl = 1;
+	cppi_info->sched_tbl_ctrl = 0;
 	cppi_info->version = usbss_read(USBSS_REVISION);
 
 	if (cppi41_init_done)



This Function is called in 

int __devinit cppi41_init(u8 id, u8 irq, int num_instances)
{
    struct usb_cppi41_info *cppi_info = &usb_cppi41_info[id];
    u16 numch, blknum, order;
    u32 i;

    /* init cppi info structure  */
    cppi_info->dma_block = 0;
    for (i = 0 ; i < USB_CPPI41_NUM_CH ; i++)
        cppi_info->ep_dma_ch[i] = i + (15 * id);

    cppi_info->q_mgr = 0;
    cppi_info->num_tx_comp_q = 15;
    cppi_info->num_rx_comp_q = 15;
    cppi_info->tx_comp_q = id ? tx_comp_q1 : tx_comp_q;
    cppi_info->rx_comp_q = id ? rx_comp_q1 : rx_comp_q;
    cppi_info->bd_intr_ctrl = 1;
    cppi_info->sched_tbl_ctrl = 0;
    cppi_info->version = usbss_read(USBSS_REVISION);

    if (cppi41_init_done)
        return 0;

    blknum = cppi_info->dma_block;

    /* Queue manager information */
    cppi41_queue_mgr[0].num_queue = 159;
    cppi41_queue_mgr[0].queue_types = CPPI41_FREE_DESC_BUF_QUEUE |
                        CPPI41_UNASSIGNED_QUEUE;
    cppi41_queue_mgr[0].base_fdbq_num = 0;
    cppi41_queue_mgr[0].assigned = assigned_queues;

    /* init DMA block */
    cppi41_dma_block[0].num_tx_ch = 30;
    cppi41_dma_block[0].num_rx_ch = 30;
    cppi41_dma_block[0].tx_ch_info = tx_ch_info;

    /* initilize cppi41 dma & Qmgr address */
    ...........................................................
    ...........................................................
    ...........................................................
}


