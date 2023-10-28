#include "kellogg.h"
#include "debug_printk_functions.h"

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/string.h>

int _isdigit(char c)
{
    return c > '0' && c < '9';
}

int extract_number(const char *str)
{
    int result = 0;
    int i = 0;

    // Skip non-numeric characters at the beginning
    while (str[i] != '\0' && !_isdigit(str[i]))
    {
        i++;
    }

    // Collect numeric characters and convert them to an integer
    while (str[i] != '\0' && _isdigit(str[i]))
    {
        result = result * 10 + (str[i] - '0');
        i++;
    }

    return result;
}

/** @brief This function is called when a user-space application attempts to write data to the device file. It should write data from the user-space buffer to the device.
 *  @param filep A pointer to a file object (defined in linux/fs.h)
 *  @param buffer The pointer to the buffer to which this function writes the data
 *  @param len The length of the b
 *  @param offset The offset if required
 *  @return     If the write operation is successful, it should return the number of bytes written, which should be equal to len. If an error occurs during the write operation, the function should return a negative error code (e.g., -EFAULT, -EIO, -ENOMEM) to indicate the specific error that occurred.
 */
ssize_t kellogg_char_dev_write(struct file *filep, const char *buffer, size_t len, loff_t *offset)
{
    char *file_name = filep->f_path.dentry->d_iname;
    int device_id = extract_number(file_name) % 10;

    print_file_info(KELLOG_NAME, filep);
    printk(KERN_INFO "%s content size:%lu offset: %lld\n", KELLOG_NAME, len, *offset);
    printk(KERN_INFO "%s:kellogg_char_dev_write\n", KELLOG_NAME);

    switch (device_id)
    {
    case 0:
        printk(KERN_EMERG "%s: KERN_EMERG\n%s\n", KELLOG_NAME, buffer);
        break;
    case 1:
        printk(KERN_ALERT "%s: KERN_ALERT\n%s\n", KELLOG_NAME, buffer);
        break;
    case 2:
        printk(KERN_CRIT "%s: KERN_CRIT\n%s\n", KELLOG_NAME, buffer);
        break;
    case 3:
        printk(KERN_ERR "%s: KERN_ERR\n%s\n", KELLOG_NAME, buffer);
        break;
    case 4:
        printk(KERN_WARNING "%s: KERN_WARNING\n%s\n", KELLOG_NAME, buffer);
        break;
    case 5:
        printk(KERN_NOTICE "%s: KERN_NOTICE\n%s\n", KELLOG_NAME, buffer);
        break;
    case 6:
        printk(KERN_INFO "%s: KERN_INFO\n%s\n", KELLOG_NAME, buffer);
        break;
    case 7:
        printk(KERN_DEBUG "%s: KERN_DEBUG\n%s\n", KELLOG_NAME, buffer);
        break;

    default:
        printk(KERN_ALERT "%s: dafaq is this level\n", KELLOG_NAME);
        break;
    }
    return len;
}