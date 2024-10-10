// usage: anton numberOfGreetings delay
#include<stdio.h>
#include<stdlib.h>

void work(size_t number, size_t delay);
void active_wait(size_t delay);

int main(int argc, char const *argv[])
{
    // disable stdout buffer for immediate output
    setbuf(stdout, 0);
    // check for correct number of arguments
    if (argc != 3)
    {
        printf("usage: %s numberOfGreetings delay\n", argv[0]);
        return 1;
    }

    // convert arguments to integers
    size_t number = atoi(argv[1]);
    size_t delay = atoi(argv[2]);

    // call work function
    work(number, delay);
    printf("Done\n");
    // return 0 to indicate success
    return 0;
}

void work(size_t number, size_t delay)
{
    for (size_t i = 0; i < number; i++)
    {
        printf("Hallo Anton!\t");
        active_wait(delay);
    }
    putchar('\n'); 
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
