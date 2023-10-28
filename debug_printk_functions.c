#include "debug_printk_functions.h"
#include <linux/module.h>
#include <linux/kernel.h>

void printk_inode_info(const char *prefix, struct inode *inode)
{
    printk(KERN_INFO "%s Inode Information:\n", prefix);
    printk(KERN_INFO "%s i_ino: %lu\n", prefix, inode->i_ino);
    printk(KERN_INFO "%s i_mode: 0x%-4x\n", prefix, inode->i_mode);
    printk(KERN_INFO "%s i_uid: %u\n", prefix, i_uid_read(inode));
    printk(KERN_INFO "%s i_gid: %u\n", prefix, i_gid_read(inode));
    printk(KERN_INFO "%s i_size: %lld\n", prefix, i_size_read(inode));
    printk(KERN_INFO "%s i_blocks: %lld\n", prefix, inode->i_blocks);
    printk(KERN_INFO "%s i_atime: %lld\n", prefix, inode->i_atime.tv_sec);
    printk(KERN_INFO "%s i_mtime: %lld\n", prefix, inode->i_mtime.tv_sec);
    printk(KERN_INFO "%s i_ctime: %lld\n", prefix, inode->i_ctime.tv_sec);
}

void print_file_info(const char *prefix, struct file *filp)
{
    printk(KERN_INFO "%s File Information:\n", prefix);
    printk(KERN_INFO "%s   f_flags: 0x%-5x\n", prefix, filp->f_flags);
    printk(KERN_INFO "%s   f_mode: 0x%-5x\n", prefix, filp->f_mode);
    printk(KERN_INFO "%s   f_pos: %lld\n", prefix, filp->f_pos);
}

void print_file_path(const char *prefix, struct file *filp)
{
    struct path path;
    struct dentry *dentry;
    struct vfsmount *vfsmnt;

    path = filp->f_path;
    dentry = path.dentry;
    vfsmnt = path.mnt;

    printk(KERN_INFO "File Name: %s\n", dentry->d_iname);
    //printk(KERN_INFO "Mount Point: %s\n", vfsmnt->mnt_devname);
}