File Name: dmtimer.c
File Path: linux/arch/arm/plat-omap/dmtimer.c

OMAP Dual-Mode Timers


static void omap_dm_timer_reset(struct omap_dm_timer *timer)
 {
-	omap_dm_timer_enable(timer);
 	if (timer->pdev->id != 1) {
 		omap_dm_timer_write_reg(timer, OMAP_TIMER_IF_CTRL_REG, 0x06);
 		omap_dm_timer_wait_for_reset(timer);
 	}
 
 	__omap_dm_timer_reset(timer, 0, 0);
-	omap_dm_timer_disable(timer);
-	timer->posted = 1;
 }
 
 
 
 
int omap_dm_timer_prepare(struct omap_dm_timer *timer)
 {
 	struct dmtimer_platform_data *pdata = timer->pdev->dev.platform_data;
 
+	omap_dm_timer_enable(timer);
+

 timer->fclk = clk_get(&timer->pdev->dev, "fck");
    if (WARN_ON_ONCE(IS_ERR_OR_NULL(timer->fclk))) {
        timer->fclk = NULL;
        dev_err(&timer->pdev->dev, ": No fclk handle.\n");
        return -EINVAL;
    }
   ............................................
   ............................................
   ............................................
}
   
   
   
   
   
if (pdata->needs_manual_reset)
 		omap_dm_timer_reset(timer);
 
-	timer->posted = 1;
+	__omap_dm_timer_enable_posted(timer);
+	omap_dm_timer_disable(timer);
 	return 0;
 }
 

This function is called in omap_dm_timer_prepare function

 
 int omap_dm_timer_prepare(struct omap_dm_timer *timer)
{
    struct dmtimer_platform_data *pdata = timer->pdev->dev.platform_data;

    omap_dm_timer_enable(timer);

    timer->fclk = clk_get(&timer->pdev->dev, "fck");
    if (WARN_ON_ONCE(IS_ERR_OR_NULL(timer->fclk))) {
        timer->fclk = NULL;
        dev_err(&timer->pdev->dev, ": No fclk handle.\n");
        return -EINVAL;
    }

    if (pdata->needs_manual_reset)
        omap_dm_timer_reset(timer);

    __omap_dm_timer_enable_posted(timer);
    omap_dm_timer_disable(timer);
    return 0;
}

   
  
/**
 * omap_dm_timer_probe - probe function called for every registered device
 * @pdev:   pointer to current timer platform device
 *
 * Called by driver framework at the end of device registration for all
 * timer devices.
 */
static int __devinit omap_dm_timer_probe(struct platform_device *pdev)
{
    int ret;
    unsigned long flags;
    struct omap_dm_timer *timer;
    struct resource *mem, *irq, *ioarea;
    struct dmtimer_platform_data *pdata = pdev->dev.platform_data;

    if (!pdata) {
        dev_err(&pdev->dev, "%s: no platform data.\n", __func__);
        return -ENODEV;
    }
  
   .............................................   
   .............................................
   .............................................
 	timer->id = pdev->id;
+	timer->errata = pdata->timer_errata;
 	timer->irq = irq->start;
  .............................................   
  .............................................
  .............................................
};




  
  
