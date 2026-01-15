#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>
#include <fcntl.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 15
#endif

char *ft(char *s1, char *s2, int len)
{
    int l = 0, i = -1;
    char *res;

    while (s1 && s1[l])
        l++;
    res = malloc(len + l + 1);
    if (!res)
        return (free(s1), NULL);
    while (++i < l)
        res[i] = s1[i];
    i = -1;
    while (++i < len)
        res[l + i] = s2[i];
    res[l + len] = '\0';
    return (free(s1), res);
}

char *gnl(int fd)
{
    static char buf[BUFFER_SIZE + 1];
    char *line = NULL;
    char *nl;
    size_t r;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return NULL;
    while (1)
    {
        nl = buf;
        while (*nl && *nl != '\n')
            nl++;
        if (*nl == '\n')
        {
            line = ft(line, buf, nl - buf + 1);
            if (!line)
                return NULL;
            int i = 0, j = nl - buf + 1;
            while (buf[j])
                buf[i++] = buf[j++];
            buf[i] = '\0';
            return line;
        }
        if (*buf)
        {
            line = ft(line, buf, nl - buf);
            if (!line)
                return NULL;
        }
        r = read(fd, buf, BUFFER_SIZE);
        if (r <= 0)
            return (r == 0 && line ? line : (free(line), NULL));
        buf[r] = '\0';
    }
}

int main()
{
    int fd;
    char *line;
    fd=open("deneme.txt", O_RDONLY);
    while((line = gnl(fd)))
    {
        printf("%s", line);
        free(line);
    }
}