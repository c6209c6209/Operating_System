#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/list.h>
#include <linux/slab.h>

struct student {
    int id, year, month, day;
    struct list_head studentList;
};

LIST_HEAD(studentLinkedList);

int student_init(void) {
    struct student *newStudent;
    struct student *temp = NULL;
    int i;
    for (i = 0; i < 5; i++) {
        newStudent = kmalloc(sizeof(*newStudent), GFP_KERNEL);
        newStudent->id = i;
        newStudent->year = i*2;
        newStudent->month = i*2;
        newStudent->day = i*2;
        INIT_LIST_HEAD(&newStudent->studentList);
        list_add_tail(&newStudent->studentList, &studentLinkedList);
    }

    list_for_each_entry (temp, &studentLinkedList, studentList) {
        printk("%d, %d-%d-%d\n", temp->id, temp->day, temp->month, temp->year);
    }

    return 0;
}

void student_exit(void){
    struct student *temp, *next;
    list_for_each_entry_safe(temp, next, &studentLinkedList, studentList) {
        printk("Removing student_%d\n", temp->id);
        list_del(&temp->studentList);
        kfree(temp);
    }
}

module_init(student_init);
module_exit(student_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("OS hw1");
MODULE_AUTHOR("c6209c6209");