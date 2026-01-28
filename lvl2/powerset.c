#include <stdio.h>
#include <stdlib.h>

void ft(int *ar, int size, int tar, int idx, int *s, int sub_s)
{
    int i;
    if (tar == 0)
    {
        for (i = 0; i < sub_s; i++)
            printf("%d%c", s[i], i == sub_s - 1 ? '\n' : ' ');
        if (sub_s == 0)
            printf("\n");
        return;
    }
    if (idx == size)
        return;
    s[sub_s] = ar[idx];
    ft(ar, size, tar - ar[idx], idx + 1, s, sub_s + 1);
    ft(ar, size, tar, idx + 1, s, sub_s);
}

int main(int ac, char **av)
{
    int tar, size, i, *ar, *s;
    if (ac < 2)
        return 1;
    tar = atoi(av[1]);
    size = ac - 2;
    ar = malloc(sizeof(int) * size);
    s = malloc(sizeof(int) * size);
    if (!ar || !s)
        return 1;
    for (i = 0; i < size; i++)
        ar[i] = atoi(av[i + 2]);
    ft(ar, size, tar, 0, s, 0);
    free(ar);
    free(s);
}