#include "header.h"

int ft_min(int x, int y)
{
	if (x < y)
		return (x);
	else
		return (y);
}

void	ft_create_D(int ***D)
{
	int i;

	*D = (int**)malloc(sizeof(int*) * g_count);
	i = -1;
	while (++i < g_count)
		*(*D + i) = (int*)malloc(sizeof(int) * g_count);
}