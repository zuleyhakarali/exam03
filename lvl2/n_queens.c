#include <stdlib.h>
#include <unistd.h>

static int	is_safe(int *pos, int col, int row)
{
	int i;

	i = 0;
	while (i < col)
	{
		if (pos[i] == row || abs(pos[i] - row) == col - i)
			return 0;
		i++;
	}
	return 1;
}

static void	print_solution(int *pos, int n)
{
	int i;
	char c;

	i = 0;
	while (i < n)
	{
		c = pos[i] + '0';
		write(1, &c, 1);
		if (i + 1 < n)
			write(1, " ", 1);
		i++;
	}
	write(1, "\n", 1);
}

static void	solve(int *pos, int col, int n)
{
	int row;

	if (col == n)
	{
		print_solution(pos, n);
		return;
	}
	row = 0;
	while (row < n)
	{
		if (is_safe(pos, col, row))
		{
			pos[col] = row;
			solve(pos, col + 1, n);
		}
		row++;
	}
}

int	main(int ac, char **av)
{
	int n;
	int *pos;

	if (ac != 2)
		return 1;
	n = atoi(av[1]);
	if (n <= 0)
		return 1;
	pos = calloc(n, sizeof(int));
	if (!pos)
		return 1;
	solve(pos, 0, n);
	free(pos);
	return 0;
}