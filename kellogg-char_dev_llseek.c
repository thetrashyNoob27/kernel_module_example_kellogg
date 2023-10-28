#include "kellogg.h"

/** @brief This function is used to change the current file position within the device. It is typically associated with seeking or repositioning within the device.
 *  @param filp This is a pointer to the file structure associated with the device file that the llseek operation is being performed on. The filp structure contains information about the opened file, including the file position.
 *  @param off This parameter represents the new file position (offset) that you want to set. It's of type loff_t, which is a type used for file offsets.
 *  @param whence This parameter is an integer that specifies the reference point for setting the new file position (off). It can take one of the following values:
 *                SEEK_SET (0): Set the file position to an absolute value (off is the new position).
 *                SEEK_CUR (1): Set the file position relative to the current position (off is added to the current position).
 *                SEEK_END (2): Set the file position relative to the end of the file (off is subtracted from the end of the file).
 *  @return represent the new file position after the seek operation.
 */
loff_t kellogg_char_dev_llseek(struct file *filp, loff_t off, int whence)
{
    printk(KERN_INFO "%s:kellogg_char_dev_llseek\n", KELLOG_NAME);
    return 0;
}