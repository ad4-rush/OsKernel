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
    struct timespec start_time_rr; 
    struct timespec end_time_rr;
    struct sched_param parameter;
    pid_t pid_two;
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
        if (i==1)
        {
        clock_gettime(CLOCK_REALTIME, &start_time_rr);
        }
        pid_two = fork();
        if (pid_two == 0) { // This block will be run by the child process
            if (i == 0) {
                parameter.sched_priority = 0;
                sched_setscheduler(pid_two,SCHED_OTHER,&parameter);
                perror("\nSetting scheduling policy of process to sched_other ");
                pid_other = pid_two;
                execl("/home/amartya/Desktop/Codes/2022062_2022024/Q2_testing/counter_function", "counter_function", NULL);
            } else if (i == 1) {
                parameter.sched_priority = 1;               
                sched_setscheduler(pid_two,SCHED_RR,&parameter);
                perror("\nSetting scheduling policy of process to sched_rr ");
                pid_rr = pid_two;
                execl("/home/amartya/Desktop/Codes/2022062_2022024/Q2_testing/counter_function", "counter_function", NULL);
            } else if (i == 2) {
                parameter.sched_priority = 1;                
                sched_setscheduler(pid_two,SCHED_FIFO,&parameter);
                perror("\nSetting scheduling policy of process to sched_fifo ");
                pid_fifo = pid_two;
                execl("/home/amartya/Desktop/Codes/2022062_2022024/Q2_testing/counter_function", "counter_function", NULL);
            }
        }  
    }
    // Collecting process end-time      
    if (pid_rr=waitpid(pid_rr, NULL, 0) && rr_done==0)
    {
        clock_gettime(CLOCK_REALTIME, &end_time_rr);
        rr_done=1;
    }
    printf("\nProcesses done, now writting into file second.\n");
    //Writing in the file
    FILE *pointer_two = fopen("/home/amartya/Desktop/Codes/2022062_2022024/Q2_testing/output.txt","a");

        fprintf(pointer_two,"Sched_rr scheduling process takes %Lf \n",time_used(start_time_rr.tv_sec,end_time_rr.tv_sec,start_time_rr.tv_nsec,end_time_rr.tv_nsec));

    fclose(pointer_two);
    return 0;
}