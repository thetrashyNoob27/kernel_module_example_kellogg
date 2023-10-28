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
struct kellogg_cdev *kellogg_char_device = NULL;
struct class *kellog_device_class = NULL;
struct device **kellog_class_device = NULL;

struct file_operations kellogg_file_operation = {
    .owner = THIS_MODULE,
    .llseek = kellogg_char_dev_llseek,
    .read = kellogg_char_dev_read,
    .write = kellogg_char_dev_write,
    .unlocked_ioctl = kellogg_char_dev_unlocked_ioctl,
    .open = kellogg_char_dev_open,
    .release = kellogg_char_dev_release,
};
