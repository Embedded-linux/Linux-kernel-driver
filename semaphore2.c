#include <linux/module.h>
#include <linux/init.h>
#include <linux/errno.h>
#include <asm/atomic.h>
#include <linux/version.h>
#include <linux/semaphore.h>

static char *modname = __stringify(KBUILD_BASENAME);

extern struct semaphore my_sem;

static int __init my_init(void)
{
	printk(KERN_ALERT "\n%s\n", __FUNCTION__);
	printk(KERN_INFO "satish is testing\n");
	
	printk(KERN_INFO "trying to load module %s\n", modname);
	printk(KERN_INFO "semaphore_count=%u\n" , my_sem.count);

	if(down_trylock(&my_sem)) {
		printk(KERN_WARNING 
			"Not loading the module: down_trylock failed\n");
	return -EBUSY;
	}
	
	printk(KERN_INFO "\n Grabbed semaphore in %s, ", modname);
	printk(KERN_INFO "\n semaphore_count=%u\n", my_sem.count);

	return 0;
}
	

static void __exit my_exit(void)
{
	printk(KERN_ALERT "\n%s\n", __FUNCTION__);
	printk(KERN_INFO "satish is testing\n");
	
	up(&my_sem);
	printk(KERN_INFO "\n exited semaphore in %s, ", modname);
	printk(KERN_INFO "\n semaphore_count=%u\n", my_sem.count);
}	
	
module_init(my_init);
module_exit(my_exit);

MODULE_AUTHOR("G satish Kumaar");
MODULE_DESCRIPTION("semaphore chk with 3 modules");
MODULE_LICENSE("GPL");
