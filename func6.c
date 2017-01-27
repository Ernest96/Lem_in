/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func6.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dprovorn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 16:07:45 by dprovorn          #+#    #+#             */
/*   Updated: 2017/01/27 16:08:38 by dprovorn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int8_t	ft_first_check(char *line)
{
	if (*line == 0)
		ft_error();
	if (*line == '#' && *(line + 1) != '#')
		return (1);
	return (0);
}

void	ft_check_possible(t_room *head)
{
	int start;
	int end;

	start = 0;
	end = 0;
	while (head)
	{
		if (head->type == 1)
			start = 1;
		else if (head->type == 2)
			end = 1;
		head = head->next;
	}
	if (start == 0 || end == 0)
		ft_error();
}

void	ft_res_array(void)
{
	int i;
	int j;

	i = -1;
	while (++i < g_count)
	{
		j = -1;
		while (++j < g_count)
			if (i != j)
				g_tab[i][j] = 9999;
			else
				g_tab[i][j] = 0;
	}
}

void	ft_insert(char **str)
{
	int i;
	int m;
	int n;

	i = -1;
	while (++i < g_count)
	{
		if (!ft_strcmp(*str, g_names[i]))
			m = i;
		if (!ft_strcmp(*(str + 1), g_names[i]))
			n = i;
	}
	if (n != m)
	{
		g_tab[m][n] = 1;
		g_tab[n][m] = 1;
	}
}

void	ft_create_relation(t_room *head, char *line)
{
	C_REL;
	temp = ft_strchr(line, '-');
	if (ft_strchr(++temp, '-'))
		ft_error();
	if (!g_rel)
		ft_create_array(head);
	str = ft_strsplit(line, '-');
	if (*str == NULL || *(str + 1) == NULL)
		ft_error();
	room = head;
	count = 0;
	while (room)
	{
		if (!ft_strcmp(room->name, *str) || !ft_strcmp(room->name, *(str + 1)))
			++count;
		room = room->next;
	}
	if (count != 2)
		ft_error();
	ft_insert(str);
	ft_free_split(&str);
}
