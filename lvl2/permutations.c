#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

void swap(char *a, char *b)
{
    char tmp = *a;
    *a = *b;
    *b = tmp;
}

void sort(char *s)
{
    int i = 0, j;
    while (s[i])
    {
        j = i + 1;
        while (s[j])
        {
            if (s[i] > s[j])
                swap(&s[i], &s[j]);
            j++;
        }
        i++;
    }
}

int len(char *s)
{
    int i = 0;
    while (s[i])
        i++;
    return i;
}

void rev(char *s, int start)
{
    int end = len(s) - 1;
    while (start < end)
    {
        swap(&s[start], &s[end]);
        start++;
        end--;
    }
}

int permut(char *s)
{
    int i = len(s) - 2;
    int j = len(s) - 1;
    while (i >= 0 && s[i] >= s[i + 1])
        i--;
    if (i < 0)
        return 0;
    while(s[j] <= s[i])
        j--;
    swap(&s[i], &s[j]);
    rev(s, i + 1);
    return 1;  
}

int main(int ac, char **av)
{
    if (ac != 2 || !av[1][0])
        return 1;
    char *s;
    s = av[1];
    sort(s);
    puts(s);
    while (permut(s))
        puts(s);
}