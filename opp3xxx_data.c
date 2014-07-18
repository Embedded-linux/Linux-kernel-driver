File Path: arch/arm/mach-omap2/opp3xxx_data.c
File Name: opp3xxx_data.c
 
 
OMAP3 OPP table definitions

#include <linux/module.h>
+#include <linux/io.h>

#define AM33XX_ES2_0_VDD_MPU_OPP100_UV		1100000
+#define AM33XX_ES2_0_VDD_MPU_OPP120_UV		1200000
 #define AM33XX_ES2_0_VDD_MPU_OPPTURBO_UV	1260000
-#define AM33XX_ES2_0_VDD_MPU_OPPNITRO_UV	1320000
+#define AM33XX_ES2_0_VDD_MPU_OPPNITRO_UV	1325000


	/* MPU OPP3 - OPPTurbo */
+	/* MPU OPP3 - OPP120 */
+	OPP_INITIALIZER("mpu", true,  720000000,
+				AM33XX_ES2_0_VDD_MPU_OPP120_UV),
+	/* MPU OPP4 - OPPTurbo */
 	OPP_INITIALIZER("mpu", true, 800000000,
 				AM33XX_ES2_0_VDD_MPU_OPPTURBO_UV),
-	/* MPU OPP4 - OPPNitro */
+	/* MPU OPP5 - OPPNitro */
 	OPP_INITIALIZER("mpu", false, 1000000000,
 				AM33XX_ES2_0_VDD_MPU_OPPNITRO_UV),
 				
 				
 				
+#define AM33XX_ES2_1_VDD_MPU_OPP50_UV		950000
+#define AM33XX_ES2_1_VDD_MPU_OPP100_UV		1100000
+#define AM33XX_ES2_1_VDD_MPU_OPP120_UV		1200000
+#define AM33XX_ES2_1_VDD_MPU_OPPTURBO_UV	1260000
+#define AM33XX_ES2_1_VDD_MPU_OPPNITRO_UV	1325000
+
+#define OPP_50_300_INDEX	0
+#define OPP_100_300_INDEX	1
+#define OPP_100_600_INDEX	2
+#define OPP_120_720_INDEX	3
+#define OPP_TURBO_800_INDEX	4
+#define OPP_NITRO_1GHZ_INDEX	5
+
+/* From AM335x TRM, SPRUH73H, Section 9.3.50 */
+#define AM33XX_EFUSE_SMA_OFFSET	0x7fc
+
+/*
+ * Bits [12:0] are OPP Disabled bits,
+ * 1 = OPP is disabled and not available,
+ * 0 = OPP available.
+ */
+#define MAX_FREQ_MASK		0x1fff
+#define MAX_FREQ_SHFT		0
+
+#define OPP_50_300MHZ_BIT		(0x1 << 4)
+#define OPP_100_300MHZ_BIT		(0x1 << 5)
+#define OPP_100_600MHZ_BIT		(0x1 << 6)
+#define OPP_120_720MHZ_BIT		(0x1 << 7)
+#define OPP_TURBO_800MHZ_BIT		(0x1 << 8)
+#define OPP_NITRO_1GHZ_BIT		(0x1 << 9)
+
+static struct omap_opp_def __initdata am33xx_es2_1_opp_list[] = {
+	/* MPU OPP1 - OPP50-300MHz */
+	OPP_INITIALIZER("mpu", false,  300000000,
+				AM33XX_ES2_1_VDD_MPU_OPP50_UV),
+	/* MPU OPP1 - OPP100-300MHz (used for ZCE) */
+	OPP_INITIALIZER("mpu", false,  300000000,
+				AM33XX_ES2_1_VDD_MPU_OPP100_UV),
+	/* MPU OPP2 - OPP100 */
+	OPP_INITIALIZER("mpu", false,  600000000,
+				AM33XX_ES2_1_VDD_MPU_OPP100_UV),
+	/* MPU OPP3 - OPP120 */
+	OPP_INITIALIZER("mpu", false,  720000000,
+				AM33XX_ES2_1_VDD_MPU_OPP120_UV),
+	/* MPU OPP3 - OPPTurbo */
+	OPP_INITIALIZER("mpu", false, 800000000,
+				AM33XX_ES2_1_VDD_MPU_OPPTURBO_UV),
+	/* MPU OPP4 - OPPNitro */
+	OPP_INITIALIZER("mpu", false, 1000000000,
+				AM33XX_ES2_1_VDD_MPU_OPPNITRO_UV),
+};
+



int __init omap3_opp_init(void)
 {
 	int r = -ENODEV;
+	u32 rev, val, max_freq;




	ARRAY_SIZE(omap36xx_opp_def_list));
 	else if (cpu_is_am33xx()) {
-		if (omap_rev() == AM335X_REV_ES1_0)
+		rev = omap_rev();
+		switch (rev) {
+		case AM335X_REV_ES1_0:
 			r = omap_init_opp_table(am33xx_es1_0_opp_def_list,
 				ARRAY_SIZE(am33xx_es1_0_opp_def_list));
-		else
+			break;
+
+		case AM335X_REV_ES2_1:
+			/*
+			 * First read efuse sma reg to detect package type and
+			 * supported frequency
+			 */
+			val =
+			readl(AM33XX_CTRL_REGADDR(AM33XX_EFUSE_SMA_OFFSET));
+
+			if (!(val & MAX_FREQ_MASK)) {
+				/*
+				* if mpu max freq is not populated, fall back to
+				* PG 2.0 OPP settings.
+				*/
+				r =
+				omap_init_opp_table(am33xx_es2_0_opp_def_list,
+					ARRAY_SIZE(am33xx_es2_0_opp_def_list));
+				break;
+			}
+
+			/*
+			 * 1 = OPP is disabled and not available,
+			 * 0 = OPP available.
+			 */
+			max_freq = (~val & MAX_FREQ_MASK);
+
+			if (max_freq & OPP_50_300MHZ_BIT)
+				am33xx_es2_1_opp_list[OPP_50_300_INDEX].
+					default_available = true;
+
+			if (max_freq & OPP_100_300MHZ_BIT)
+				am33xx_es2_1_opp_list[OPP_100_300_INDEX].
+					default_available = true;
+
+			if (max_freq & OPP_100_600MHZ_BIT)
+				am33xx_es2_1_opp_list[OPP_100_600_INDEX].
+					default_available = true;
+
+			if (max_freq & OPP_120_720MHZ_BIT)
+				am33xx_es2_1_opp_list[OPP_120_720_INDEX].
+					default_available = true;
+
+			if (max_freq & OPP_TURBO_800MHZ_BIT)
+				am33xx_es2_1_opp_list[OPP_TURBO_800_INDEX].
+					default_available = true;
+
+			if (max_freq & OPP_NITRO_1GHZ_BIT)
+				am33xx_es2_1_opp_list[OPP_NITRO_1GHZ_INDEX].
+					default_available = true;
+
+			r = omap_init_opp_table(am33xx_es2_1_opp_list,
+				ARRAY_SIZE(am33xx_es2_1_opp_list));
+			break;
+
+		case AM335X_REV_ES2_0:
+		/* FALLTHROUGH */
+		default:
 			r = omap_init_opp_table(am33xx_es2_0_opp_def_list,
 				ARRAY_SIZE(am33xx_es2_0_opp_def_list));
-	}
-	else
+		}
+	} else {
 		r = omap_init_opp_table(omap34xx_opp_def_list,
 			ARRAY_SIZE(omap34xx_opp_def_list));
+	}
 
 	return r;
 }
















 
 




