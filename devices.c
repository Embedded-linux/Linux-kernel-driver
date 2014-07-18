File name: devices.c
File path: arch/arm/mach-ompa2/devices.c


/* The values below are based upon silicon characterization data.
  * Each OPP and sensor combination potentially has different values.
  * The values of ERR2VOLT_GAIN and ERR_MIN_LIMIT also change based on
- * the PMIC step size.  Values have been given to cover the AM335 EVM
+ * the PMIC step size.	Values have been given to cover the AM335 EVM
  * (12.5mV step) and the Beaglebone (25mV step).  If the step
  * size changes, you should update these values, and don't forget to
  * change the step size in the platform data structure, am33xx_sr_pdata.
  */


+#define AM33XX_SR0_OPP50_CNTRL_OFFSET		0x07B8
+#define AM33XX_SR0_OPP50_EVM_ERR_MIN_LIMIT	0xF0
+#define AM33XX_SR0_OPP50_BB_ERR_MIN_LIMIT	0xEA
+#define AM33XX_SR0_OPP50_ERR_MAX_LIMIT		0x2
+#define AM33XX_SR0_OPP50_ERR_WEIGHT		0x4
+#define AM33XX_SR0_OPP50_MARGIN			0
+
+#define AM33XX_SR0_OPP100_CNTRL_OFFSET		0x07BC
+#define AM33XX_SR0_OPP100_EVM_ERR_MIN_LIMIT	0xF0
+#define AM33XX_SR0_OPP100_BB_ERR_MIN_LIMIT	0xF1
+#define AM33XX_SR0_OPP100_ERR_MAX_LIMIT		0x2
+#define AM33XX_SR0_OPP100_ERR_WEIGHT		0x4
+#define AM33XX_SR0_OPP100_MARGIN		0
+
+#define AM33XX_SR1_OPP50_CNTRL_OFFSET		0x0770
+#define AM33XX_SR1_OPP50_EVM_ERR_MIN_LIMIT	0xFA
+#define AM33XX_SR1_OPP50_BB_ERR_MIN_LIMIT	0xC0
+#define AM33XX_SR1_OPP50_ERR_MAX_LIMIT		0x2
+#define AM33XX_SR1_OPP50_ERR_WEIGHT		0x4
+#define AM33XX_SR1_OPP50_MARGIN			0
+
+
+#define AM33XX_SR1_OPP100_CNTRL_OFFSET		0x0774
+#define AM33XX_SR1_OPP100_EVM_ERR_MIN_LIMIT	0xFB
+#define AM33XX_SR1_OPP100_BB_ERR_MIN_LIMIT	0xDF
+#define AM33XX_SR1_OPP100_ERR_MAX_LIMIT		0x2
+#define AM33XX_SR1_OPP100_ERR_WEIGHT		0x4
+#define AM33XX_SR1_OPP100_MARGIN		0
+
+#define AM33XX_SR1_OPP120_CNTRL_OFFSET		0x0778
+#define AM33XX_SR1_OPP120_EVM_ERR_MIN_LIMIT	0xFC
+#define AM33XX_SR1_OPP120_BB_ERR_MIN_LIMIT	0xE6
+#define AM33XX_SR1_OPP120_ERR_MAX_LIMIT		0x2
+#define AM33XX_SR1_OPP120_ERR_WEIGHT		0x7
+#define AM33XX_SR1_OPP120_MARGIN		0
+
+#define AM33XX_SR1_OPPTURBO_CNTRL_OFFSET	0x077C
+#define AM33XX_SR1_OPPTURBO_EVM_ERR_MIN_LIMIT	0xFD
+#define AM33XX_SR1_OPPTURBO_BB_ERR_MIN_LIMIT	0xEA
+#define AM33XX_SR1_OPPTURBO_ERR_MAX_LIMIT	0x2
+#define AM33XX_SR1_OPPTURBO_ERR_WEIGHT		0x7
+#define AM33XX_SR1_OPPTURBO_MARGIN		0
+#define AM33XX_SR1_OPPTURBO_MARGIN		0
+
+/* bits 31:16 = SenP margin; bit 15:0 = SenN margin */
+
+#define AM33XX_SR1_OPPNITRO_MARGIN		0x018B019A



 /* the voltages and frequencies should probably be defined in opp3xxx_data.c.
    Once SR is integrated to the mainline driver, and voltdm is working
    correctly in AM335x, these can be removed.  */
    
    
