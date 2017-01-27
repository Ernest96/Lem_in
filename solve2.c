#include "header.h"

void	dijkstra(int **d, int start, int end)
{
	INIT_DIJKSTRA;
	while (++k < g_count)
	{
		if (k == 0)
		{
			ft_memcpy(d[k], g_temp[start], sizeof(int) * g_count);
			m[g_m++] = start;
			marked[start] = 1;
			v = find_min(d[k], marked, m);
		}
		else
		{
			i = -1;
			while (++i < g_count)
				if (marked[i] == 0)
					d[k][i] = ft_min(d[k - 1][i], d[k - 1][v] + g_temp[v][i]);
				else
					d[k][i] = d[k - 1][i];
			v = find_min(d[k], marked, m);
		}	
	}
	--g_m;
	g_path[g_p++] = start;
	find_path(d, g_count - 1, end, m);
	g_path[g_p++] = end;
}

int		ft_check_solution_1(int start, int end, int *path)
{
	if(*path== start && *(path + 1) == end)
		if (g_temp[start][end] == 9999)
			return (0);
	return(1);
}

int		ft_check_solution_2(int start, int end, int *path)
{
	if(*(path + 1) == start && *(path + 2) == end)
	{
		if (g_temp[start][end] == 9999)
			return (0);
	}
	return (1);
}

int 	**ft_init_path(int start)
{
	int **paths;
	int i;
	int j;
	int n;

	n = 0;
	i = 0;
	j = -1;
	while (++j < g_count)
		if (g_temp[start][j] == 1)
			++n;

	paths = (int**)malloc(sizeof(int *) * (n + 1));
	j = -1;
	*paths  = (int*)malloc(sizeof(int) * (g_count + 1));
	paths[0][0] = g_p;
	while (++i <= g_p)
		paths[0][i] = g_path[i - 1];
	paths[1] = NULL;
	return (paths);
}

void	reset_sim(int *sim)
{
	int i;

	i = -1;
	while (++i < g_count)
	{
		sim[i] = 0;
		g_pos[i] = 0;
	}
}