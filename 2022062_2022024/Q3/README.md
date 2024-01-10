# Linux Kernel Module for Counting Processes

This is a Linux kernel module that creates a `/proc` file named `running_processes`. When read, this file shows the number of processes in the system.

## Code Structure

The code is structured as follows:

1. *Module Metadata*: The `MODULE_AUTHOR` and `MODULE_LICENSE` macros provide information about the module's author and license.

2. *my_proc_show Function*: This function counts the number of processes in the system and writes this count to a `seq_file`.

3. *my_proc_open Function*: This function opens the `seq_file`.

4. *my_proc_fops Structure*: This structure defines the file operations for the `/proc` file.

5. *custom_syscall_init Function*: This is the module's initialization function. It creates the `/proc` file when the module is loaded.

6. *custom_syscall_exit Function*: This is the module's exit function. It removes the `/proc` file when the module is unloaded.

## Usage

To use this module, follow these steps:

1. Compile the module with a Linux kernel build system.
2. This command will clear all the log message of kernel `sudo dmesg -C`.
3. Load the module with `sudo insmod Q3.ko`.
4. Check the kernel log messages with `sudo dmesg -T` to confirm that the module was loaded successfully.
5. Read the `/proc/running_processes` file with `cat /proc/running_processes` to see the number of running processes.
6. Unload the module with `sudo rmmod Q3.ko`.
7. Check the kernel log messages with `sudo dmesg -T` to confirm that the module was unloaded successfully.
8. If you try to read `/proc/running_processes` again, you'll see that there's no such file because it was removed when the module was unloaded.

## Dependencies

This program requires the following headers:

- `linux/init.h`
- `linux/module.h`
- `linux/kernel.h`
- `linux/proc_fs.h`
- `linux/seq_file.h`
- `linux/sched/signal.h`

## Assumptions
`Number of Processes`

In this project, we provide information about the number of processes in the system. While it is possible to count the number of running processes, it's also important to consider all processes, including those that may be in a sleeping or blocked state. This distinction can be crucial for understanding the system's current state and resource utilization. I ran command `ps aux` which tells the number of processes and state and it turned out be same as given by my code.

By default, the code does not distinguish between running, sleeping, or blocked processes. Instead, it displays the total number of processes, including those in various states. This approach provides a comprehensive view of the system's process activity.


`Counting Running Processes`

If you wish to specifically count only the number of running processes, you can do so by uncommenting the line of code (e.g., line number 17) in the codebase that enables this feature. However, it's important to note that in some cases, you may observe that the number of running processes remains consistently low (e.g., 1) depending on the system and the specific conditions under which the code is run. When I run `htop` command on my terminal the result of this was matching. There was only 1 process in running state.  