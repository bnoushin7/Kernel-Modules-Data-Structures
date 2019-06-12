obj-m += linkedlist.o
obj-m += linkedlist_v2.o
obj-m += queues.o
obj-m += maps.o
obj-m += rbtrees.o

KDIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

all: linkedlist.c linkedlist_v2.c queues.c maps.c rbtrees.c
	make -C $(KDIR) SUBDIRS=$(PWD) modules

clean:	
	make -C $(KDIR) SUBDIRS=$(PWD) clean
