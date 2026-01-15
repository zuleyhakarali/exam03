#include <unistd.h>

static int len(char *s)
{
	int i = 0;
	while (s[i])
		i++;
	return i;
}

static void print(char *s, int n)
{
	write(1, s, n);
	write(1, "\n", 1);
}

static void count_remove(char *s, int *l, int *r)
{
	int i = 0, bal = 0;
	*l = 0;
	*r = 0;

	while (s[i])
	{
		if (s[i] == '(')
			bal++;
		else if (s[i] == ')')
		{
			if (bal == 0)
				(*r)++;
			else
				bal--;
		}
		i++;
	}
	*l = bal;
}

static void dfs(char *s, int n, int i, int bal, int l, int r)
{
	if (i == n)
	{
		if (bal == 0 && l == 0 && r == 0)
			print(s, n);
		return;
	}

	if (s[i] == '(')
	{
		if (l > 0)
		{
			char c = s[i];
			s[i] = ' ';
			dfs(s, n, i + 1, bal, l - 1, r);
			s[i] = c;
		}
		dfs(s, n, i + 1, bal + 1, l, r);
	}
	else if (s[i] == ')')
	{
		if (r > 0)
		{
			char c = s[i];
			s[i] = ' ';
			dfs(s, n, i + 1, bal, l, r - 1);
			s[i] = c;
		}
		if (bal > 0)
			dfs(s, n, i + 1, bal - 1, l, r);
	}
	else
		dfs(s, n, i + 1, bal, l, r);
}

int main(int ac, char **av)
{
	int l, r, n;

	if (ac != 2)
		return 0;

	n = len(av[1]);
	count_remove(av[1], &l, &r);
	dfs(av[1], n, 0, 0, l, r);
}