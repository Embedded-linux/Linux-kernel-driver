File path: drivers/usb/musb/musb_gadget.c
File name: musb_gadget.c

MUSB OTG driver peripheral support

void musb_g_rx(struct musb *musb, u8 epnum)
 	}
 
 	if (dma && (csr & MUSB_RXCSR_DMAENAB)) {
-		csr &= ~(MUSB_RXCSR_AUTOCLEAR
-				| MUSB_RXCSR_DMAENAB
-				| MUSB_RXCSR_DMAMODE);
 		musb_writew(epio, MUSB_RXCSR,
 			MUSB_RXCSR_P_WZC_BITS | csr);
 			
 			
 	This function is defined in 
 	
 	/*
 * Data ready for a request; called from IRQ
 */
void musb_g_rx(struct musb *musb, u8 epnum)
{
    u16         csr;
    struct musb_request *req;
    struct usb_request  *request;
    void __iomem        *mbase = musb->mregs;
    struct musb_ep      *musb_ep;
    void __iomem        *epio = musb->endpoints[epnum].regs;
    struct dma_channel  *dma;
    struct musb_hw_ep   *hw_ep = &musb->endpoints[epnum];

    if (hw_ep->is_shared_fifo)
        musb_ep = &hw_ep->ep_in;
    else
        musb_ep = &hw_ep->ep_out;

    musb_ep_select(musb, mbase, epnum);

    req = next_request(musb_ep);
    if (!req)
        return;

    request = &req->request;

    csr = musb_readw(epio, MUSB_RXCSR);
    dma = is_dma_capable() ? musb_ep->dma : NULL;

    dev_dbg(musb->controller, "<== %s, rxcsr %04x%s %p\n", musb_ep->end_point.name,
            csr, dma ? " (dma)" : "", request);

    if (csr & MUSB_RXCSR_P_SENTSTALL) {
        csr |= MUSB_RXCSR_P_WZC_BITS;
        csr &= ~MUSB_RXCSR_P_SENTSTALL;
        musb_writew(epio, MUSB_RXCSR, csr);
        return;
    }

  ..........................................................
  ..........................................................
  ..........................................................
}


  
  
  
  
  
