1.File Name: am335x_evm_defconfig  
  File Path: arch/arm/configs/am335x_evm_defconfig

  The defconfig file used to setup the configuration when building the kernel and it varies based on 
  the platform you are using.

+CONFIG_USB_TI_CPPI41_DMA_HW=y
+# CONFIG_MUSB_PIO_ONLY is not set

+CONFIG_USB_TI_CPPI41_DMA=y



**************************************************************************************


2.File Path: arch/arm/mach-omap2/board-am335xevm.c 

+static void mmc1_emmc_init(int evm_id, int profile)
+{
+	setup_pin_mux(mmc1_common_pin_mux);
+	setup_pin_mux(mmc1_dat4_7_pin_mux);
+
+	am335x_mmc[1].mmc = 2;
+	am335x_mmc[1].caps = MMC_CAP_8_BIT_DATA;
+	am335x_mmc[1].gpio_cd = -EINVAL;
+	am335x_mmc[1].gpio_wp = -EINVAL;
+	am335x_mmc[1].ocr_mask = MMC_VDD_32_33 | MMC_VDD_33_34; /* 3V3 */
+
+	/* mmc will be initialized when mmc0_init is called */
+	return;
+}
+


Above function depends on the intilization of mmc0_init function
          
          
static void mmc0_init(int evm_id, int profile)
{
    switch (evm_id) {
    case BEAGLE_BONE_A3:
    case BEAGLE_BONE_OLD:
    case EVM_SK:
        setup_pin_mux(mmc0_common_pin_mux);
        setup_pin_mux(mmc0_cd_only_pin_mux);
        break;
    default:
        setup_pin_mux(mmc0_common_pin_mux);
        setup_pin_mux(mmc0_cd_only_pin_mux);
        setup_pin_mux(mmc0_wp_only_pin_mux);
        break;
    }

    omap2_hsmmc_init(am335x_mmc);
    return;
}
  
          
**************************************************************************************
     
     
+	if (omap_rev() >= AM335X_REV_ES2_0)     
          
It is called in below function in arch/arm/mach-omap2/board-am335xevm.c

static void am335x_rtc_init(int evm_id, int profile)
{
    void __iomem *base;
    struct clk *clk;
    struct omap_hwmod *oh;
    struct platform_device *pdev;
    char *dev_name = "am33xx-rtc";
      ...........................
      ...........................
      ...........................
      
       if (omap_rev() >= AM335X_REV_ES2_0)
       am335x_rtc_info.wakeup_capable = 1;
       ..........................
       ..........................
       ..........................
}




**************************************************************************************



+static void sgx_init(int evm_id, int profile)
+{
+	if (omap3_has_sgx()) {
+		am33xx_gpu_init();
+	}
+}


  sgx_init function depends on below function for general purpose evm functions.

/* General Purpose EVM */
static struct evm_dev_cfg gen_purp_evm_dev_cfg[] = {
    {am335x_rtc_init, DEV_ON_BASEBOARD, PROFILE_ALL},
    {clkout2_enable, DEV_ON_BASEBOARD, PROFILE_ALL},
    {enable_ecap0,  DEV_ON_DGHTR_BRD, (PROFILE_0 | PROFILE_1 |
                        PROFILE_2 | PROFILE_7) },
    {lcdc_init, DEV_ON_DGHTR_BRD, (PROFILE_0 | PROFILE_1 |
                        PROFILE_2 | PROFILE_7) },
    {mfd_tscadc_init,   DEV_ON_DGHTR_BRD, (PROFILE_0 | PROFILE_1 |
                        PROFILE_2 | PROFILE_7) },
    {rgmii1_init,   DEV_ON_BASEBOARD, PROFILE_ALL},
    {rgmii2_init,   DEV_ON_DGHTR_BRD, (PROFILE_1 | PROFILE_2 |
                        PROFILE_4 | PROFILE_6) },
    {usb0_init, DEV_ON_BASEBOARD, PROFILE_ALL},
    {usb1_init, DEV_ON_BASEBOARD, PROFILE_ALL},
    {evm_nand_init, DEV_ON_DGHTR_BRD,
        (PROFILE_ALL & ~PROFILE_2 & ~PROFILE_3)},
    {i2c1_init,     DEV_ON_DGHTR_BRD, (PROFILE_ALL & ~PROFILE_2)},
    {lis331dlh_init, DEV_ON_DGHTR_BRD, (PROFILE_ALL & ~PROFILE_2)},
    {mcasp1_init,   DEV_ON_DGHTR_BRD, (PROFILE_0 | PROFILE_3 | PROFILE_7)},
    {mmc1_init, DEV_ON_DGHTR_BRD, PROFILE_2},
    {mmc2_wl12xx_init,  DEV_ON_BASEBOARD, (PROFILE_0 | PROFILE_3 |
                                PROFILE_5)},
    {mmc0_init, DEV_ON_BASEBOARD, (PROFILE_ALL & ~PROFILE_5)},
    {mmc0_no_cd_init,   DEV_ON_BASEBOARD, PROFILE_5},
    {spi0_init, DEV_ON_DGHTR_BRD, PROFILE_2},
    {uart1_wl12xx_init, DEV_ON_BASEBOARD, (PROFILE_0 | PROFILE_3 |
                                PROFILE_5)},
    {wl12xx_init,   DEV_ON_BASEBOARD, (PROFILE_0 | PROFILE_3 | PROFILE_5)},
    {d_can_init,    DEV_ON_DGHTR_BRD, PROFILE_1},
    {matrix_keypad_init, DEV_ON_DGHTR_BRD, PROFILE_0},
    {volume_keys_init,  DEV_ON_DGHTR_BRD, PROFILE_0},
    {uart2_init,    DEV_ON_DGHTR_BRD, PROFILE_3},
    {haptics_init,  DEV_ON_DGHTR_BRD, (PROFILE_4)},
    {sgx_init,  DEV_ON_BASEBOARD, PROFILE_ALL},
    {NULL, 0, 0},
};


     
     
     
+	{sgx_init,	DEV_ON_BASEBOARD, PROFILE_NONE},
       
