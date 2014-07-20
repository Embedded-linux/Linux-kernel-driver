File path: drivers/usb/musb/cppi41_dma.c
File name: cppi41_dma.c

This file implements a DMA interface using TI's CPPI 4.1 DMA.

static unsigned cppi41_next_rx_segment(struct cppi41_channel *rx_ch)
 	u8 en_bd_intr = cppi->en_bd_intr;
 	u8 dma_mode, autoreq;
 	u8 rx_dma_mode = cppi->cppi_info->rx_dma_mode;
-
+	u8 sched_tbl_ctrl = cppi->cppi_info->sched_tbl_ctrl;
 
 	pkt_len = rx_ch->length;
 	
 	
 	
	/* enable schedular if not enabled */
-	if (is_peripheral_active(cppi->musb) && (n_bd > 0))
-		cppi41_schedtbl_add_dma_ch(0, 0, rx_ch->ch_num, 0);
+	if (sched_tbl_ctrl && is_peripheral_active(cppi->musb) && (n_bd > 0))
+		cppi41_schedtbl_add_dma_ch(0, 0,
+			cppi->cppi_info->ep_dma_ch[rx_ch->ch_num], 0);



/**
 * cppi41_next_rx_segment - DMA read for the next chunk of a buffer
 * @rx_ch:  Rx channel
 *
 * Context: controller IRQ-locked
 *
 * NOTE: In the transparent mode, we have to queue one packet at a time since:
 *   - we must avoid starting reception of another packet after receiving
 *     a short packet;
 *   - in host mode we have to set ReqPkt bit in the endpoint's RXCSR after
 *     receiving each packet but the last one... ugly!
 */
static unsigned cppi41_next_rx_segment(struct cppi41_channel *rx_ch)
{
    struct cppi41 *cppi = rx_ch->channel.private_data;
    struct musb *musb = cppi->musb;
    struct usb_pkt_desc *curr_pd;
    struct cppi41_host_pkt_desc *hw_desc;
    u32 length = rx_ch->length - rx_ch->curr_offset;
    u32 pkt_size = rx_ch->pkt_size;
    u32 max_rx_transfer_size = MAX_GRNDIS_PKTSIZE;
    u32 i, n_bd , pkt_len;
    u8 en_bd_intr = cppi->en_bd_intr;
    u8 dma_mode, autoreq;
    u8 rx_dma_mode = cppi->cppi_info->rx_dma_mode;
    u8 sched_tbl_ctrl = cppi->cppi_info->sched_tbl_ctrl;

    pkt_len = rx_ch->length;
    /*
     * Rx can use the generic RNDIS mode where we can
     * probably fit this transfer in one PD and one IRQ
     * (or two with a short packet).
     */
    dma_mode = USB_TRANSPARENT_MODE;
    autoreq = USB_AUTOREQ_ALL_BUT_EOP;

    if (is_peripheral_enabled(cppi->musb))
        rx_dma_mode = USB_TRANSPARENT_MODE;


   .........................................................
   .........................................................
   .........................................................
}



   
      ****************************************************************************
      
  static void usb_process_rx_bd(struct cppi41 *cppi,
 	u8 ch_num, ep_num;
 	struct musb *musb = cppi->musb;
 	u32 length = 0, orig_buf_len;
+	u8 sched_tbl_ctrl = cppi->cppi_info->sched_tbl_ctrl;

 	/* Extract the data from received packet descriptor */
 	length = curr_pd->hw_desc.desc_info & CPPI41_PKT_LEN_MASK;


	curr_pd->eop = 0;
 		/* disable the rx dma schedular */
-		if (is_peripheral_active(cppi->musb) &&
+		if (sched_tbl_ctrl && is_peripheral_active(cppi->musb) &&
 			!cppi->cppi_info->rx_inf_mode)
-			cppi41_schedtbl_remove_dma_ch(0, 0, ch_num, 0);
+			cppi41_schedtbl_remove_dma_ch(0, 0,
+				cppi->cppi_info->ep_dma_ch[ch_num], 0);
 	}


The above function is called in 


static void usb_process_rx_bd(struct cppi41 *cppi,
        struct usb_pkt_desc *curr_pd)
{
    u8 en_bd_intr = cppi->en_bd_intr;
    struct cppi41_channel *rx_ch;
    u8 ch_num, ep_num;
    struct musb *musb = cppi->musb;
    u32 length = 0, orig_buf_len;
    u8 sched_tbl_ctrl = cppi->cppi_info->sched_tbl_ctrl;

    /* Extract the data from received packet descriptor */
    length = curr_pd->hw_desc.desc_info & CPPI41_PKT_LEN_MASK;
    ch_num = curr_pd->ch_num;
    ep_num = curr_pd->ep_num;

    /* the cppi41 dma will set received byte length as 1 when
     * zero length packet is received, fix this dummy byte by
     * setting acutal length received as zero
     */
    if (curr_pd->hw_desc.pkt_info & CPPI41_ZLP)
        length = 0;

    rx_ch = &cppi->rx_cppi_ch[ch_num];
    dev_dbg(musb->controller, "Rx complete: dma channel(%d) ep%d len %d\n",
        ch_num, ep_num, length);

    rx_ch->channel.actual_len += length;

    if (curr_pd->eop) {
        curr_pd->eop = 0;
        /* disable the rx dma schedular */
        if (sched_tbl_ctrl && is_peripheral_active(cppi->musb) &&
            !cppi->cppi_info->rx_inf_mode)
            cppi41_schedtbl_remove_dma_ch(0, 0,
                cppi->cppi_info->ep_dma_ch[ch_num], 0);
    }

    /*
     * Return Rx PD to the software list --
     * this is protected by critical section
     */


  .....................................................................
  .....................................................................
  .....................................................................
}
  
  
  
  
  


   
   