+#define AM33XX_VDD_MPU_OPP50_UV			950000
+#define AM33XX_VDD_MPU_OPP100_UV		1100000
+#define AM33XX_VDD_MPU_OPP120_UV		1200000
+#define AM33XX_VDD_MPU_OPPTURBO_UV		1260000
+#define AM33XX_VDD_CORE_OPP50_UV		950000
+#define AM33XX_VDD_CORE_OPP100_UV		1100000
+
+#define AM33XX_VDD_MPU_OPP50_FREQ		275000000
+#define AM33XX_VDD_MPU_OPP100_FREQ		500000000
+#define AM33XX_VDD_MPU_OPP120_FREQ		600000000
+#define AM33XX_VDD_MPU_OPPTURBO_FREQ		720000000
+
+#define AM33XX_ES2_0_VDD_MPU_OPP50_UV		950000
+#define AM33XX_ES2_0_VDD_MPU_OPP100_UV		1100000
+#define AM33XX_ES2_0_VDD_MPU_OPP120_UV		1200000
+#define AM33XX_ES2_0_VDD_MPU_OPPTURBO_UV	1260000
+#define AM33XX_ES2_0_VDD_MPU_OPPNITRO_UV	1320000
+
+#define AM33XX_ES2_0_VDD_MPU_OPP50_FREQ		300000000
+#define AM33XX_ES2_0_VDD_MPU_OPP100_FREQ	600000000
+#define AM33XX_ES2_0_VDD_MPU_OPP120_FREQ	720000000
+#define AM33XX_ES2_0_VDD_MPU_OPPTURBO_FREQ	800000000
+#define AM33XX_ES2_0_VDD_MPU_OPPNITRO_FREQ	1000000000

