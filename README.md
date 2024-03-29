# Kernel Modules and Data Structures

This project develops a kernel module and manipulates the following frequently-used kernel data structures: linked lists, queues, maps, and red-black trees. The modules take one integer parameter `dstruct_size` and should compile against a v4.0 kernel.  Each module includes a function manipulating the following data structures:

## Linked lists
(A) constructs a linked list containing `dstruct_size` random integers; (B) prints on the kernel log the content of the list through the use of list navigation functions; and (C) destructs the list and free its content. There are two versions of the linked list exercise: one executing (A), (B) and (C) in the same function, the second calling (A), (B) and (C) each in a different function.

## Queues
It creates a queue and enqueue `dstruct_size` random integers, then dequeue these elements, print them, then free them if needed.

## Maps 
It creates a map and insert in it `dstruct_size` random integers. The `id` value associated with each element is constrained into a specific range defined by a low and high bound, clearly indicated in the code. It prints the content of the map and the id associated with each element before freeing the data structure.

## Red-black trees 
It creates a `rbtree` with nodes being random integers, indexed by the integers values. It inserts `dstruct_size` random integers (while being careful not to insert duplicates) into the tree and then prints the tree on the kernel log. Then a loop iterates over an integer range of the choice (according to the tree content) and for each of these indicates (by printing to the kernel log) if it is present in the tree, and remove the element. Next, it prints the tree again. Finally all remaining elements are removed from the tree and the data structure freed if needed. Note that with the red-black tree implementation of Linux, it is needed to implement the search and insert functions.
