#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>

#include "kellogg.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("peter jackson");
MODULE_DESCRIPTION("A char device demo that printk");
MODULE_VERSION("0.1");

#define KELLOG_NAME "kellogg"
#define KELLOG_DEVICE_NAME "klog"
#define KELLOG_DEVICE_CNT 8
#define KELLOG_DEVICE_ID_MINOR_START 0

int kellog_device_number_majour = -1;
struct class *kellog_device_class = NULL;
struct device **kellog_class_device = NULL;
