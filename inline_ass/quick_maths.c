#include <stdlib.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{
    int x = 3;
    int y = 5;
    int r = 0;

    asm(
        "ADD %2, %1"    // gets the second and third parameter (b, a) and transforms them into 64bit register calls (rbx, rax)
                        // --> uses Accumulator- and Base-register (https://en.wikibooks.org/wiki/X86_Assembly/X86_Architecture)
                        // also read https://www.cs.uaf.edu/2017/fall/cs301/lecture/09_11_registers.html
        : "=a" (r)      // r = rax, where the result of the addition is stored (in Linux, ADD stores in second parameter)
        : "a" (x), "b" (y)
    );

    printf("%i + %i = %i\n", x, y, r);

    asm(
        "MUL %2"
        : "=a" (r)
        : "a" (x), "b" (y)
    );

    printf("%i * %i = %i\n", x, y, r);

    return 0;
}
