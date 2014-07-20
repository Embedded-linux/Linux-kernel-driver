File path:drivers/staging/iio/adc/ti_adc.c
File name: ti_adc.c

 TI ADC MFD driver
 
 
 
 static ssize_t tiadc_set_mode(struct device *dev,
 {
 	struct iio_dev *indio_dev = dev_get_drvdata(dev);
 	struct adc_device *adc_dev = iio_priv(indio_dev);
 	
 	............................................
 	............................................
 	............................................

+	unsigned int config;
 
 	config = adc_readl(adc_dev, TSCADC_REG_CTRL);
 	config &= ~(TSCADC_CNTRLREG_TSCSSENB);
 	adc_writel(adc_dev, TSCADC_REG_CTRL, config);
 	............................................
 	............................................
 	............................................
 	
+	if (!strncmp(buf, "oneshot", 7))
+		adc_dev->is_continuous_mode = false;
+	else if (!strncmp(buf, "continuous", 10))
+		adc_dev->is_continuous_mode = true;
+	else {
+		dev_err(dev, "Operational mode unknown\n");
+		return -EINVAL;
 	}
 
+	adc_step_config(adc_dev, adc_dev->is_continuous_mode);
+
 	}
 	
 	
 	
 Setting mode of TI_ADC is defined in below function
 static ssize_t tiadc_set_mode(struct device *dev,
        struct device_attribute *attr, const char *buf, size_t count)
{
    struct iio_dev *indio_dev = dev_get_drvdata(dev);
    struct adc_device *adc_dev = iio_priv(indio_dev);
    unsigned int config;

    config = adc_readl(adc_dev, TSCADC_REG_CTRL);
    config &= ~(TSCADC_CNTRLREG_TSCSSENB);
    adc_writel(adc_dev, TSCADC_REG_CTRL, config);

    if (!strncmp(buf, "oneshot", 7))
        adc_dev->is_continuous_mode = false;
    else if (!strncmp(buf, "continuous", 10))
        adc_dev->is_continuous_mode = true;
    else {
        dev_err(dev, "Operational mode unknown\n");
        return -EINVAL;
    }

    adc_step_config(adc_dev, adc_dev->is_continuous_mode);

    config = adc_readl(adc_dev, TSCADC_REG_CTRL);
    adc_writel(adc_dev, TSCADC_REG_CTRL,
            (config | TSCADC_CNTRLREG_TSCSSENB));
    return count;
}



 	
****************************************************************** 	

+	if (status & TSCADC_IRQENB_FIFO1OVRRUN) {
+		config = adc_readl(adc_dev, TSCADC_REG_CTRL);
+		config &= ~(TSCADC_CNTRLREG_TSCSSENB);
+		adc_writel(adc_dev, TSCADC_REG_CTRL, config);
+
+		adc_writel(adc_dev, TSCADC_REG_IRQSTATUS,
+				TSCADC_IRQENB_FIFO1OVRRUN |
+				TSCADC_IRQENB_FIFO1UNDRFLW |
+				TSCADC_IRQENB_FIFO1THRES);
+
+		adc_writel(adc_dev, TSCADC_REG_CTRL,
+			(config | TSCADC_CNTRLREG_TSCSSENB));
+		return IRQ_HANDLED;
+	} else if (status & TSCADC_IRQENB_FIFO1THRES) {
 		adc_writel(adc_dev, TSCADC_REG_IRQCLR,
 				TSCADC_IRQENB_FIFO1THRES);
 


The above function is called in  which checks irq handler of tiadc_irq

static irqreturn_t tiadc_irq(int irq, void *private)
{
    struct iio_dev *idev = private;
    struct adc_device *adc_dev = iio_priv(idev);
    unsigned int status, config;

    status = adc_readl(adc_dev, TSCADC_REG_IRQSTATUS);
    if (status & TSCADC_IRQENB_FIFO1OVRRUN) {
        config = adc_readl(adc_dev, TSCADC_REG_CTRL);
        config &= ~(TSCADC_CNTRLREG_TSCSSENB);
        adc_writel(adc_dev, TSCADC_REG_CTRL, config);

        adc_writel(adc_dev, TSCADC_REG_IRQSTATUS,
                TSCADC_IRQENB_FIFO1OVRRUN |
                TSCADC_IRQENB_FIFO1UNDRFLW |
                TSCADC_IRQENB_FIFO1THRES);

        adc_writel(adc_dev, TSCADC_REG_CTRL,
            (config | TSCADC_CNTRLREG_TSCSSENB));
        return IRQ_HANDLED;
    } else if (status & TSCADC_IRQENB_FIFO1THRES) {
        adc_writel(adc_dev, TSCADC_REG_IRQCLR,
                TSCADC_IRQENB_FIFO1THRES);

        if (iio_buffer_enabled(idev)) {
            if (!work_pending(&adc_dev->poll_work))
                schedule_work(&adc_dev->poll_work);
        } else {
            wake_up_interruptible(&adc_dev->wq_data_avail);
        }
        return IRQ_HANDLED;
    } else {
        return IRQ_NONE;
    }
}


*****************************************************************************


static void tiadc_poll_handler(struct work_struct *work_s)
 		container_of(work_s, struct adc_device, poll_work);
 	struct iio_dev *idev = iio_priv_to_dev(adc_dev);
 	struct iio_buffer *buffer = idev->buffer;
-	unsigned int fifo1count, readx1, status;
+	unsigned int fifo1count, readx1;
 	int i;
 	u32 *iBuf;
 
 	fifo1count = adc_readl(adc_dev, TSCADC_REG_FIFO1CNT);
-	iBuf = kmalloc((fifo1count + 1) * sizeof(u32), GFP_KERNEL);
-	if (iBuf == NULL)
-		return;
+	if (fifo1count * sizeof(u32) <
+				buffer->access->get_bytes_per_datum(buffer)) {
+		dev_err(adc_dev->mfd_tscadc->dev, "%s: Short FIFO event\n",
+								__func__);
+		goto out;
+	}


+	iBuf = kmalloc(fifo1count * sizeof(u32), GFP_KERNEL);
+	if (iBuf == NULL)
+		goto out;
 




+
+out:
+	adc_writel(adc_dev, TSCADC_REG_IRQSTATUS,
+				TSCADC_IRQENB_FIFO1THRES);
+	adc_writel(adc_dev, TSCADC_REG_IRQENABLE,
+				TSCADC_IRQENB_FIFO1THRES);
 }
 
 
 
 This function is called in 
 
 static void tiadc_poll_handler(struct work_struct *work_s)
{
    struct adc_device *adc_dev =
        container_of(work_s, struct adc_device, poll_work);
    struct iio_dev *idev = iio_priv_to_dev(adc_dev);
    struct iio_buffer *buffer = idev->buffer;
    unsigned int fifo1count, readx1;
    int i;
    u32 *iBuf;

    fifo1count = adc_readl(adc_dev, TSCADC_REG_FIFO1CNT);
    if (fifo1count * sizeof(u32) <
                buffer->access->get_bytes_per_datum(buffer)) {
        dev_err(adc_dev->mfd_tscadc->dev, "%s: Short FIFO event\n",
                                __func__);
        goto out;
    }

    iBuf = kmalloc(fifo1count * sizeof(u32), GFP_KERNEL);
    if (iBuf == NULL)
        goto out;

    for (i = 0; i < fifo1count; i++) {
        readx1 = adc_readl(adc_dev, TSCADC_REG_FIFO1);
        readx1 &= TSCADC_FIFOREAD_DATA_MASK;
        iBuf[i] = readx1;
    }

    buffer->access->store_to(buffer, (u8 *) iBuf, iio_get_time_ns());
    kfree(iBuf);

out:
    adc_writel(adc_dev, TSCADC_REG_IRQSTATUS,
                TSCADC_IRQENB_FIFO1THRES);
    adc_writel(adc_dev, TSCADC_REG_IRQENABLE,
                TSCADC_IRQENB_FIFO1THRES);
}


******************************************************************


static int tiadc_buffer_postenable(struct iio_dev *idev)
 {
 	struct adc_device *adc_dev = iio_priv(idev);
 	struct iio_buffer *buffer = idev->buffer;

+	unsigned int enb, config;
+	int stepnum;
 	u8 bit;
 

+		config = adc_readl(adc_dev, TSCADC_REG_CTRL);
+		adc_writel(adc_dev, TSCADC_REG_CTRL,
+					config & ~TSCADC_CNTRLREG_TSCSSENB);
+		adc_writel(adc_dev, TSCADC_REG_CTRL,
+					config | TSCADC_CNTRLREG_TSCSSENB);
+
+
+		adc_writel(adc_dev, TSCADC_REG_IRQSTATUS,
+				TSCADC_IRQENB_FIFO1THRES |
+				TSCADC_IRQENB_FIFO1OVRRUN |
+				TSCADC_IRQENB_FIFO1UNDRFLW);
+		adc_writel(adc_dev, TSCADC_REG_IRQENABLE,
+				TSCADC_IRQENB_FIFO1THRES |
+				TSCADC_IRQENB_FIFO1OVRRUN);
 
 		adc_writel(adc_dev, TSCADC_REG_SE, 0x00);
 		
 			stepnum = chan->channel + 9;
 			enb = adc_readl(adc_dev, TSCADC_REG_SE);
 			
 			
-			enb |= stepnum;
-			adc_writel(adc_dev, TSCADC_REG_SE, TSCADC_ENB(enb));
+			enb |= (1 << stepnum);
+			adc_writel(adc_dev, TSCADC_REG_SE, enb);		
 	
 	
 		
 This fuction is called in 
 static int tiadc_buffer_postenable(struct iio_dev *idev)
{
    struct adc_device *adc_dev = iio_priv(idev);
    struct iio_buffer *buffer = idev->buffer;
    unsigned int enb, config;
    int stepnum;
    u8 bit;

    if (!adc_dev->is_continuous_mode) {
        pr_info("Data cannot be read continuously in one shot mode\n");
        return -EINVAL;
    } else {

        config = adc_readl(adc_dev, TSCADC_REG_CTRL);
        adc_writel(adc_dev, TSCADC_REG_CTRL,
                    config & ~TSCADC_CNTRLREG_TSCSSENB);
        adc_writel(adc_dev, TSCADC_REG_CTRL,
                    config | TSCADC_CNTRLREG_TSCSSENB);


        adc_writel(adc_dev, TSCADC_REG_IRQSTATUS,
                TSCADC_IRQENB_FIFO1THRES |
                TSCADC_IRQENB_FIFO1OVRRUN |
                TSCADC_IRQENB_FIFO1UNDRFLW);
        adc_writel(adc_dev, TSCADC_REG_IRQENABLE,
                TSCADC_IRQENB_FIFO1THRES |
                TSCADC_IRQENB_FIFO1OVRRUN);

        adc_writel(adc_dev, TSCADC_REG_SE, 0x00);
        for_each_set_bit(bit, buffer->scan_mask,
                adc_dev->channels) {
            struct iio_chan_spec const *chan = idev->channels + bit;
            /*
             * There are a total of 16 steps available
             * that are shared between ADC and touchscreen.
             * We start configuring from step 16 to 0 incase of
             * ADC. Hence the relation between input channel
             * and step for ADC would be as below.
             */
            stepnum = chan->channel + 9;
            enb = adc_readl(adc_dev, TSCADC_REG_SE);
            enb |= (1 << stepnum);
            adc_writel(adc_dev, TSCADC_REG_SE, enb);
        }
        return 0;
    }
}


*******************************************************************



 	static int adc_resume(struct platform_device *pdev)
 	struct adc_device	*adc_dev = tscadc_dev->adc;
 	unsigned int restore;
 
+	restore = adc_readl(adc_dev, TSCADC_REG_CTRL);
+	restore &= ~(TSCADC_CNTRLREG_TSCSSENB);
+	adc_writel(adc_dev, TSCADC_REG_CTRL, restore);
+
 	adc_writel(adc_dev, TSCADC_REG_FIFO1THR, FIFO1_THRESHOLD);
 	adc_step_config(adc_dev, adc_dev->is_continuous_mode);
 	
 	
 	 	restore &= ~(TSCADC_CNTRLREG_POWERDOWN);
+	restore |= TSCADC_CNTRLREG_TSCSSENB;
 	adc_writel(adc_dev, TSCADC_REG_CTRL, restore);
 	return 0;
 }




The above function is calle din 

static int adc_resume(struct platform_device *pdev)
{
    struct ti_tscadc_dev   *tscadc_dev = pdev->dev.platform_data;
    struct adc_device   *adc_dev = tscadc_dev->adc;
    unsigned int restore;

    restore = adc_readl(adc_dev, TSCADC_REG_CTRL);
    restore &= ~(TSCADC_CNTRLREG_TSCSSENB);
    adc_writel(adc_dev, TSCADC_REG_CTRL, restore);

    adc_writel(adc_dev, TSCADC_REG_FIFO1THR, FIFO1_THRESHOLD);
    adc_step_config(adc_dev, adc_dev->is_continuous_mode);

    /* Make sure ADC is powered up */
    restore &= ~(TSCADC_CNTRLREG_POWERDOWN);
    restore |= TSCADC_CNTRLREG_TSCSSENB;
    adc_writel(adc_dev, TSCADC_REG_CTRL, restore);
    return 0;
}


***************************************************************************
 
 
 
