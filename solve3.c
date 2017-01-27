/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dprovorn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 18:11:53 by dprovorn          #+#    #+#             */
/*   Updated: 2017/01/27 18:19:06 by dprovorn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	ft_put_change(int coord)
{
	ft_putstr("L");
	ft_putnbr(g_pos[coord]);
	ft_putchar('-');
	ft_putstr(g_names[coord]);
	ft_putchar(' ');
}

void	mark_node(int **paths, int option, int to_mark, int prev)
{
	int k;
	int i;

	k = -1;
	i = -1;
	while (paths[++k])
		;
	if (option == 0)
	{
		while (++i < k)
		{
			g_temp[paths[i][1]][paths[i][2]] = 9999;
			g_temp[paths[i][2]][paths[i][1]] = 9999;
		}
	}
	else
	{
		g_temp[paths[k - 1][1]][paths[k - 1][2]] = 9999;
		g_temp[paths[k - 1][2]][paths[k - 1][1]] = 9999;
		g_temp[to_mark][prev] = 9999;
		g_temp[prev][to_mark] = 9999;
	}
}

int		**copy_in_lpath(int **paths, int k)
{
	int i;
	int j;
	int **found_path;

	i = -1;
	found_path = (int**)malloc(sizeof(int*) * (k + 1));
	while (++i < k)
		found_path[i] = (int*)malloc(sizeof(int) * g_count);
	i = -1;
	while (++i < k)
	{
		j = -1;
		while (++j < paths[i][0] + 1)
			found_path[i][j] = paths[i][j];
	}
	found_path[k] = NULL;
	i = 0;
	found_path[k - 1][0] = g_p;
	while (++i <= g_p)
		found_path[k - 1][i] = g_path[i - 1];
	return (found_path);
}

int		**find_another(int **paths, int start, int end)
{
	FA;
	while (paths[++k])
		;
	while (++i < paths[k - 1][0])
	{
		j = -1;
		while (++j < k - 1)
		{
			m = 1;
			while (++m < paths[j][0])
				if (paths[k - 1][i] == paths[j][m])
				{
					mark_node(paths, 1, paths[j][m], paths[k - 1][i - 1]);
					g_p = 0;
					g_path[g_p++] = start;
					dijkstra(g_d, paths[k - 1][2], end);
					w = -1;
					while (++w < g_p)
						if (!(g_path[2] == end))
							found_path = copy_in_lpath(paths, k);
				}
		}
	}
	return (found_path);
}

void	copy_back(void)
{
	int i;
	int j;

	i = -1;
	while (++i < g_count)
	{
		j = -1;
		while (++j < g_count)
			g_temp[i][j] = g_tab[i][j];
	}
}
