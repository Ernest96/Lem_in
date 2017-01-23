#include "header.h"

int ft_min(int x, int y)
{
	if (x < y)
		return (x);
	else
		return (y);
}

void	ft_create_d_path()
{
	int j;
	int i;

	g_d = (int**)malloc(sizeof(int*) * g_count);
	i = -1;
	while (++i < g_count)
		*(g_d + i) = (int*)malloc(sizeof(int) * g_count);
	g_path = (int*)malloc(sizeof(int) * (g_count + 1));
	g_temp = (int**)malloc(sizeof(int*) * g_count);
   	i = -1;
	while (++i < g_count)
	*(g_temp + i) = (int*)malloc(sizeof(int) * g_count);
	i = -1;
	while (++i < g_count)
	{
		j = -1;
		while (++j < g_count)
			g_temp[i][j] = g_tab[i][j];
	}
}
