#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct s_pt
{
	float x;
	float y;
}	t_pt;

static float dist(t_pt a, t_pt b)
{
	float dx = a.x - b.x;
	float dy = a.y - b.y;
	return sqrtf(dx * dx + dy * dy);
}

static float path_len(t_pt *p, int *ord, int n)
{
	float len = 0;
	int i = 0;

	while (i < n - 1)
	{
		len += dist(p[ord[i]], p[ord[i + 1]]);
		i++;
	}
	len += dist(p[ord[n - 1]], p[ord[0]]);
	return len;
}

static void swap(int *a, int *b)
{
	int t = *a;
	*a = *b;
	*b = t;
}

static void permute(t_pt *p, int *ord, int l, int n, float *best)
{
	int i;
	float cur;

	if (l == n)
	{
		cur = path_len(p, ord, n);
		if (*best < 0 || cur < *best)
			*best = cur;
		return;
	}
	i = l;
	while (i < n)
	{
		swap(&ord[l], &ord[i]);
		permute(p, ord, l + 1, n, best);
		swap(&ord[l], &ord[i]);
		i++;
	}
}

int main(void)
{
	t_pt	*p = NULL;
	int		*ord = NULL;
	int		n = 0;
	float	best = -1;

	while (1)
	{
		t_pt tmp;
		if (fscanf(stdin, "%f, %f\n", &tmp.x, &tmp.y) != 2)
			break;
		p = realloc(p, sizeof(t_pt) * (n + 1));
		p[n++] = tmp;
	}
	if (n == 0)
		return 0;

	ord = malloc(sizeof(int) * n);
	for (int i = 0; i < n; i++)
		ord[i] = i;

	permute(p, ord, 0, n, &best);
	printf("%.2f\n", best);

	free(p);
	free(ord);
	return 0;
}