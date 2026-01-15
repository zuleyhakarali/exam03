#define _GNU_SOURCE
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

int main(int ac, char **av)
{
    char buf[4096];
    char *new = NULL;
    char *pos;
    size_t len, old_len, i;
    ssize_t r, j;

    if (ac != 2 || !av[1][0])
        return (perror("Error"), 1);
    len = strlen(av[1]);
    while ((r = read(0, buf, sizeof(buf))) > 0)
    {
        old_len = new ? strlen(new) : 0;
        new = realloc(new, old_len + r + 1);
        if (!new)
            return (perror("Error"), 1);
        for (j = 0; j < r; j++)
            new[old_len + j] = buf[j];
        new[old_len + r] = '\0';
        while ((pos = memmem(new, strlen(new), av[1], len)))
        {
            write(1, new, pos - new);
            for (i = 0; i < len; i++)
                write(1, "*", 1);
            mem move(new, pos + len, strlen(pos + len) + 1);
        }
    }
    if (r < 0)
        return (perror("Error"), 1);
    if (new)
        write(1, new, strlen(new));
    free(new);
}
