#include <linux/module.h> 
#include <linux/interrupt.h> 
 
#include "lab_miscdev.h" 
 
#define MAXIRQS 256 
 
#define NCOPY (MAXIRQS * sizeof(int)) 

static int *interrupts;

static irqreturn_t my_interrupt(int irq, void *dev_id)
{
        interrupts[irq]++;
        return IRQ_NONE;
}


static void freeup_irqs(void)
{
        int irq;
        for (irq = 0; irq < MAXIRQS; irq++){
                if(interrupts[irq] >= 0){
                        synchronize_irq(irq);
                        printk(KERN_INFO "freeing irq = %4d, which has %10d events\n", irq, interrupts[irq]);
                        free_irq(irq, interrupts);
                        }
                }
}

static void get_irqs(void)
{
        int irq;


  interrupts = (int *)ramdisk;
        for(irq = 0; irq < MAXIRQS; irq++)
        {
                interrupts[irq] = -1;
                if(request_irq (irq, my_interrupt, IRQF_SHARED, "my_intr", interrupts)){
                interrupts[irq] = 0;
                printk(KERN_INFO "successed in registering irq=%d\n", irq);
                }
        }
}


static const struct file_operations mycdrv_fops = {
        .owner = THIS_MODULE,
        .read = mycdrv_generic_read,
};

static int __init my_init(void)
{
        int rc = my_generic_init();
        if(!rc)
        get_irqs();
        return rc;
}

static void __exit my_exit(void)
{
        freeup_irqs();
        my_generic_exit();
}

module_init(my_init);
module_exit(my_exit);

MODULE_AUTHOR("G Satish Kumar");
MODULE_DESCRIPTION("IRQ Usage");
MODULE_LICENSE("GPL");
















