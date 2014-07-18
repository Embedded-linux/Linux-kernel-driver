File Name:dmtimer.h
File path:linux/arch/arm/plat-omap/include/plat/dmtimer.h  


OMAP Dual-Mode Timers header file

+/* posted mode types */
+#define OMAP_TIMER_NONPOSTED			0x00
+#define OMAP_TIMER_POSTED			0x01
+



/*
 * timer errata flags
 *
 * Errata i103/i767 impacts all OMAP3/4/5 devices including AM33xx. This
 * errata prevents us from using posted mode on these devices, unless the
 * timer counter register is never read. For more details please refer to
 * the OMAP3/4/5 errata documents.
 */
#define OMAP_TIMER_ERRATA_I103_I767         0x80000000


struct dmtimer_platform_data {
 	int (*set_timer_src)(struct platform_device *pdev, int source);
 	int timer_ip_version;
+	u32 timer_errata;
 	u32 needs_manual_reset:1;
 	bool reserved;
 	
 	
 	
 	
 	
 	struct omap_dm_timer {
 	bool loses_context;
 	int ctx_loss_count;
 	int revision;
+	u32 errata;
 	struct platform_device *pdev;
 	struct list_head node;
 	
 	
 	
 	
-	/* Match hardware reset default of posted mode */
+}
+
+/*
+ * __omap_dm_timer_enable_posted - enables write posted mode
+ * @timer:      pointer to timer instance handle
+ *
+ * Enables the write posted mode for the timer. When posted mode is enabled
+ * writes to certain timer registers are immediately acknowledged by the
+ * internal bus and hence prevents stalling the CPU waiting for the write to
+ * complete. Enabling this feature can improve performance for writing to the
+ * timer registers.
+ */
+static inline void __omap_dm_timer_enable_posted(struct omap_dm_timer *timer)
+{
+	if (timer->posted)
+		return;
+
+	if (timer->errata & OMAP_TIMER_ERRATA_I103_I767)
+		return;
+
 	__omap_dm_timer_write(timer, OMAP_TIMER_IF_CTRL_REG,
-					OMAP_TIMER_CTRL_POSTED, 0);
+			OMAP_TIMER_CTRL_POSTED, 0);
+	timer->context.tsicr = OMAP_TIMER_CTRL_POSTED;
+	timer->posted = OMAP_TIMER_POSTED;
 }
 



+/**
+ * __omap_dm_timer_override_errata - override errata flags for a timer
+ * @timer:      pointer to timer handle
+ * @errata:    errata flags to be ignored
+ *
+ * For a given timer, override a timer errata by clearing the flags
+ * specified by the errata argument. A specific erratum should only be
+ * overridden for a timer if the timer is used in such a way the erratum
+ * has no impact.
+ */
+static inline void __omap_dm_timer_override_errata(struct omap_dm_timer *timer,
+		u32 errata)
+{
+       timer->errata &= ~errata;
+}
+
+

