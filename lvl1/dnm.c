#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <math.h>

int min(char *s)
{
    int o=0,c=0;
    while (*s)
    {
        if (*s == '(')
            o++;
        if (*s== ')')
            o? o-- : c++;
        s++;
    }
    return o+c;
}

int ok(char *s)
{
    int b = 0;
    while (*s)
    {
        if (*s == '(')
            b++;
        if (*s== ')' && --b < 0)
            return 0;
        s++;
    }
    return !b;
}

void solve(char *s, int i, int rm, char *b)
{
    if (!s[i])
    {
        if (!rm && ok(b))
                write(1, b, i), write(1, "\n", 1);
        return ;
    }
    b[i] = s[i];
    solve(s, i+1, rm, b);
    if (rm && (b[i] == '(' || s[i] == ')'))
    {
        b[i] = ' ';
        solve(s, i+1, rm-1, b);
    }
}

int main(int ac, char **av)
{
    char b[1024];
    if (ac!=2)
        return 1;
    solve(av[1], 0, min(av[1]), b);
}