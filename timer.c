File Name: timer.c
File Path: linux/arch/arm/mach-omap2/timer.c

OMAP2 GP timer support.



+/**
+  * omap_dm_timer_get_errata - get errata flags for a timer
+  *
+  * Get the timer errata flags that are specific to the OMAP device being used.
+  */
+u32 __init omap_dm_timer_get_errata(void)
+{
+	if (cpu_is_omap24xx())
+		return 0;
+
+	return OMAP_TIMER_ERRATA_I103_I767;
+}
+





static int __init omap_dm_timer_init_one(struct omap_dm_timer *timer,
 						int gptimer_id,
-						const char *fck_source)
+						const char *fck_source,
+						int posted)
 {


    
    ....................................
    ....................................
    ....................................
	timer->posted = 1;
+
+	if (posted)
+		__omap_dm_timer_enable_posted(timer);
+
+	/* Check that the intended posted configuration matches the actual */
+	if (posted != timer->posted)
+		return -EINVAL;
 



static void __init omap2_gp_clockevent_init(int gptimer_id,
                        const char *fck_source)
{
    int res;
    .....................................
    .....................................
    .....................................
+	clkev.errata = omap_dm_timer_get_errata();
+
+	/*
+	 * For clock-event timers we never read the timer counter and
+	 * so we are not impacted by errata i103 and i767. Therefore,
+	 * we can safely ignore this errata for clock-event timers.
+	 */
+	__omap_dm_timer_override_errata(&clkev, OMAP_TIMER_ERRATA_I103_I767);
+
+	res = omap_dm_timer_init_one(&clkev, gptimer_id, fck_source,
+				OMAP_TIMER_POSTED);


    .....................................
    .....................................
    .....................................
}





static void __init omap2_gp_clocksource_init(int gptimer_id,
 {
 	int res;
 

+	clksrc.errata = omap_dm_timer_get_errata();
+
+	res = omap_dm_timer_init_one(&clksrc, gptimer_id, fck_source,
+				OMAP_TIMER_NONPOSTED);
 	BUG_ON(res);

  	pr_info("OMAP clocksource: GPTIMER%d at %lu Hz\n",
 		gptimer_id, clksrc.rate);
 
 	__omap_dm_timer_load_start(&clksrc,
-			OMAP_TIMER_CTRL_ST | OMAP_TIMER_CTRL_AR, 0, 1);
+			OMAP_TIMER_CTRL_ST | OMAP_TIMER_CTRL_AR, 0,
+			OMAP_TIMER_NONPOSTED);
 	init_sched_clock(&cd, dmtimer_update_sched_clock, 32, clksrc.rate);
 
    .....................................
    .....................................
    .....................................
}
   
   
   
   
static int __init omap_timer_init(struct omap_hwmod *oh, void *unused)
 {
    .....................................
    .....................................
    .....................................

 		pdata->reserved = 1;
 
 	pwrdm = omap_hwmod_get_pwrdm(oh);
+	pdata->timer_errata = omap_dm_timer_get_errata();
 	pdata->loses_context = pwrdm_can_ever_lose_context(pwrdm);
 #ifdef CONFIG_PM
 	pdata->get_context_loss_count = omap_pm_get_dev_context_loss_count;
 	  .....................................
    .....................................
    .....................................
  
    }
 	
 	
   

