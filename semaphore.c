#include <linux/init.h>
#include <linux/module.h>
#include <linux/version.h>
#include <asm/atomic.h>
#include <linux/semaphore.h>

/* Linux version call changes */

#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,37)
DECLARE_MUTEX(my_sem);
#else
DEFINE_SEMAPHORE(my_sem);
#endif
EXPORT_SYMBOL(my_sem);

static int __init my_init(void)
{
	printk(KERN_INFO "\n Initilize semaphore, ");
	printk(KERN_INFO "\n semaphore count= %u\n", my_sem.count);
	return 0;
}


static void __exit my_exit(void)
{
	
	printk(KERN_INFO "\n Exiting semaphore, ");
	printk(KERN_INFO "\n semaphore count= %u\n", my_sem.count);
}


module_init(my_init);
module_exit(my_exit);

MODULE_AUTHOR("G Satish Kumar");
MODULE_DESCRIPTION("semaphore contention");
MODULE_LICENSE("GPL");
