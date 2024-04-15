// usage: anton numberOfGreetings delay
#include<stdio.h>
#include<stdlib.h>

void work(int number, int delay);
void active_wait(int delay);

int main(int argc, char const *argv[])
{
    setbuf(stdout, 0); // disable stdout buffer
    if (argc != 3)
    {
        printf("usage: %s numberOfGreetings delay\n", argv[0]);
        return 1;
    }

    int number = atoi(argv[1]);
    int delay = atoi(argv[2]);

    work(number, delay);
    printf("Done\n");
    return 0;
}

void work(int number, int delay)
{
    for (size_t i = 0; i < number; i++)
    {
        printf("Hallo Caesar!\t");
        active_wait(delay);
    }
    putchar('\n');
    
}

void active_wait(int delay)
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
