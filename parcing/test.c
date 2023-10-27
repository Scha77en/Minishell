#include <stdio.h>

char   *change_value(char *str)
{
    str = "No";
}

int main()
{
    char *str[] = {"hello", "world"};

    char *ok = change_value(*str);
    printf("str = %s\n", str[0]);
    printf("ok = %s\n", ok);
}