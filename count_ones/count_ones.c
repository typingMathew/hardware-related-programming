// Aufruf: count_ones <Dezimalzahl>
// Zählt die binären Einsen in einer Dezimalzahl
// Dabei wird zuerst inline die Assemblerfunktion popcnt verwendet und deren Zeit gemessen
// Danach wird selbiges über ein C-Schleifenkonstrukt evaluiert und dessen Zeit gemessen

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<stdint.h>

typedef int (* const decorableFnType)(int64_t paramOne);

int count_asm(int64_t number) {
    int64_t ones = 0;
    __asm__(
        "popcnt %1, %0"
        : "=r" (ones)
        : "r" (number)
    );
    return ones;
}

int count_c(int64_t number) {
    int ones = 0;
    while (number)
    {
        ones += number & 1;
        number >>= 1;
    }
    return ones;
}

int count_time(decorableFnType fn, int64_t paramOne) {
    struct timespec start, end;
    int ret_val;
    // get start time
    ret_val = clock_gettime(0, &start);
    if (ret_val != 0) {
        perror("clock_gettime");
        return 1;
    }
    // call function
    int ones = fn(paramOne);
    // get end time
    ret_val = clock_gettime(0, &end);
    if (ret_val != 0) {
        perror("clock_gettime");
        return 1;
    }
    // get diff time in nanoseconds
    int t_ns = (int)(end.tv_sec - start.tv_sec) * 1.0e9 +
              (int)(end.tv_nsec - start.tv_nsec);
    printf("Time taken by %s: %i ns\n", fn == count_asm ? "ASM" : "C", t_ns);
    return ones;
}

int main(int argc, char const *argv[]) {
    if (argc != 2) {
        printf("Aufruf: %s <Dezimalzahl>\n", argv[0]);
        return 1;
    }

    int64_t number = atol(argv[1]);
    
    int ones = count_time(count_asm, number);
    printf("Number of ones in %ld is %d\n", number, ones);

    ones = count_time(count_c, number);
    printf("Number of ones in %ld is %d\n", number, ones);

    return 0;
}
