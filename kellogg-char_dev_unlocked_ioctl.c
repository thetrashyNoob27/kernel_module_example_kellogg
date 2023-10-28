#include "kellogg.h"

/** @brief This field represents a callback for handling device-specific I/O control (ioctl) requests. It is used to provide device-specific features or configuration through ioctl calls.
 *  @param filp This is a pointer to the file structure associated with the device file 
 *  @param cmd This parameter is an unsigned integer that represents the IOCTL command.
 *  @param arg This parameter is an unsigned long integer that represents the argument or data associated with the IOCTL command. 
 *  @return     If the ioctl operation is successful, it should return 0 to indicate success. If an error occurs during the ioctl operation, the function should return a negative error code (e.g., -EINVAL, -EFAULT, -ENODEV) to indicate the specific error that occurred.
 */
long int kellogg_char_dev_unlocked_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
    printk(KERN_INFO "%s:kellogg_char_dev_unlocked_ioctl\n", KELLOG_NAME);
    return 0;
}