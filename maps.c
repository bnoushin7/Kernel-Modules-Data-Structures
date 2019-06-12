/*
Author: Noushin Behboudi
Email : b.noushin7@gmail.com
*/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/random.h>
#include<linux/slab.h>
#include<linux/idr.h>

static int dstruct = 5;
module_param(dstruct, int, 0);

static int __init map_init(void)
{

	int i, id, *tmp;
	int rand[dstruct];
	struct idr my_map;
	int ids_to_iterate [dstruct];
	idr_init(&my_map);
	idr_preload(GFP_KERNEL);

	for(i=0; i<dstruct; ++i){
		get_random_bytes(&rand[i], 1);
	//	printk("rand is: %d\n",rand[i]);
		id = idr_alloc(&my_map, &rand[i], 10, 550, GFP_KERNEL);
		ids_to_iterate[i] = id;

		idr_preload_end();
		if(id == -ENOSPC)
			printk("error! no id available in the requested range\n");
		else if(id == -ENOMEM)
			printk("error! could not allocate memory\n");

	}
	printk("Now reading from the map\n");	
	for(i=0; i<dstruct; ++i){
		tmp = idr_find(&my_map, ids_to_iterate[i]);
		printk("pair is: <%d , %d>\n", ids_to_iterate[i], *tmp );

	}


	printk(KERN_INFO "Now the map will be freed");
	idr_destroy(&my_map);

	return 0;
}

static void __exit map_exit(void)
{

	printk(KERN_INFO "kernel module unloaded.\n");


}

module_init(map_init);
module_exit(map_exit);


MODULE_LICENSE("GPL");
MODULE_AUTHOR("Noushin noushin7<@vt.edu");
MODULE_DESCRIPTION("Linkedlist manipulation");

