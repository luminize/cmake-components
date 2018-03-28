#include <iostream>
//#include <string.h>
//#include <stdlib.h>
//#include <stdint.h>
//#include <vector>
#include <string>


void read_foo(std::string foo)
{
    std::cout << foo << std::endl;
}

void update_bar(std::string bar)
{
    std::cout << bar << std::endl;
}

void write_baz(std::string baz)
{
    std::cout << baz << std::endl;
}

int main()
{
    unsigned long addr = 0;
    read_foo("str_foo");
    update_bar("str_bar");
    write_baz("str_baz");

    printf("adress read_foo   : %p\n", &read_foo);
    printf("adress update_bar : %p\n", &update_bar);
    printf("adress write_baz  : %p\n", &write_baz);
    //printf("\n");
    addr = (unsigned long)&read_foo;
    printf("adress read_foo   : %ld\n", addr);
    addr = (unsigned long)&update_bar;
    printf("adress update_bar : %ld\n", addr);
    addr = (unsigned long)&write_baz;
    printf("adress write_baz  : %ld\n", addr);

    while (1)
    {
        // eternal loop doing nothing
    }
}