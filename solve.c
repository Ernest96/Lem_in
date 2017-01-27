#include "header.h"

int		find_min(int *d, int8_t *marked, int *m)
{
	int min;
	int v;
	int i;

	min = INT_MAX;
	i = -1;
	while (++i < g_count)	
		if (d[i] < min && marked[i] == 0)
			{
				v = i;
				min = d[i];
			}
	m[g_m++] = v;
	marked[v] = 1;
	return (v);
}

void	find_path(int **d, int vert, int i, int *m)
{
	if (vert == 0)
		return ;
	if (d[vert - 1][i] != d[vert][i])
	{
		find_path(d, vert - 1, m[vert], m);
		g_path[g_p++] = m[vert];
	}
	else
		find_path(d, vert - 1, i, m);
}

int 	*get_m()
{
	int i;
	int *m;

	m = (int*)malloc(sizeof(int) * g_count);
	i = -1;
	while (++i < g_count)
		*(m + i) = 0;
	return (m);
}

int8_t 	*get_marked()
{
	int 	i;
	int8_t	*marked;

	marked = (int8_t*)malloc(sizeof(int8_t) * g_count);
	i = -1;
	while (++i < g_count)
		*(marked + i) = 0;
	return (marked);
}
