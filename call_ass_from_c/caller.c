#include<stdio.h>
#include<stdlib.h>

extern int called_add_ints(int, int);

int main(int argc, char const *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <int> <int>", argv[0]);
    }

    int a = atoi(argv[1]);
    int b = atoi(argv[2]);

    int sum = called_add_ints(a, b);

    printf("%i + %i = %i\n", a, b, sum);
    return 0;
}
