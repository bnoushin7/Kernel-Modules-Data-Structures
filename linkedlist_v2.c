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


void func_A(struct my_linkedlist* link_A)
{
	int i;
	int rand;


	struct my_linkedlist *tmp;
	for(i=0; i<dstruct; ++i){
		tmp = kmalloc(sizeof(struct my_linkedlist), GFP_KERNEL);
		get_random_bytes(&rand, 1);
        //	printk("rand is: %d\n", rand);
		tmp->node_value = rand;
		INIT_LIST_HEAD(&tmp->list);
		list_add_tail(&(tmp->list), &(link_A->list));
	}
}


void func_B(struct my_linkedlist* link_B)
{
	struct my_linkedlist *tmp;
	tmp = kmalloc(sizeof(struct my_linkedlist), GFP_KERNEL);
	list_for_each_entry(tmp, &link_B->list, list) {

		printk(KERN_INFO "Value is : %d\n", tmp->node_value);
	}
}


void func_C(struct my_linkedlist* link_C)
{

	struct my_linkedlist *tmp, *type_next;
	tmp = kmalloc(sizeof(struct my_linkedlist), GFP_KERNEL);
	type_next = kmalloc(sizeof(struct my_linkedlist), GFP_KERNEL);
	list_for_each_entry_safe(tmp, type_next, &link_C->list, list){

		printk(KERN_INFO "freeing node with value: %d\n", tmp->node_value);
		list_del(&tmp->list);
		kfree(tmp);
	}
}


static int __init ll_init(void)
{
	struct my_linkedlist ll;
	INIT_LIST_HEAD(&ll.list);
	func_A(&ll);
	func_B(&ll);
	func_C(&ll);

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

