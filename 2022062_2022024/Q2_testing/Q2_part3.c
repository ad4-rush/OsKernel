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
    struct timespec start_time_fifo; 
    struct timespec end_time_fifo;
    struct sched_param parameter;
    pid_t pid_three;
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
        if (i==2)
        {
        clock_gettime(CLOCK_REALTIME, &start_time_fifo);
        }
        pid_three = fork();
        if (pid_three == 0) { // This block will be run by the child process
            if (i == 0) {
                parameter.sched_priority = 0;
                sched_setscheduler(pid_three,SCHED_OTHER,&parameter);
                perror("\nSetting scheduling policy of process to sched_other ");
                pid_other = pid_three;
                execl("/home/amartya/Desktop/Codes/2022062_2022024/Q2_testing/counter_function", "counter_function", NULL);
            } else if (i == 1) {
                parameter.sched_priority = 1;               
                sched_setscheduler(pid_three,SCHED_RR,&parameter);
                perror("\nSetting scheduling policy of process to sched_rr ");
                pid_rr = pid_three;
                execl("/home/amartya/Desktop/Codes/2022062_2022024/Q2_testing/counter_function", "counter_function", NULL);
            } else if (i == 2) {
                parameter.sched_priority = 1;                
                sched_setscheduler(pid_three,SCHED_FIFO,&parameter);
                perror("\nSetting scheduling policy of process to sched_fifo ");
                pid_fifo = pid_three;
                execl("/home/amartya/Desktop/Codes/2022062_2022024/Q2_testing/counter_function", "counter_function", NULL);
            }
        }  
    }
    // Collecting process end-time     
    if (pid_fifo=waitpid(pid_fifo, NULL, 0) && fifo_done==0)
    {
        clock_gettime(CLOCK_REALTIME, &end_time_fifo);
        fifo_done=1;
    }


    printf("\nProcesses done, now writting into file third.\n");
    //Writing in the file
    FILE *pointer_third = fopen("/home/amartya/Desktop/Codes/2022062_2022024/Q2_testing/output.txt","a");

        fprintf(pointer_third,"Sched_fifo scheduling process takes %Lf \n",time_used(start_time_fifo.tv_sec,end_time_fifo.tv_sec,start_time_fifo.tv_nsec,end_time_fifo.tv_nsec));

    fclose(pointer_third);
    printf("\nNow, plotting. \n");
    return 0;
}