+static struct am33xx_sr_opp_data sr1_opp_data_2_0[] = {
+	{
+		.efuse_offs	= AM33XX_SR1_OPP50_CNTRL_OFFSET,
+		.e2v_gain	= 0,
+		.err_minlimit	= AM33XX_SR1_OPP50_EVM_ERR_MIN_LIMIT,
+		.err_maxlimit	= AM33XX_SR1_OPP50_ERR_MAX_LIMIT,
+		.err_weight	= AM33XX_SR1_OPP50_ERR_WEIGHT,
+		.margin		= AM33XX_SR1_OPP50_MARGIN,
+		.nominal_volt	= AM33XX_ES2_0_VDD_MPU_OPP50_UV,
+		.frequency	= AM33XX_ES2_0_VDD_MPU_OPP50_FREQ,
+	},
+	{
+		.efuse_offs	= AM33XX_SR1_OPP100_CNTRL_OFFSET,
+		.e2v_gain	= 0,
+		.err_minlimit	= AM33XX_SR1_OPP100_EVM_ERR_MIN_LIMIT,
+		.err_maxlimit	= AM33XX_SR1_OPP100_ERR_MAX_LIMIT,
+		.err_weight	= AM33XX_SR1_OPP100_ERR_WEIGHT,
+		.margin		= AM33XX_SR1_OPP100_MARGIN,
+		.nominal_volt	= AM33XX_ES2_0_VDD_MPU_OPP100_UV,
+		.frequency	= AM33XX_ES2_0_VDD_MPU_OPP100_FREQ,
+	},
+	{
+		.efuse_offs	= AM33XX_SR1_OPP120_CNTRL_OFFSET,
+		.e2v_gain	= 0,
+		.err_minlimit	= AM33XX_SR1_OPP120_EVM_ERR_MIN_LIMIT,
+		.err_maxlimit	= AM33XX_SR1_OPP120_ERR_MAX_LIMIT,
+		.err_weight	= AM33XX_SR1_OPP120_ERR_WEIGHT,
+		.margin		= AM33XX_SR1_OPP120_MARGIN,
+		.nominal_volt	= AM33XX_ES2_0_VDD_MPU_OPP120_UV,
+		.frequency	= AM33XX_ES2_0_VDD_MPU_OPP120_FREQ,
+	},
+	{
+		.efuse_offs     = AM33XX_SR1_OPPTURBO_CNTRL_OFFSET,
+		.e2v_gain       = 0,
+		.err_minlimit   = AM33XX_SR1_OPPTURBO_EVM_ERR_MIN_LIMIT,
+		.err_maxlimit   = AM33XX_SR1_OPPTURBO_ERR_MAX_LIMIT,
+		.err_weight     = AM33XX_SR1_OPPTURBO_ERR_WEIGHT,
+		.margin		= AM33XX_SR1_OPPTURBO_MARGIN,
+		.nominal_volt	= AM33XX_ES2_0_VDD_MPU_OPPTURBO_UV,
+		.frequency	= AM33XX_ES2_0_VDD_MPU_OPPTURBO_FREQ,
+	},
+	{
+		/* NITRO can use the TURBO data, except for margin */
+		.efuse_offs     = AM33XX_SR1_OPPTURBO_CNTRL_OFFSET,
+		.e2v_gain       = 0,
+		.err_minlimit   = AM33XX_SR1_OPPTURBO_EVM_ERR_MIN_LIMIT,
+		.err_maxlimit   = AM33XX_SR1_OPPTURBO_ERR_MAX_LIMIT,
+		.err_weight     = AM33XX_SR1_OPPTURBO_ERR_WEIGHT,
+		.margin		= AM33XX_SR1_OPPNITRO_MARGIN,
+		.nominal_volt	= AM33XX_ES2_0_VDD_MPU_OPPNITRO_UV,
+		.frequency	= AM33XX_ES2_0_VDD_MPU_OPPNITRO_FREQ,
+	},
+};





 static struct am33xx_sr_opp_data sr1_opp_data[] = {
+	{
+		.efuse_offs     = AM33XX_SR1_OPP50_CNTRL_OFFSET,
+		.e2v_gain       = 0,
+		.err_minlimit   = AM33XX_SR1_OPP50_EVM_ERR_MIN_LIMIT,
+		.err_maxlimit   = AM33XX_SR1_OPP50_ERR_MAX_LIMIT,
+		.err_weight     = AM33XX_SR1_OPP50_ERR_WEIGHT,
+		.margin		= AM33XX_SR1_OPP50_MARGIN,
+		.nominal_volt	= AM33XX_VDD_MPU_OPP50_UV,
+		.frequency	= AM33XX_VDD_MPU_OPP50_FREQ,
+	},
+	{
+		.efuse_offs     = AM33XX_SR1_OPP100_CNTRL_OFFSET,
+		.e2v_gain       = 0,
+		.err_minlimit   = AM33XX_SR1_OPP100_EVM_ERR_MIN_LIMIT,
+		.err_maxlimit   = AM33XX_SR1_OPP100_ERR_MAX_LIMIT,
+		.err_weight     = AM33XX_SR1_OPP100_ERR_WEIGHT,
+		.margin		= AM33XX_SR1_OPP100_MARGIN,
+		.nominal_volt	= AM33XX_VDD_MPU_OPP100_UV,
+		.frequency	= AM33XX_VDD_MPU_OPP100_FREQ,
+	},
+	{
+		.efuse_offs	= AM33XX_SR1_OPP120_CNTRL_OFFSET,
+		.e2v_gain       = 0,
+		.err_minlimit   = AM33XX_SR1_OPP120_EVM_ERR_MIN_LIMIT,
+		.err_maxlimit   = AM33XX_SR1_OPP120_ERR_MAX_LIMIT,
+		.err_weight     = AM33XX_SR1_OPP120_ERR_WEIGHT,
+		.margin		= AM33XX_SR1_OPP120_MARGIN,
+		.nominal_volt	= AM33XX_VDD_MPU_OPP120_UV,
+		.frequency	= AM33XX_VDD_MPU_OPP120_FREQ,
+	},
+	{
+		.efuse_offs	= AM33XX_SR1_OPPTURBO_CNTRL_OFFSET,
+		.e2v_gain       = 0,
+		.err_minlimit   = AM33XX_SR1_OPPTURBO_EVM_ERR_MIN_LIMIT,
+		.err_maxlimit   = AM33XX_SR1_OPPTURBO_ERR_MAX_LIMIT,
+		.err_weight     = AM33XX_SR1_OPPTURBO_ERR_WEIGHT,
+		.margin		= AM33XX_SR1_OPPTURBO_MARGIN,
+		.nominal_volt	= AM33XX_VDD_MPU_OPPTURBO_UV,
+		.frequency	= AM33XX_VDD_MPU_OPPTURBO_FREQ,
+	},




 static struct am33xx_sr_opp_data sr1_opp_data[] = {
 
+	{
+		.efuse_offs     = AM33XX_SR0_OPP50_CNTRL_OFFSET,
+		.e2v_gain       = 0,
+		.err_minlimit   = AM33XX_SR0_OPP50_EVM_ERR_MIN_LIMIT,
+		.err_maxlimit   = AM33XX_SR0_OPP50_ERR_MAX_LIMIT,
+		.err_weight     = AM33XX_SR0_OPP50_ERR_WEIGHT,
+		.margin		= AM33XX_SR0_OPP50_MARGIN,
+		.nominal_volt	= AM33XX_VDD_CORE_OPP50_UV,
+	},
+	{
+		.efuse_offs     = AM33XX_SR0_OPP100_CNTRL_OFFSET,
+		.e2v_gain       = 0,
+		.err_minlimit   = AM33XX_SR0_OPP100_EVM_ERR_MIN_LIMIT,
+		.err_maxlimit   = AM33XX_SR0_OPP100_ERR_MAX_LIMIT,
+		.err_weight     = AM33XX_SR0_OPP100_ERR_WEIGHT,
+		.margin		= AM33XX_SR0_OPP100_MARGIN,
+		.nominal_volt	= AM33XX_VDD_CORE_OPP100_UV,
+	},
+};


+
+static struct am33xx_sr_sdata sr_sensor_data_2_0[] = {
+	{
+		.sr_opp_data	= sr0_opp_data,
+		/* note that OPP50 is NOT used in Linux kernel for AM335x */
+		.no_of_opps	= 0x2,
+		.default_opp	= 0x1,
+		.senn_mod       = 0x1,
+		.senp_mod       = 0x1,
+	},
+	{
+		.sr_opp_data    = sr1_opp_data_2_0,
+		/* the opp data below should be determined
+		   dynamically during SR probe */
+		.no_of_opps	= 0x5,
+		.default_opp	= 0x3,
+		.senn_mod       = 0x1,
+		.senp_mod       = 0x1,
+	},
 };


static struct am33xx_sr_sdata sr_sensor_data[] = {

+	{
+		.sr_opp_data	= sr0_opp_data,
+		/* note that OPP50 is NOT used in Linux kernel for AM335x */
+		.no_of_opps	= 0x2,
+		.default_opp	= 0x1,
+		.senn_mod       = 0x1,
+		.senp_mod       = 0x1,
+	},
+	{
+		.sr_opp_data    = sr1_opp_data,
+		/* the opp data below should be determined
+		   dynamically during SR probe */
+		.no_of_opps	= 0x4,
+		.default_opp	= 0x3,
+		.senn_mod       = 0x1,
+		.senp_mod       = 0x1,
+	},
 };
 
 
 
 
 static struct am33xx_sr_platform_data am33xx_sr_pdata = {
+	.vd_name[0]		= "vdd_core",
+	.vd_name[1]		= "vdd_mpu",
+	.ip_type		= 2,
+	.irq_delay		= 1000,
+	.no_of_vds		= 2,
+	.no_of_sens		= ARRAY_SIZE(sr_sensor_data),
+	.vstep_size_uv		= 12500,
+	.enable_on_init		= true,
+	.sr_sdata		= sr_sensor_data,
 };
 


static struct resource am33xx_sr_resources[] = {

-       },
+	{
+		.name   =       "smartreflex0",
+		.start  =       AM33XX_SR0_BASE,
+		.end    =       AM33XX_SR0_BASE + SZ_4K - 1,
+		.flags  =       IORESOURCE_MEM,
+	},
+	{
+		.name   =       "smartreflex0",
+		.start  =       AM33XX_IRQ_SMARTREFLEX0,
+		.end    =       AM33XX_IRQ_SMARTREFLEX0,
+		.flags  =       IORESOURCE_IRQ,
+	},
+	{
+		.name   =       "smartreflex1",
+		.start  =       AM33XX_SR1_BASE,
+		.end    =       AM33XX_SR1_BASE + SZ_4K - 1,
+		.flags  =       IORESOURCE_MEM,
+	},
+	{
+		.name   =       "smartreflex1",
+		.start  =       AM33XX_IRQ_SMARTREFLEX1,
+		.end    =       AM33XX_IRQ_SMARTREFLEX1,
+		.flags  =       IORESOURCE_IRQ,
+	},
};



 /* VCORE for SR regulator init */
 static struct platform_device am33xx_sr_device = {
+	.name	       = "smartreflex",
+	.id	       = -1,
+	.num_resources  = ARRAY_SIZE(am33xx_sr_resources),
+	.resource       = am33xx_sr_resources,
+	.dev = {
+	       .platform_data = &am33xx_sr_pdata,
+	},
 };


 void __init am33xx_sr_init(void)
 {
+	if (omap_rev() != AM335X_REV_ES1_0)
+		am33xx_sr_pdata.sr_sdata = sr_sensor_data_2_0;
+
+	/* For beaglebone, update voltage step size and related parameters
+	   appropriately.  All other AM33XX platforms are good with the
+	   structure defaults as initialized above. */
+	if ((am33xx_evmid == BEAGLE_BONE_OLD) ||
+			(am33xx_evmid == BEAGLE_BONE_A3)) {
+		printk(KERN_ERR "address of pdata = %08x\n",
+			(u32)&am33xx_sr_pdata);
+
+		am33xx_sr_pdata.vstep_size_uv = 25000;
+	}
+
+	if (platform_device_register(&am33xx_sr_device))
+		printk(KERN_ERR "failed to register am33xx_sr device\n");
+	else
+		printk(KERN_INFO "registered am33xx_sr device\n");
 }



+
+void __init am33xx_gpu_init(void)
+{
+	int id = -1;
+	struct platform_device *pdev;
+	struct omap_hwmod *oh;
+	char *oh_name = "gfx";
+	char *dev_name = "pvrsrvkm";
+
+	oh = omap_hwmod_lookup(oh_name);
+	if (!oh) {
+		pr_err("Could not find %s hwmod data\n", oh_name);
+		return;
+	}
+
+	pdev = omap_device_build(dev_name, id, oh, NULL, 0, NULL, 0, 0);
+
+	WARN(IS_ERR(pdev), "could not build omap_device for %s\n", oh_name);
+
+}


Voltage regulator initialization values based on AM335x (Beagle bone).
gpu_init() function.




