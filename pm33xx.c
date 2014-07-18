File Path: linux/arch/arm/mach-omap2/pm33xx.c

 AM33XX Power Management Routines
 
-	struct omap_hwmod *gpmc_oh, *usb_oh, *gpio1_oh;
+	struct omap_hwmod *gpmc_oh, *usb_oh, *gpio1_oh, *rtc_oh;



usb_oh		= omap_hwmod_lookup("usb_otg_hs");
 	gpmc_oh		= omap_hwmod_lookup("gpmc");
 	gpio1_oh	= omap_hwmod_lookup("gpio1");	/* WKUP domain GPIO */
+	rtc_oh		= omap_hwmod_lookup("rtc");

This is called in the pm_suspend function 

static int am33xx_pm_suspend(void)
{
    int state, ret = 0;

    struct omap_hwmod *gpmc_oh, *usb_oh, *gpio1_oh, *rtc_oh;

    usb_oh      = omap_hwmod_lookup("usb_otg_hs");
    gpmc_oh     = omap_hwmod_lookup("gpmc");
    gpio1_oh    = omap_hwmod_lookup("gpio1");   /* WKUP domain GPIO */
    rtc_oh      = omap_hwmod_lookup("rtc");
   ...................................................
   ...................................................
   ...................................................

}





 	/*
+	 * Keep RTC module enabled during standby
+	 * for PG2.x to enable wakeup from RTC.
+	 */
+	if ((omap_rev() >= AM335X_REV_ES2_0) &&
+		(suspend_state == PM_SUSPEND_STANDBY))
+		omap_hwmod_enable(rtc_oh);
+
+	/*




+	am33xx_standby_setup(suspend_state);
+

The above function called in 

static int am33xx_pm_suspend(void)
{

    ..............................................
    ..............................................
    ..............................................
    ..............................................
    
    omap3_intc_suspend();

    am33xx_standby_setup(suspend_state);

    writel(0x0, AM33XX_CM_MPU_MPU_CLKCTRL);

    ret = cpu_suspend(0, am33xx_do_sram_idle);
    ..............................................
    ..............................................
    ..............................................
}




+	/*
+	 * Put RTC module to idle on resume from standby
+	 * for PG2.x.
+	 */
+	if ((omap_rev() >= AM335X_REV_ES2_0) &&
+		(suspend_state == PM_SUSPEND_STANDBY))
+		omap_hwmod_idle(rtc_oh);
+
 	ret = am33xx_verify_lp_state(ret);
 
 
 
 
 
 	reg = omap_rev();
-	if (reg == AM335X_REV_ES2_0)
+	if (reg >= AM335X_REV_ES2_0)
 		
 		
 The condtion is checked in 
 
 
 static int __init am33xx_pm_init(void)
{
    int ret;
#ifdef CONFIG_SUSPEND
    void __iomem *base;
    u32 reg;
    u32 evm_id;
  .............................................
  .............................................
  .............................................
    /* CPU Revision */
    reg = omap_rev();
    if (reg >= AM335X_REV_ES2_0)
        suspend_cfg_param_list[CPU_REV] = CPU_REV_2;
    else
        suspend_cfg_param_list[CPU_REV] = CPU_REV_1;
        
      ...............................................        
      ...............................................
      ...............................................
      
      
}



 
 		
 		
 
 


