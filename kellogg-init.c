#include "kellogg.h"

static int __init kellogg_init(void)
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

    // register the  character device
    {
        kellogg_char_device = kmalloc(KELLOG_DEVICE_CNT * sizeof(struct kellogg_cdev), GFP_KERNEL);
        if (!kellogg_char_device)
        {
            printk(KERN_ALERT "%s: failed to malloc for kellogg_char_device\n", KELLOG_NAME);
            goto fail;
        }
        memset(kellogg_char_device, 0, KELLOG_DEVICE_CNT * sizeof(struct kellogg_cdev));
        printk(KERN_INFO "%s:kellogg_char_device kmalloc successful\n", KELLOG_NAME);
        for (int i = 0; i < KELLOG_DEVICE_CNT; i++)
        {
            int add_result;
            int devno = MKDEV(kellog_device_number_majour, KELLOG_DEVICE_ID_MINOR_START + i);

            struct kellogg_cdev *device = kellogg_char_device + i;
            kellogg_character_device_setup(device);
            cdev_init(&device->cdev, &kellogg_file_operation);
            add_result = cdev_add(&device->cdev, devno, 1);
            if (add_result)
            {
                printk(KERN_ALERT "%s: Error %d adding %s%d\n", KELLOG_NAME, add_result, KELLOG_DEVICE_NAME, i);
                goto fail;
            }
        }
        printk(KERN_INFO "%s: character device register successful\n", KELLOG_NAME);
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
        printk(KERN_INFO "%s: before kmalloc device\n", KELLOG_NAME);
        kellog_class_device = kmalloc(KELLOG_DEVICE_CNT * sizeof(struct device *), GFP_KERNEL);
        printk(KERN_INFO "%s: after kmalloc device\n", KELLOG_NAME);
        if (!kellog_class_device)
        {
            printk(KERN_ALERT "%s: failed to malloc for class device\n", KELLOG_NAME);
            goto fail;
        }
        memset(kellog_class_device, 0, KELLOG_DEVICE_CNT * sizeof(struct device *));
        printk(KERN_INFO "%s: device struct kmalloc successful\n", KELLOG_NAME);
        for (int i = 0; i < KELLOG_DEVICE_CNT; i++)
        {
            kellog_class_device[i] = device_create(kellog_device_class, NULL, MKDEV(kellog_device_number_majour, i), NULL, "%s%d", KELLOG_DEVICE_NAME, i);
            if (IS_ERR(kellog_class_device[i]))
            {
                printk(KERN_ALERT "%s:Failed to create the device in devfs %s%d\n", KELLOG_NAME, KELLOG_DEVICE_NAME, i);
                goto fail;
            }
            printk(KERN_INFO "%s: create dev file %s%d\n", KELLOG_NAME, KELLOG_DEVICE_NAME, i);
        }
        printk(KERN_INFO "%s: devfs device created correctly\n", KELLOG_NAME);
    }
    printk(KERN_INFO "%s: module init success\n", KELLOG_NAME);

    return 0;
fail:
    kellog_resource_release();
    return 1;
}

void kellogg_character_device_setup(struct kellogg_cdev *dev)
{
    if (!dev)
    {
        printk(KERN_WARNING "%s:get your shit together. your are trying to kellogg_character_device_setup a NULL\n", KELLOG_NAME);
        return;
    }
    mutex_init(&dev->lock);
}

module_init(kellogg_init);