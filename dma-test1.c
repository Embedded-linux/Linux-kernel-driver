#include <linux/module.h>
#include <linux/init.h>
#include <linux/pci.h>
#include <linux/slab.h>
#include <linux/dma-mapping.h>
#include <linux/dmapool.h>

static int direction = PCI_DMA_BIDIRECTIONAL;

static char *kbuf;
static dma_addr_t handle;
static size_t size = (10 * PAGE_SIZE);
static struct dma_pool *mypool;
static size_t pool_size = 1024;
static size_t pool_align = 8;


static void output(char *kbuf, dma_addr_t handle, size_t size, char *string)
{
        unsigned long diff;
        diff = (unsigned long)kbuf - handle;
        printk(KERN_INFO "kbuf=%12p, handle=%12p, size = %d\n", kbuf, (unsigned long *)handle, (int)size);
        printk(KERN_INFO "(kbuf-handle)=%12p, %12lu, PAGE_OFFSET=%12lu, comapre=%lu\n",(void *)diff, diff, PAGE_OFFSET, diff - PAGE_OFFSET);
          strcpy(kbuf, string);
        printk(KERN_INFO, "string written was %s \n", kbuf);
        printk(KERN_INFO, "sttoish testing string copy with DMA\n");
}


static int __init my_init(void)
{

        printk(KERN_INFO "Satish testing DMA module");

        printk(KERN_INFO "testing DMA coherent mapping dma_alloc_coherent()");
        kbuf = dma_alloc_coherent(NULL, size, &handle, GFP_KERNEL);
        output(kbuf, handle, size, "dma_alloc_coherent string");
        dma_free_coherent(NULL, size, kbuf, handle);


        printk(KERN_INFO "Testing DMA Mapping dma_map_page()");
        kbuf = kmalloc(size, GFP_KERNEL);
        handle = dma_map_single(NULL, size, &handle, GFP_KERNEL);
        output(kbuf, handle, size, "this is dma_map_single string");
        dma_unmap_single(NULL, handle, size, direction);
        kfree(kbuf);


        printk(KERN_INFO "Testing DMA Pool method");
        mypool = dma_pool_create("mypool", NULL, pool_size, pool_align, 0);
        kbuf = dma_pool_alloc(mypool, GFP_KERNEL, &handle);
        output(kbuf, handle, size, "This is dma_pool_alloc string");
        dma_pool_free(mypool, kbuf, handle);
        dma_pool_destroy(mypool);

        return 0;
}

static void __exit my_exit(void)
{
        printk(KERN_INFO "Module unloading\n");
}


module_init(my_init);
module_exit(my_exit);


MODULE_AUTHOR("G Satish Kumar");
MODULE_DESCRIPTION("Testing DMA single page, coherent and pool allocation");
MODULE_LICENSE("GPL");

