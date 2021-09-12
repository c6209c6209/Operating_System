#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>

void dfs(struct task_struct *current_task) {
    struct task_struct *child;
    struct list_head *list;

    printk(KERN_INFO "pid: %d |pname: %s |state: %ld\n"
    ,current_task->pid, current_task->comm, current_task->state);

    list_for_each(list, &current_task->children) {
        child = list_entry(list, struct task_struct, sibling);
        dfs(child);
    }
}

int process_init(void) {
    printk(KERN_INFO "loading module\n");
    dfs(&init_task);
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