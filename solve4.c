/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dprovorn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 17:29:49 by dprovorn          #+#    #+#             */
/*   Updated: 2017/01/27 17:31:40 by dprovorn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		try_all(int ***paths, int furn, int start, int end)
{
	static int flag = 0;

	TA;
	if (flag == 0 && (flag2 = 1))
		g_step = ft_simulate(*paths, furn, end, 0);
	else
	{
		n = ft_simulate(*paths, furn, end, 0);
		if (g_step > n && (flag2 = 1))
			g_step = n;
	}
	temp_path = find_another(temp_path, start, end);
	while (temp_path)
	{
		n = ft_simulate(temp_path, furn, end, 0);
		if (g_step > n && (flag2 = 1))
		{
			g_step = n;
			*paths = temp_path;
		}
		temp_path = find_another(temp_path, start, end);
	}
	flag++;
	copy_back();
	return (flag2);
}

void	delete_node(int **paths)
{
	int i;

	i = -1;
	while (paths[++i])
		;
	g_tab[paths[i - 1][1]][paths[i - 1][2]] = 9999;
	g_tab[paths[i - 1][2]][paths[i - 1][1]] = 9999;
	paths[i - 1] = NULL;
}

void	add_path(int **paths, int start, int end)
{
	int i;
	int k;

	g_p = 0;
	dijkstra(g_d, start, end);
	i = 0;
	k = -1;
	while (paths[++k])
		;
	paths[k] = (int*)malloc(sizeof(int) * (g_count + 1));
	paths[k][0] = g_p;
	while (++i <= g_p)
		paths[k][i] = g_path[i - 1];
	paths[k + 1] = NULL;
}

void	lem_in(int start, int end, int furn)
{
	int **paths;
	int nr;
	int flag;

	g_pos = (int*)malloc(sizeof(int) * g_count);
	paths = ft_init_path(start);
	nr = 1;
	while (ft_check_solution_2(start, end, paths[nr - 1]))
	{
		flag = try_all(&paths, furn, start, end);
		mark_node(paths, 0, 0, 0);
		if (flag == 0)
			delete_node(paths);
		add_path(paths, start, end);
		if (flag)
			nr++;
	}
	paths[nr - 1] = NULL;
	ft_putchar(10);
	ft_simulate(paths, furn, end, 1);
}
