#include "kellogg.h"

/** @brief This function is called when a user-space application attempts to write data to the device file. It should write data from the user-space buffer to the device.
 *  @param filep A pointer to a file object (defined in linux/fs.h)
 *  @param buffer The pointer to the buffer to which this function writes the data
 *  @param len The length of the b
 *  @param offset The offset if required
 *  @return     If the write operation is successful, it should return the number of bytes written, which should be equal to len. If an error occurs during the write operation, the function should return a negative error code (e.g., -EFAULT, -EIO, -ENOMEM) to indicate the specific error that occurred.
 */
ssize_t kellogg_char_dev_write(struct file *filep, const char *buffer, size_t len, loff_t *offset)
{
    printk(KERN_INFO "%s:kellogg_char_dev_write\n", KELLOG_NAME);
    return 0;
}