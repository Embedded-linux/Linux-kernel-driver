/* Timer function executes and print out total elapsed time from module is loaded */


#include <linux/module.h>
#include <linux/timer.h>
#include <asm/msr.h>		
#include <linux/init.h>
#include <linux/jiffies.h>
#include <linux/slab.h>

static unsigned long speed;	/* MHZ of CPU */

static struct timer_list timer_a;

static struct kt_data {
	unsigned long period;
	unsigned long start_time;	
	u64 tsc_start;		
	u64 tsc_end;		
} *data_a;

static void ktfun_a(unsigned long var)
{
	u64 ticks;
	int msecs;
	struct kt_data *tdata = (struct kt_data *)var;

	rdtscll(tdata->tsc_end);
	ticks = tdata->tsc_end - tdata->tsc_start;
	msecs = (unsigned long)ticks / (speed * 1000);
	printk(KERN_INFO
	       "A: period = %ld  elapsed = %ld TSC ticks: %lld msecs = %d\n",
	       tdata->period, jiffies - tdata->start_time, ticks, msecs);

	rdtscll(tdata->tsc_start);
	mod_timer(&timer_a, tdata->period + jiffies);
}


static int __init my_init(void)
{
	speed = cpu_khz / 1000;
	printk(KERN_INFO "CPU MHZ is found to be: %ld \n", speed);

	init_timer(&timer_a);

	timer_a.function = ktfun_a;
	data_a = kmalloc(sizeof(*data_a), GFP_KERNEL);
	timer_a.data = (unsigned long)data_a;
	data_a->period = 1 * HZ;	/* short period, 1 second  */
	data_a->start_time = jiffies;
	timer_a.expires = jiffies + data_a->period;

	rdtscll(data_a->tsc_start);
	add_timer(&timer_a);

	return 0;
}

static void __exit my_exit(void)
{
	/* delete any running timers */
	printk(KERN_INFO "Deleted timer A: rc = %d\n",
	       del_timer_sync(&timer_a));
	kfree(data_a);
	printk(KERN_INFO "Module successfully unloaded \n");
}

module_init(my_init);
module_exit(my_exit);

MODULE_AUTHOR("G Satish Kumar");
MODULE_DESCRIPTION("Periodic timers to find out elapsed time 
		since module is loaded");
MODULE_LICENSE("GPL");

