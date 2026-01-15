#include <unistd.h>
#include <stdlib.h>

static void	swap(char *a, char *b)
{
	char t = *a;
	*a = *b;
	*b = t;
}

static void	sort_str(char *s)
{
	int i, j;

	i = 0;
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

static void	print(char *s)
{
	int i = 0;
	while (s[i])
		write(1, &s[i++], 1);
	write(1, "\n", 1);
}

static void	permute(char *s, int l)
{
	int i;

	if (!s[l])
	{
		print(s);
		return;
	}
	i = l;
	while (s[i])
	{
		swap(&s[l], &s[i]);
		permute(s, l + 1);
		swap(&s[l], &s[i]);
		i++;
	}
}

int	main(int ac, char **av)
{
	char *s;

	if (ac != 2)
		return 1;
	s = av[1];
	if (!*s)
		return 0;
	sort_str(s);
	permute(s, 0);
	return 0;
}