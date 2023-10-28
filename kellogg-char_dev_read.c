#include "kellogg.h"

/** @brief This function is called whenever device is being read from user space i.e. data is being sent from the device to the user. In this case is uses the copy_to_user() function to send the buffer string to the user and captures any errors.
 *  @param filp A pointer to a file object (defined in linux/fs.h)
 *  @param buf The pointer to the buffer to which this function writes the data
 *  @param count The length of the buffer
 *  @param f_pos The offset if required
 *  @return On success, the number of bytes read is returned. On error, a negative error code is returned.
 */
ssize_t kellogg_char_dev_read(struct file *filp, char __user *buf, size_t count, loff_t *f_pos)
{
    int error_count = 0;
    char *message = "lol char device driver go brrrrrrrrrrr\n";
    int size_of_message = strlen(message);

    printk(KERN_INFO "%s: read %lu bytes data\n", KELLOG_NAME, count);
    printk(KERN_INFO "%s:kellogg_char_dev_read\n", KELLOG_NAME);

    // copy_to_user has the format ( * to, *from, size) and returns 0 on success
    error_count = copy_to_user(buf, message, size_of_message);

    if (error_count == 0)
    {
        printk(KERN_INFO "%s: Sent %d characters to the user\n", KELLOG_NAME, size_of_message);
        return size_of_message; // clear the position to the start and return 0
    }

    printk(KERN_INFO "%s: Failed to send %d characters to the user\n", KELLOG_NAME, error_count);
    return -EFAULT; // Failed -- return a bad address message (i.e. -14)
}