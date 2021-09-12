#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sched/signal.h>
#include <linux/sched.h>

int process_init(void) {
    struct task_struct *task;

    printk(KERN_INFO "loading module\n");
    for_each_process(task) {
        printk(KERN_INFO "pid: %d |pname: %s |state: %ld\n", task->pid, task->comm, task->state);
    }

    return 0;
}

void process_exit(void) {
    printk(KERN_INFO "removing module\n");
}

module_init(process_init);
module_exit(process_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("SIMPLE MODULE");
MODULE_AUTHOR("廖昱瑋");