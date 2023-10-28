#include "kellogg.h"

/** @brief is function is called when the last reference to the device file is released (e.g., when the file is closed). It is used for cleanup and resource deallocation.
 *  @param inodep A pointer to an inode object (defined in linux/fs.h)
 *  @param filep A pointer to a file object (defined in linux/fs.h)
 *  @return If the release operation is successful (i.e., all cleanup tasks are completed without errors), it should return 0 to indicate success. If an error occurs during the release operation, the function should return a negative error code (e.g., -EBUSY, -EIO, -ENOMEM) to indicate the specific error that occurred.
 */
int kellogg_char_dev_release(struct inode *inodep, struct file *filep)
{
    printk(KERN_INFO "%s:kellogg_char_dev_release\n", KELLOG_NAME);
    return 0;
}