#include <stdio.h>
#include <unistd.h>
#include<sys/wait.h>
#include<sched.h>
#include <time.h>

long double time_used(long sec_s,long sec_e,long nsec_s,long nsec_e){
    long double result=0.0;
    result =result+(sec_e-sec_s);
    long double accuracy = (nsec_e-nsec_s)/1000000000.0;
    result=(float)result+accuracy;
    return result;
}

int main(int argc, char const *argv[])
{
    int i;
    int temp_variable;
    struct timespec start_time_other; 
    struct timespec end_time_other;
    struct sched_param parameter;
    pid_t pid;
    pid_t pid_other;
    pid_t pid_rr;
    pid_t pid_fifo;
    int other_done=0;
    int rr_done=0;
    int fifo_done=0;
    long double time_other;
    long double time_rr;
    long double time_fifo;
    printf(" \nStarting program to create processes. \n ");
    // Creating processes
    for (i = 0; i < 3; i++) {
        if (i==0)
        {
        clock_gettime(CLOCK_REALTIME, &start_time_other);
        }
        pid = fork();
        if (pid == 0) { // This block will be run by the child process
            if (i == 0) {
                parameter.sched_priority = 0;
                sched_setscheduler(pid,SCHED_OTHER,&parameter);
                perror("\nSetting scheduling policy of process to sched_other ");
                pid_other = pid;
                execl("/home/amartya/Desktop/Codes/2022062_2022024/Q2_testing/counter_function", "counter_function", NULL);
            } else if (i == 1) {
                parameter.sched_priority = 1;               
                sched_setscheduler(pid,SCHED_RR,&parameter);
                perror("\nSetting scheduling policy of process to sched_rr ");
                pid_rr = pid;
                execl("/home/amartya/Desktop/Codes/2022062_2022024/Q2_testing/counter_function", "counter_function", NULL);
            } else if (i == 2) {
                parameter.sched_priority = 1;                
                sched_setscheduler(pid,SCHED_FIFO,&parameter);
                perror("\nSetting scheduling policy of process to sched_fifo ");
                pid_fifo = pid;
                execl("/home/amartya/Desktop/Codes/2022062_2022024/Q2_testing/counter_function", "counter_function", NULL);
            }
        }  
    }
    // Collecting process end-time         
    if (pid_other=waitpid(pid_other, NULL, 0))
    {
    clock_gettime(CLOCK_REALTIME, &end_time_other);
    other_done=1;
    }
    printf("\nProcesses done, now writting into file first.\n");
    //Writing in the file
    FILE *pointer = fopen("/home/amartya/Desktop/Codes/2022062_2022024/Q2_testing/output.txt","a");
    fprintf(pointer,"Sched_other scheduling process takes %Lf \n",time_used(start_time_other.tv_sec,end_time_other.tv_sec,start_time_other.tv_nsec,end_time_other.tv_nsec));
    fclose(pointer);
    return 0;
}