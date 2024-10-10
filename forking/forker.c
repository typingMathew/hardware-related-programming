#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void active_wait(size_t delay);

pid_t process_number = 1;

int main(int argc, char const *argv[])
{
    for (size_t i = 0; i < 2; i++)
    {
        process_number <<= 1;
        int ret = fork();
        if (ret < 0)
        {
            printf("Fork failed\n");
            return 1;
        }
        else if (ret == 0){
            printf("I am the child. My PID is %i and my Parent-PID is %i \n", getpid(), getppid());
        }
        else{
            printf("I am the parent. My PID is %i\n", getpid());
        }
    }
    
    active_wait(5000);
    
    printf("Number of processes: %i\n", process_number);
    return 0;
}

void active_wait(size_t delay)
{
    for (size_t i = 0; i < delay; i++)
    {
        for (size_t j = 0; j < delay; j++)
        {
            j++;
            j--;
        }
    }
}
