#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>

#include "kellogg.h"

static int __init kellog_init(void)
{
    printk(KERN_ALERT "kellogg init\n");
    // alloc device major id

    {
        dev_t dev = 0;
        int result = alloc_chrdev_region(&dev, KELLOG_DEVICE_ID_MINOR_START, KELLOG_DEVICE_CNT, KELLOG_NAME);
        if (result < 0)
        {
            printk(KERN_ALERT "%s: can't get device major id\n", KELLOG_NAME);
            goto fail;
        }
        kellog_device_number_majour = MAJOR(dev);
        printk(KERN_INFO "%s: ddevice major id alloc correctly\n", KELLOG_NAME);
    }

    // Register the device class
    {
        kellog_device_class = class_create(THIS_MODULE, KELLOG_NAME);
        if (IS_ERR(kellog_device_class))
        {
            printk(KERN_ALERT "%s: Failed to register device class\n", KELLOG_NAME);
            goto fail;
        }
        printk(KERN_INFO "%s: device class registered correctly\n", KELLOG_NAME);
    }

    // create device in devfs
    {
        kellog_class_device = kmalloc(KELLOG_DEVICE_ID_MINOR_START * sizeof(struct device *), GFP_KERNEL);
        if (!kellog_class_device)
        {
            printk(KERN_ALERT "%s: failed to malloc for class device\n", KELLOG_NAME);
            goto fail;
        }
        memset(kellog_class_device, 0, KELLOG_DEVICE_CNT * sizeof(struct device *));
        printk(KERN_INFO "%s: device struct kmalloc successful\n", KELLOG_NAME);
        for (int i = 0; i < KELLOG_DEVICE_ID_MINOR_START; i++)
        {
            kellog_class_device[i] = device_create(kellog_device_class, NULL, MKDEV(kellog_device_number_majour, i), NULL, "%s%d", KELLOG_DEVICE_NAME, i);
            if (IS_ERR(kellog_class_device[i]))
            {
                printk(KERN_ALERT "%s:Failed to create the device in devfs %s%d\n", KELLOG_NAME, KELLOG_DEVICE_NAME, i);
                goto fail;
            }
        }
        printk(KERN_INFO "%s: devfs device created correctly\n", KELLOG_NAME);
    }
    printk(KERN_INFO "%s: module init success\n", KELLOG_NAME);

    return 0;
fail:
    kellog_resource_release();
    return 1;
}

module_init(kellog_init);