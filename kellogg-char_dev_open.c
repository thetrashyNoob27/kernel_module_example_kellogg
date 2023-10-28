#include "kellogg.h"
#include "debug_printk_functions.h"

/** @brief The device open function that is called each time the device is opened This will only increment the numberOpens counter in this case.
 *  @param inode A pointer to an inode object (defined in linux/fs.h)
 *  @param filp A pointer to a file object (defined in linux/fs.h)
 *  @return     If the open operation is successful, it should return 0 to indicate success. If an error occurs during the open operation, the function should return a negative error code (e.g., -ENXIO, -ENOMEM, -EIO) to indicate the specific error that occurred.
 */
int kellogg_char_dev_open(struct inode *inode, struct file *filp)
{
    printk_inode_info(KELLOG_NAME,inode);
    print_file_info(KELLOG_NAME,filp);
    print_file_path(KELLOG_NAME,filp);
    printk(KERN_INFO "%s:kellogg_char_dev_open\n", KELLOG_NAME);
    return 0;
}