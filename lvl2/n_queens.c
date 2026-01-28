#include <stdlib.h>
#include <stdio.h>

int ok(int *q, int r, int col)
{
    int i = 0;
    while (i < col)
    {
        if (q[i] == r || q[i] - i == r - col || q[i] + i == r + col)
            return 0;
        i++;
    }
    return 1;
}

void solve(int *q, int n, int col)
{
    int r;
    if (col == n)
    {
        for (r = 0; r < n; r++)
            printf("%d%c", q[r], r == n - 1 ? '\n' : ' ');
        return;
    }
    for (r = 0; r < n; r++)
    {
        if (ok(q, r, col))
        {
            q[col] = r;
            solve(q, n, col + 1);
        }
    }
}

int main(int ac, char **av)
{
    int n, *q;
    if (ac != 2)
        return 1;
    n = atoi(av[1]);
    q = calloc(n, sizeof(int));
    solve(q, n, 0);
    free(q);
    return 0;
}