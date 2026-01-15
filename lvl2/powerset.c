#include <unistd.h>
#include <stdlib.h>

static void	putnbr(int n)
{
	char c;

	if (n < 0)
	{
		write(1, "-", 1);
		n = -n;
	}
	if (n >= 10)
		putnbr(n / 10);
	c = '0' + (n % 10);
	write(1, &c, 1);
}

static void	print_subset(int *subset, int size)
{
	int i = 0;

	while (i < size)
	{
		if (i > 0)
			write(1, " ", 1);
		putnbr(subset[i]);
		i++;
	}
	write(1, "\n", 1);
}

static void	backtrack(
	int *arr, int len,
	int target, int idx,
	int sum, int *subset, int sub_size)
{
	if (sum == target)
    {
		print_subset(subset, sub_size);
        return ;
    }
	if (idx >= len)
		return;
	backtrack(arr, len, target, idx + 1, sum, subset, sub_size);
	subset[sub_size] = arr[idx];
	backtrack(arr, len, target, idx + 1,
		sum + arr[idx], subset, sub_size + 1);
}

int	main(int ac, char **av)
{
	int	target;
	int	*arr;
	int	*subset;
	int	len;
	int	i;

	if (ac < 2)
		return 0;

	target = atoi(av[1]);
	len = ac - 2;

	arr = malloc(sizeof(int) * len);
	subset = malloc(sizeof(int) * len);
	if (!arr || !subset)
		return 1;

	i = 0;
	while (i < len)
	{
		arr[i] = atoi(av[i + 2]);
		i++;
	}
	backtrack(arr, len, target, 0, 0, subset, 0);
	free(arr);
	free(subset);
	return 0;
}