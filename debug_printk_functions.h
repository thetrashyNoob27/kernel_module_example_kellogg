#ifndef DEBUG_PRINTK_FUNCTIONS
#define DEBUG_PRINTK_FUNCTIONS

#include <linux/fs.h>
void printk_inode_info(const char *prefix, struct inode *inode);
void print_file_info(const char *prefix, struct file *filp);
void print_file_path(const char *prefix, struct file *filp);

#endif