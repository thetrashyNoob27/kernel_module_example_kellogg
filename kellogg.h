#ifndef KELLOGG_H
#define KELLOGG_H

#define KELLOG_NAME "kellogg"
#define KELLOG_DEVICE_NAME "klog"
#define KELLOG_DEVICE_CNT 8
#define KELLOG_DEVICE_ID_MINOR_START 0


#define KELLOG_NAME "kellogg"
#define KELLOG_DEVICE_NAME "klog"
#define KELLOG_DEVICE_CNT 8
#define KELLOG_DEVICE_ID_MINOR_START 0



extern int kellog_device_number_majour;
extern  struct class *kellog_device_class;
extern  struct device **kellog_class_device;

void kellog_resource_release(void);
#endif