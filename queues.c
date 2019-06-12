/*
Author: Noushin Behboudi
Email : b.noushin7@gmail.com
*/

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/random.h>
#include <linux/kfifo.h>
static int dstruct = 5;
module_param(dstruct, int, 0);

struct kfifo my_queue;

struct q_element
{
int value;
};


static int __init q_init(void)
{

	int i, rand, ret_alloc, ret;
	unsigned int deq_ret;
	struct q_element tmp_que, tmp_deque;

	ret_alloc = kfifo_alloc(&my_queue, 1024, GFP_KERNEL);
	if(ret_alloc)
		return ret_alloc;

	for(i=0; i<dstruct; ++i){
		get_random_bytes(&rand, 1);
		tmp_que.value = rand;

	ret = kfifo_in(&my_queue, &tmp_que, sizeof(struct q_element));
	if(ret != sizeof(struct q_element))
		printk("Not enough space left in the queue\n  size is %d", ret);
		else
		printk("random value is: %d\n", rand);
	}
	printk(KERN_INFO "Now the queue will be dequeued\n");

	for(i=0; i<dstruct; ++i){

	 deq_ret = kfifo_out(&my_queue, &tmp_deque, sizeof(struct q_element));
		printk("dequeued value is: %d\n", tmp_deque.value);
				}
	 kfifo_free(&my_queue);

	return 0;
}


static void __exit q_exit(void)
{

	printk(KERN_INFO "kernel module unloaded.n");


}

module_init(q_init);
module_exit(q_exit);


MODULE_LICENSE("GPL");
MODULE_AUTHOR("Noushin noushin7<@vt.edu");
MODULE_DESCRIPTION("Queue manipulation");

