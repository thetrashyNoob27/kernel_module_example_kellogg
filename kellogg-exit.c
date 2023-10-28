#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>

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
        for (int i = 0; i < KELLOG_DEVICE_ID_MINOR_START; i++)
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

    // un-register device major id
    printk(KERN_INFO "%s:un-register the device major id\n", KELLOG_NAME);
    unregister_chrdev_region(MKDEV(kellog_device_number_majour, 0), KELLOG_DEVICE_CNT);
}

module_exit(kellog_exit);
