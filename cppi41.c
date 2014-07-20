File path: drivers/usb/musb/cppi41.c
File name: cppi41.c

 CPPI 4.1 support

+struct cppi41_dma_sched_tbl_t dma_sched_tbl[MAX_SCHED_TBL_ENTRY];


int cppi41_dma_block_init(u8 dma_num, u8 q_mgr, u8 num_order,
 	 */
 	cppi41_init_teardown_queue(dma_num);
 
+	for (i = 0; i < MAX_SCHED_TBL_ENTRY; i += 2) {
+		dma_sched_tbl[i].pos = i;
+		dma_sched_tbl[i].dma_ch = i;
+		dma_sched_tbl[i].is_tx = 1;
+		dma_sched_tbl[i].enb = 1;
+
+		dma_sched_tbl[i+1].pos = i + 1;
+		dma_sched_tbl[i+1].dma_ch = i;
+		dma_sched_tbl[i+1].is_tx = 0;
+		dma_sched_tbl[i+1].enb = 1;
+	}
+
 	/* Initialize the DMA scheduler. */
 	num_reg = (tbl_size + 3) / 4;
 	for (i = 0; i < num_reg; i++) {
 	
 	This Function is called in 
 	
 	int cppi41_dma_block_init(u8 dma_num, u8 q_mgr, u8 num_order,
                 u32 *sched_tbl, u8 tbl_size)
{
    const struct cppi41_dma_block *dma_block;
    unsigned num_desc, num_reg;
    void *ptr;
    int error, i;
    u16 q_num;
    u32 val;

    if (dma_num >= cppi41_num_dma_block ||
        q_mgr >= cppi41_num_queue_mgr ||
        !tbl_size || sched_tbl == NULL)
        return -EINVAL;

    error = cppi41_queue_alloc(CPPI41_FREE_DESC_QUEUE |
                   CPPI41_UNASSIGNED_QUEUE, q_mgr, &q_num);
    if (error) {
        printk(KERN_ERR "ERROR: %s: Unable to allocate teardown "
               "descriptor queue.\n", __func__);
        return error;
    }
    DBG("Teardown descriptor queue %d in queue manager 0 "
        "allocated\n", q_num);

    /*
     * Tell the hardware about the Teardown descriptor
     * queue manager and queue number.
     */
    dma_block = &cppi41_dma_block[dma_num];
    cppi_writel((q_mgr << DMA_TD_DESC_QMGR_SHIFT) |
             (q_num << DMA_TD_DESC_QNUM_SHIFT),
             dma_block->global_ctrl_base +
             DMA_TEARDOWN_FREE_DESC_CTRL_REG);
    DBG("Teardown free descriptor control @ %p, value: %x\n",
        dma_block->global_ctrl_base + DMA_TEARDOWN_FREE_DESC_CTRL_REG,
        cppi_readl(dma_block->global_ctrl_base +
            DMA_TEARDOWN_FREE_DESC_CTRL_REG));

    num_desc = 1 << num_order;
    dma_teardown[dma_num].rgn_size = num_desc *
                     sizeof(struct cppi41_teardown_desc);

    /* Pre-allocate teardown descriptors. */

 	  ..................................................
 	  .................................................. 
 	  ..................................................
}







 	
