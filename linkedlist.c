/*
Author: Noushin Behboudi
Email : b.noushin7@gmail.com
*/

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/list.h>
#include <linux/random.h>
#include<linux/slab.h>

static int dstruct = 5;
module_param(dstruct, int, 0);

struct my_linkedlist
{
	int node_value;
	struct list_head list; 
};

struct my_linkedlist ll;


static int __init ll_init(void)
{
	struct my_linkedlist *aNewll, *tmpll, *a_ll;
	int i;
	int rand;

	tmpll = kmalloc(sizeof(struct my_linkedlist), GFP_KERNEL);
	a_ll = kmalloc(sizeof(struct my_linkedlist), GFP_KERNEL);
	INIT_LIST_HEAD(&ll.list);

	for(i=0; i<dstruct; ++i){
		aNewll = kmalloc(sizeof(struct my_linkedlist), GFP_KERNEL);
		get_random_bytes(&rand, 1);
	//      printk("rand is: %d\n", rand);
		aNewll->node_value = rand;
		INIT_LIST_HEAD(&aNewll->list);
		list_add_tail(&(aNewll->list), &(ll.list));
	}


	list_for_each_entry(tmpll, &ll.list, list) {

		printk(KERN_INFO "Value is : %d\n", tmpll->node_value);
	}

	printk(KERN_INFO "Now the list will be freed");

	list_for_each_entry_safe(a_ll, tmpll, &ll.list, list){

		printk(KERN_INFO "freeing node with value: %d\n", a_ll->node_value);
		list_del(&a_ll->list);
		kfree(a_ll);
	}

	return 0;
}


static void __exit ll_exit(void)
{
	printk(KERN_INFO "kernel module unloaded.n");
}

module_init(ll_init);
module_exit(ll_exit);


MODULE_LICENSE("GPL");
MODULE_AUTHOR("Noushin noushin7<@vt.edu");
MODULE_DESCRIPTION("Linkedlist manipulation");

