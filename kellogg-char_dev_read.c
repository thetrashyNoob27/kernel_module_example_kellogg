#include "kellogg.h"

/** @brief This function is called whenever device is being read from user space i.e. data is being sent from the device to the user. In this case is uses the copy_to_user() function to send the buffer string to the user and captures any errors.
 *  @param filep A pointer to a file object (defined in linux/fs.h)
 *  @param buffer The pointer to the buffer to which this function writes the data
 *  @param len The length of the b
 *  @param offset The offset if required
 *  @return On success, the number of bytes read is returned. On error, a negative error code is returned.
 */
ssize_t kellogg_char_dev_read(struct file *filp, char __user *buf, size_t count, loff_t *f_pos)
{
    printk(KERN_INFO "%s:kellogg_char_dev_read\n", KELLOG_NAME);
    return 0;
}