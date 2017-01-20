#include "header.h"

int ft_min(int x, int y)
{
	if (x < y)
		return (x);
	else
		return (y);
}

void	ft_create_d(int ***d)
{
	int i;

	*d = (int**)malloc(sizeof(int*) * g_count);
	i = -1;
	while (++i < g_count)
		*(*d + i) = (int*)malloc(sizeof(int) * g_count);
}
