#include <stdio.h>

void    change_value(int i)
{
    i = 1;
}

int main()
{
    int i = 0;

    printf("%d\n", i);
    change_value(i);
    printf("%d\n", i);
}