#ifndef KELLOGG_H
#define KELLOGG_H

#include <linux/module.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/cdev.h>

#define KELLOG_NAME "kellogg"
#define KELLOG_DEVICE_NAME "klog"
#define KELLOG_DEVICE_CNT 8
#define KELLOG_DEVICE_ID_MINOR_START 0

// type defince
struct kellogg_cdev
{
    struct mutex lock; /* mutual exclusion semaphore     */
    struct cdev cdev;  /* Char device structure		*/
};

extern int kellog_device_number_majour;
extern struct kellogg_cdev *kellogg_char_device;
extern struct class *kellog_device_class;
extern struct device **kellog_class_device;

extern struct file_operations kellogg_file_operation;

void kellog_resource_release(void);
void kellogg_character_device_setup(struct kellogg_cdev *dev);
void kellogg_character_device_cleanup(struct kellogg_cdev *dev);

loff_t kellogg_char_dev_llseek(struct file *filp, loff_t off, int whence);
int kellogg_char_dev_open(struct inode *inode, struct file *filp);
ssize_t kellogg_char_dev_read(struct file *filp, char __user *buf, size_t count, loff_t *f_pos);
int kellogg_char_dev_release(struct inode *inodep, struct file *filep);
long int kellogg_char_dev_unlocked_ioctl(struct file *filp, unsigned int cmd, unsigned long arg);
ssize_t kellogg_char_dev_write(struct file *filep, const char *buffer, size_t len, loff_t *offset);

#endif