+/* Beaglebone Black */
+static struct evm_dev_cfg beagleboneblack_dev_cfg[] = {
+	{am335x_rtc_init, DEV_ON_BASEBOARD, PROFILE_NONE},
+	{clkout2_enable, DEV_ON_BASEBOARD, PROFILE_NONE},
+	{tps65217_init,	DEV_ON_BASEBOARD, PROFILE_NONE},
+	{mii1_init,	DEV_ON_BASEBOARD, PROFILE_NONE},
+	{usb0_init,	DEV_ON_BASEBOARD, PROFILE_NONE},
+	{usb1_init,	DEV_ON_BASEBOARD, PROFILE_NONE},
+	{mmc1_emmc_init,	DEV_ON_BASEBOARD, PROFILE_NONE},
+	{mmc0_init,	DEV_ON_BASEBOARD, PROFILE_NONE},
+	{i2c2_init,	DEV_ON_BASEBOARD, PROFILE_NONE},
+	{sgx_init,	DEV_ON_BASEBOARD, PROFILE_NONE},


/* EVM - Starter Kit */
static struct evm_dev_cfg evm_sk_dev_cfg[] = {
    {am335x_rtc_init, DEV_ON_BASEBOARD, PROFILE_ALL},
    {mmc1_wl12xx_init,  DEV_ON_BASEBOARD, PROFILE_ALL},
    {mmc0_init, DEV_ON_BASEBOARD, PROFILE_ALL},
    {rgmii1_init,   DEV_ON_BASEBOARD, PROFILE_ALL},
    {rgmii2_init,   DEV_ON_BASEBOARD, PROFILE_ALL},
    {lcdc_init,     DEV_ON_BASEBOARD, PROFILE_ALL},
    {enable_ecap2,     DEV_ON_BASEBOARD, PROFILE_ALL},
    {mfd_tscadc_init,   DEV_ON_BASEBOARD, PROFILE_ALL},
    {gpio_keys_init,  DEV_ON_BASEBOARD, PROFILE_ALL},
    {gpio_led_init,  DEV_ON_BASEBOARD, PROFILE_ALL},
    {lis331dlh_init, DEV_ON_BASEBOARD, PROFILE_ALL},
    {mcasp1_init,   DEV_ON_BASEBOARD, PROFILE_ALL},
    {uart1_wl12xx_init, DEV_ON_BASEBOARD, PROFILE_ALL},
    {wl12xx_init,       DEV_ON_BASEBOARD, PROFILE_ALL},
    {gpio_ddr_vtt_enb_init, DEV_ON_BASEBOARD, PROFILE_ALL},
    {sgx_init,       DEV_ON_BASEBOARD, PROFILE_ALL},
    {NULL, 0, 0},
};


***************************************************************************************
Ensuring physical regulator and setting up the values of regulator

+#define AM33XX_VDD_CORE_OPP50_UV		1100000
+#define AM33XX_OPP120_FREQ		600000000
+#define AM33XX_OPPTURBO_FREQ		720000000
+
+#define AM33XX_ES2_0_VDD_CORE_OPP50_UV	950000
+#define AM33XX_ES2_0_OPP120_FREQ	720000000
+#define AM33XX_ES2_0_OPPTURBO_FREQ	800000000
+#define AM33XX_ES2_0_OPPNITRO_FREQ	1000000000
+
+#define AM33XX_ES2_1_VDD_CORE_OPP50_UV	950000
+#define AM33XX_ES2_1_OPP120_FREQ	720000000
+#define AM33XX_ES2_1_OPPTURBO_FREQ	800000000
+#define AM33XX_ES2_1_OPPNITRO_FREQ	1000000000
+

+static void am335x_opp_update(void)
+{
+	u32 rev;
+	int voltage_uv = 0;
+	struct device *core_dev, *mpu_dev;
+	struct regulator *core_reg;
+
+	core_dev = omap_device_get_by_hwmod_name("l3_main");
+	mpu_dev = omap_device_get_by_hwmod_name("mpu");
+
+	if (!mpu_dev || !core_dev) {
+		pr_err("%s: Aiee.. no mpu/core devices? %p %p\n", __func__,
+		       mpu_dev, core_dev);
+		return;
+	}
+
+	core_reg = regulator_get(core_dev, "vdd_core");
+	if (IS_ERR(core_reg)) {
+		pr_err("%s: unable to get core regulator\n", __func__);
+		return;
+	}+
+	/*
+	 * Ensure physical regulator is present.
+	 * (e.g. could be dummy regulator.)
+	 */
+	voltage_uv = regulator_get_voltage(core_reg);
+	if (voltage_uv < 0) {
+		pr_err("%s: physical regulator not present for core" \
+		       "(%d)\n", __func__, voltage_uv);
+		regulator_put(core_reg);
+		return;
+	}
+
+	pr_debug("%s: core regulator value %d\n", __func__, voltage_uv);
+	if (voltage_uv > 0) {
+		rev = omap_rev();
+		switch (rev) {
+		case AM335X_REV_ES1_0:
+			if (voltage_uv <= AM33XX_VDD_CORE_OPP50_UV) {
+				/*
+				 * disable the higher freqs - we dont care about
+				 * the results
+				 */
+				opp_disable(mpu_dev, AM33XX_OPP120_FREQ);
+				opp_disable(mpu_dev, AM33XX_OPPTURBO_FREQ);
+			}
+			break;
+		case AM335X_REV_ES2_0:
+			if (voltage_uv <= AM33XX_ES2_0_VDD_CORE_OPP50_UV) {
+				/*
+				 * disable the higher freqs - we dont care about
+				 * the results
+				 */
+				opp_disable(mpu_dev,
+					    AM33XX_ES2_0_OPP120_FREQ);
+				opp_disable(mpu_dev,
+					    AM33XX_ES2_0_OPPTURBO_FREQ);
+				opp_disable(mpu_dev,
+					    AM33XX_ES2_0_OPPNITRO_FREQ);
+			}
+			break;
+		case AM335X_REV_ES2_1:
+		/* FALLTHROUGH */
+		default:
+			if (voltage_uv <= AM33XX_ES2_1_VDD_CORE_OPP50_UV) {
+				/*
+				 * disable the higher freqs - we dont care about
+				 * the results
+				 */
+				opp_disable(mpu_dev,
+					    AM33XX_ES2_1_OPP120_FREQ);
+				opp_disable(mpu_dev,
+					    AM33XX_ES2_1_OPPTURBO_FREQ);
+				opp_disable(mpu_dev,
+					    AM33XX_ES2_1_OPPNITRO_FREQ);
+			}
+			break;
+		}
+	}
+}
+


******************************************************************************************

+/* BeagleBone Black */
+static void setup_beagleboneblack(void)
+{
+	pr_info("The board is a AM335x Beaglebone Black.\n");
+
+	/* Beagle Bone has Micro-SD slot which doesn't have Write Protect pin */
+	am335x_mmc[0].gpio_wp = -EINVAL;
+
+	_configure_device(BEAGLE_BONE_BLACK, beagleboneblack_dev_cfg,
+				PROFILE_NONE);
+
+	/* TPS65217 regulator has full constraints */
+	regulator_has_full_constraints();
+
+	am33xx_cpsw_init(AM33XX_CPSW_MODE_MII, NULL, NULL);
+}
+


Configure_device is called to intilize the Beagle bone device and added below

/*
* @evm_id - evm id which needs to be configured
* @dev_cfg - single evm structure which includes
*               all module inits, pin-mux defines
* @profile - if present, else PROFILE_NONE
* @dghtr_brd_flg - Whether Daughter board is present or not
*/
static void _configure_device(int evm_id, struct evm_dev_cfg *dev_cfg,
    int profile)
{
    int i;

    am335x_evm_set_id(evm_id);

    /*
    * Only General Purpose & Industrial Auto Motro Control
    * EVM has profiles. So check if this evm has profile.
    * If not, ignore the profile comparison
    */

    /*
    * If the device is on baseboard, directly configure it. Else (device on
    * Daughter board), check if the daughter card is detected.
    */
    if (profile == PROFILE_NONE) {
        for (i = 0; dev_cfg->device_init != NULL; dev_cfg++) {
            if (dev_cfg->device_on == DEV_ON_BASEBOARD)
                dev_cfg->device_init(evm_id, profile);
            else if (daughter_brd_detected == true)
                dev_cfg->device_init(evm_id, profile);
        }
    } else {
        for (i = 0; dev_cfg->device_init != NULL; dev_cfg++) {
            if (dev_cfg->profile & profile) {
                if (dev_cfg->device_on == DEV_ON_BASEBOARD)
                    dev_cfg->device_init(evm_id, profile);
                else if (daughter_brd_detected == true)
                    dev_cfg->device_init(evm_id, profile);
            }
        }
    }
}




*******************************************************************************************


+	} else if (!strncmp("A335BNLT", config.name, 8)) {
+		setup_beagleboneblack();



setup_beaglebone is defined in am335x_evm_setup function


static void am335x_evm_setup(struct memory_accessor *mem_acc, void *context)
{
    int ret;
    char tmp[10];

    /* 1st get the MAC address from EEPROM */
    ret = mem_acc->read(mem_acc, (char *)&am335x_mac_addr,
        EEPROM_MAC_ADDRESS_OFFSET, sizeof(am335x_mac_addr));

    if (ret != sizeof(am335x_mac_addr)) {
        pr_warning("AM335X: EVM Config read fail: %d\n", ret);
        return;
    }

    /* Fillup global mac id */
    am33xx_cpsw_macidfillup(&am335x_mac_addr[0][0],
                &am335x_mac_addr[1][0]);

    /* get board specific data */
    ret = mem_acc->read(mem_acc, (char *)&config, 0, sizeof(config));
    if (ret != sizeof(config)) {
        pr_err("AM335X EVM config read fail, read %d bytes\n", ret);
        pr_err("This likely means that there either is no/or a failed EEPROM\n");
        goto out;
    }

    if (config.header != AM335X_EEPROM_HEADER) {
        pr_err("AM335X: wrong header 0x%x, expected 0x%x\n",
            config.header, AM335X_EEPROM_HEADER);
        goto out;
    }

    if (strncmp("A335", config.name, 4)) {
        pr_err("Board %s\ndoesn't look like an AM335x board\n",
            config.name);
        goto out;
    }
  snprintf(tmp, sizeof(config.name) + 1, "%s", config.name);
    pr_info("Board name: %s\n", tmp);
    snprintf(tmp, sizeof(config.version) + 1, "%s", config.version);
    pr_info("Board version: %s\n", tmp);

    if (!strncmp("A335BONE", config.name, 8)) {
        daughter_brd_detected = false;
        if(!strncmp("00A1", config.version, 4) ||
           !strncmp("00A2", config.version, 4))
            setup_beaglebone_old();
        else
            setup_beaglebone();
    } else if (!strncmp("A335X_SK", config.name, 8)) {
        daughter_brd_detected = false;
        setup_starterkit();
    } else {
        /* only 6 characters of options string used for now */
        snprintf(tmp, 7, "%s", config.opt);
        pr_info("SKU: %s\n", tmp);

        if (!strncmp("SKU#01", config.opt, 6))
            setup_general_purpose_evm();
        else if (!strncmp("SKU#02", config.opt, 6))
            setup_ind_auto_motor_ctrl_evm();
        else
            goto out;
    }

    am335x_opp_update();

    return;

   ................................................
   ................................................
   ................................................
}



***************************************************************************************

+	am335x_opp_update();
+
+	/*
+	 * For now, Beaglebone Black uses PG 2.0 that are speed binned and operate
+	 * up to 1GHz. So re-enable Turbo and Nitro modes,
+	 */
+	if (!strncmp("A335BNLT", config.name, 8)) {
+		struct device *mpu_dev;
+
+		mpu_dev = omap_device_get_by_hwmod_name("mpu");
+		opp_enable(mpu_dev,
+			    AM33XX_ES2_0_OPPTURBO_FREQ);
+		opp_enable(mpu_dev,
+			    AM33XX_ES2_0_OPPNITRO_FREQ);
+	}
+


It is spefice to Beagle bone black




