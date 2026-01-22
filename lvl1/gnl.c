#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>
#include <fcntl.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 15
#endif

char *ft_strchr(char *s, int c)
{
    if (!s)
        return NULL;
    while(*s && *s != (char)c)
        s++;
    if (*s == (char)c)
        return s;
    return NULL;
}

void *ft_memcpy(void *dest, const void *src, size_t n)
{
    size_t i = 0;
    if (!dest || !src)
        return dest;
    while(i < n)
    {
        ((char *)dest)[i] = ((char *)src)[i];
        i++;
    }
    return dest;
}

size_t ft_strlen(char *s)
{
    size_t i = 0;
    if (!s)
        return 0;
    while (s[i])
        i++;
    return i;
}

char *str_append_mem(char **s1, char *s2, size_t size2)
{
    size_t size1 = ft_strlen(*s1);
    char *tmp = malloc(size2 + size1 + 1);
    if (!tmp)
        return NULL;
    if (*s1)
        ft_memcpy(tmp, *s1, size1);
    ft_memcpy(tmp + size1, s2, size2);
    tmp[size1 + size2] = '\0';
    free(*s1);
    *s1 = tmp;
    return tmp; 
}

void *ft_memmove(void *dest, const void *src, size_t n)
{
    size_t i;
    if (!dest || !src || dest == src || n == 0)
        return dest;
    if (dest > src)
    {
        i = n;
        while(i-- > 0)
            ((char *)dest)[i] = ((char *)src)[i];
    }
    else
    {
        i = 0;
        while (i < n)
        {
            ((char *)dest)[i] = ((char *)src)[i];
            i++;
        }
    }
    return dest;
}

char *get_next_line(int fd)
{
    static char b[BUFFER_SIZE + 1];
    char *line = NULL, *nl;
    ssize_t r;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return NULL;
    while (1)
    {
        nl = ft_strchr(b, '\n');
        if (nl)
        {
            if (!str_append_mem(&line, b, nl - b + 1))
                return NULL;
            ft_memmove(b, nl + 1, ft_strlen(nl + 1) + 1);
            return line;
        }
        if (*b)
            if (!str_append_mem(&line, b, ft_strlen(b)))
                return NULL;
        b[0] = '\0';
        r = read(fd, b, BUFFER_SIZE);
        if (r <= 0)
            return (r == 0 ? line : NULL);
        b[r] = '\0';
    }
}

int main()
{
    char *line;
    int fd=open("deneme.txt", O_RDONLY);
    while((line = get_next_line(fd)))
    {
        printf("%s", line);
        free(line);
    }
}