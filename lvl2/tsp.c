#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct{
    float x, y;
} city;

void swap(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

float dist(city a, city b)
{
    float dx = a.x - b.x;
    float dy = a.y - b.y;
    return sqrtf(dx*dx + dy*dy);
}

float path(city *c, int *or, int n)
{
    float len =0;
    int i;
    for(i=0;i<n-1;i++)
        len += dist(c[or[i]], c[or[i+1]]);
    len += dist(c[or[n-1]], c[or[0]]);
    return len;
}

void permut(city *c, int *or, int n, int idx, float *min)
{
    int i;
    float len;
    if (idx == n)
    {
        len =path(c, or, n);
        if (len < *min)
            *min = len;
        return ;
    }
    for(i = 0;i < n;i++)
    {
        swap(&or[idx], &or[i]);
        permut(c, or, n, idx+1, min);
        swap(&or[idx], &or[i]);
    }
}

int main()
{
    city c[11];
    int or[11], n = 0, i;
    float min = 1e9;
    while (fscanf(stdin, "%f, %f\n", &c[n].x, &c[n].y) == 2)
        n++;
    for(i=0;i<n;i++)
        or[i] = i;
    permut(c, or, n, 0, &min);
    printf("%.2f\n", min);
}