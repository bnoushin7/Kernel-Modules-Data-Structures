/*
Author: Noushin Behboudi
Email : b.noushin7@gmail.com
*/

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/random.h>
#include<linux/slab.h>
#include <linux/rbtree.h>

#define TRUE 1
static int dstruct = 20;
module_param(dstruct, int, 0);

struct my_type {
	int node_value;
	struct rb_node node;
};

int my_insert(struct rb_root *root, struct my_type *data)
{
	struct rb_node **new = &(root->rb_node), *parent = NULL;

	while (*new) {
		struct my_type *this = container_of(*new, struct my_type, node);

		parent = *new;

		if (this->node_value > data->node_value)
			new = &((*new)->rb_left);
		else if (this->node_value < data->node_value)
			new = &((*new)->rb_right);
		else
			return -EEXIST;

	}

	rb_link_node(&data->node, parent, new);
	rb_insert_color(&data->node, root);
	return TRUE;
}


void print_nodes(struct rb_root *root)
{
	struct rb_node *node;
	for (node = rb_first(root); node; node = rb_next(node))
		printk("key=%d\n", rb_entry(node, struct my_type, node)->node_value);
}


struct my_type *my_search(struct rb_root *root, int key)
{
	struct rb_node *node = root->rb_node;

	while (node) {
		struct my_type *data = container_of(node, struct my_type, node);

		if (key < data->node_value) {
			node = node->rb_left;
		} else if (key > data->node_value) {
			node = node->rb_right;
		} else {
		//	printk("key %d  was found\n", data->node_value);
			return data;
		}
	}
	return NULL;
}


static int __init rbt_init(void)
{
	int i, j, k;
	int rand;

	struct rb_root my_tree = RB_ROOT;
	struct my_type *new_node_arr[dstruct];
	struct my_type *new_node;
	struct my_type *victim_node;
	struct rb_node *node;

	for(k = 0; k < dstruct; ++k)
		new_node_arr[k] = kmalloc(sizeof(*new_node), GFP_KERNEL);

	for (i = 0; i < dstruct; ++i) {
		rand = get_random_int() % 10000;
		new_node_arr[i]->node_value = rand;
		my_insert(&my_tree, new_node_arr[i]);
	}

	print_nodes(&my_tree);
	printk("*****************************************************************\n");

	for (j = 2000; j < 5000; ++j) {

		victim_node = my_search(&my_tree, j);

		if (victim_node) {
			printk("victim_node %d found and will be erased.\n", victim_node->node_value);
			rb_erase(&victim_node->node, &my_tree);
		}
	}
	printk("*****************************************************************\n");
	printk("This is the tree after deleting victim nodes! \n");
	print_nodes(&my_tree);
	
	printk("********************deleting the rest****************************\n");
	
	for (node = rb_first(&my_tree); node; node = rb_next(node)) {
			rb_erase(node, &my_tree);
			printk("%d was also deleted \n",rb_entry(node, struct my_type, node)->node_value );
					}
	printk("now the print will be empty! \n");

	print_nodes(&my_tree);



	printk("********************deleting done******************************\n");

	for(k = 0; k < dstruct; ++k)
		kfree(new_node_arr[k]);

	return 0;
}


static void __exit rbt_exit(void)
{
		printk(KERN_INFO "kernel module unloaded.n");
}

module_init(rbt_init);
module_exit(rbt_exit);


MODULE_LICENSE("GPL");
MODULE_AUTHOR("Noushin noushin7<@vt.edu");
MODULE_DESCRIPTION("rbtree manipulation");

