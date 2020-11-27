#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sched/task.h>	// init_task
#include <linux/sched/signal.h>	// for_each_process

static void traverse_count(void){
	int running = 0;			// number of TASK_RUNNING
	int interruptible = 0;		// number of TASK_INTERRUPTIBLE
	int uninterruptible = 0;	// number of TASK_UNINTERRUPTIBLE
	int zombie = 0;				// number of EXIT_ZOMBIE
	int stopped = 0;			// number of TASK_STOPPED
	int traced = 0;				// number of TASK_TRACED
	int dead = 0;				// number of EXIT_DEAD
	int unknown = 0;			// number of unknown (other)
	int total = 0;				// number of all processes

	// int exit_state;
	// int state;
	struct task_struct *p = &init_task;	// process pointer
	// read_lock(&tasklist_lock);		// get the lock of tasklist
	// for(p=&init_task; (p = next_task(p))!=&init_task;)
	for_each_process(p){
		// output the info of a process
		printk("Name:%s, pid:%d, state:%ld, dad_name:%s\n", p->comm, p->pid, p->state, p->real_parent->comm);
		total++; // count the total number of processes
		// state = p->state;
		// exit_state = p->exit_state;
		
		switch(p->exit_state){
			case EXIT_ZOMBIE:	// zombie process
				zombie++; break;
			case EXIT_DEAD: 	// dead process
				dead++; break;
			default: 			// other
				break;
		}

		// if the process has exited, traverse the next directly
		if(p->exit_state != 0) continue;

		switch(p->state){
			case TASK_RUNNING:				// running process
				running++; break;
			case TASK_INTERRUPTIBLE:		// interruptible process
				interruptible++; break;
			case TASK_UNINTERRUPTIBLE:		// uninterruptible process
				uninterruptible++; break;
			case TASK_STOPPED:				// stopped process
				stopped++; break;
			case TASK_TRACED:				// traced process
				traced++; break;
			default:						// other (unknown) process
				unknown++; break;
		}
	}
	// read_unlock(&tasklist_lock);	// unlock tasklist

	// output the count result
	printk("total: %d\n", total);			// output the total number of processes
	printk("running: %d\n", running);		// output the number of TASK_RUNNING
	printk("interruptible: %d\n", total);	// output the number of TASK_INTERRUPTIBLE
	printk("uninterruptible: %d\n", total);	// output the number of TASK_UNINTERRUPTIBLE
	printk("traced: %d\n", traced);			// output the number of TASK_TRACED
	printk("stopped: %d\n", stopped);		// output the number of TASK_STOPPED
	printk("zombie: %d\n", zombie);			// output the number of EXIT_ZOMBIE
	printk("dead: %d\n", dead);				// output the number of EXIT_DEAD
	printk("unknown: %d\n", unknown);		// output the number of other processes
}

static int proc_init(void){
	printk("<proc_traverse> Hello~\n");	// initialization msg
	printk("###\n");	// symbol of beginning
	traverse_count();	// run the traversing function
	printk("###\n");	// symbol of ending
	return 0;
	
}

static void proc_exit(void){
	printk("<proc_traverse> Bye~\n"); 	// exiting msg
}

module_init(proc_init);	// register initialization module
module_exit(proc_exit);	// register exiting module
MODULE_LICENSE("GPL");	// GNU General Public License
