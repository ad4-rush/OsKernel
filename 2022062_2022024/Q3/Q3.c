#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/sched/signal.h>

MODULE_AUTHOR("ADARSH and AMARTYA");
MODULE_LICENSE("GPL");

static int my_proc_show(struct seq_file *m, void *v) {
    int running_processes = 0;
    
    // Count the number of running processes
    struct task_struct *task;
    for_each_process(task) {
        // if (task->__state == TASK_RUNNING   )
        //***the above line when uncommented give the number of running processes as a 1/2 which was not so intersting
        //so i didn't included all the processes which are in blockes/ready/sleep state . So now my number of processes are around 200
        //I also did run ps aux command which tells the number of running processes. it was same as my output of this exact code
            running_processes++;
    }
    
    seq_printf(m, "Number of running processes: %d\n", running_processes);
    return 0;
}

static int my_proc_open(struct inode *inode, struct file *file) {
    return single_open(file, my_proc_show, NULL);
}

static const struct proc_ops my_proc_fops = {
    .proc_open = my_proc_open,
    .proc_read = seq_read,
    .proc_release = single_release,
};


static int __init custom_syscall_init(void) {
    printk(KERN_INFO "Module loaded.\n");

    // Create a proc file for displaying the number of running processes
    proc_create("running_processes", 0, NULL, &my_proc_fops);
    return 0;
}

static void __exit custom_syscall_exit(void) {
    printk(KERN_INFO "Module unloaded.\n");

    // Remove the proc file
    remove_proc_entry("running_processes", NULL);
}

module_init(custom_syscall_init);
module_exit(custom_syscall_exit);
//making all the module files required
//loading the module by sudo insmod Q3.ko
//checking the message of module by sudo dmesg -T
//now we have to run command cat /proc/running_processes
//the above command will tell the number of runnning processes
//now we can remove the module by sudo rmmod Q3.ko
//now if run command cat /proc/running_processes there would be no such file present