LDDINC=$(PWD)/../include
EXTRA_CFLAGS += -I$(LDDINC) -I"$(PWD)"



ifeq ($(KERNELRELEASE),)
    KERNELDIR ?= /lib/modules/$(shell uname -r)/build
    PWD := $(shell pwd)

modules:
	$(MAKE) -C "$(KERNELDIR)" M="$(PWD)" modules

modules_install:
	$(MAKE) -C "$(KERNELDIR)" M="$(PWD)" modules_install

clean:
	rm -rf *.o *~ core .depend .*.cmd *.ko *.mod.c .tmp_versions *.mod modules.order *.symvers

.PHONY: modules modules_install clean

else
	kellogg-objs := kellogg-exit.o  kellogg-init.o  kellogg-main.o
	obj-m	:= kellogg.o
	CFLAGS_kellogg.o := -g
endif



