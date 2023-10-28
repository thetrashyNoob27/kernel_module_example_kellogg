#include "kellogg.h"

static void __exit kellog_exit(void)
{
    kellog_resource_release();
    printk(KERN_INFO "%s: module exit finished\n", KELLOG_NAME);
}

void kellog_resource_release(void)
{
    // remove device in devfs
    if (kellog_class_device)
    {
        for (int i = 0; i < KELLOG_DEVICE_CNT; i++)
        {
            if (kellog_class_device[i] == NULL)
                continue;
            printk(KERN_INFO "%s:device %s%d removed\n", KELLOG_NAME, KELLOG_DEVICE_NAME, i);
            device_destroy(kellog_device_class, MKDEV(kellog_device_number_majour, i));
            kellog_class_device[i] = NULL;
        }
        kfree(kellog_class_device);
        kellog_class_device = NULL;
    }

    // un-register the device class
    if (kellog_device_class)
    {
        printk(KERN_INFO "%s:un-register the device class\n", KELLOG_NAME);
        class_unregister(kellog_device_class);
        class_destroy(kellog_device_class);
        kellog_device_class = NULL;
    }

    // un-register the character device
    if (kellogg_char_device)
    {
        printk(KERN_INFO "%s:un-register the char device\n", KELLOG_NAME);
        for (int i = 0; i < KELLOG_DEVICE_CNT; i++)
        {
            struct kellogg_cdev *device = kellogg_char_device + i;
            cdev_del(&device->cdev);
            // clean up character device start
            
            // clean up character device end
        }
        kfree(kellogg_char_device);
        kellogg_char_device = NULL;
    }

    // un-register device major id
    printk(KERN_INFO "%s:un-register the device major id\n", KELLOG_NAME);
    unregister_chrdev_region(MKDEV(kellog_device_number_majour, 0), KELLOG_DEVICE_CNT);
}

void kellogg_character_device_cleanup(struct kellogg_cdev *dev)
{
    if(!dev)
    {
        printk(KERN_WARNING "%s:get your shit together. your are trying to kellogg_character_device_cleanup a NULL\n", KELLOG_NAME);
        return;
    }

}

module_exit(kellog_exit);
