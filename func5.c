/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func5.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dprovorn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 16:07:36 by dprovorn          #+#    #+#             */
/*   Updated: 2017/01/27 16:07:38 by dprovorn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	ft_refresh_node(t_room *temp, char **str, int8_t flag)
{
	temp->type = flag;
	temp->x = ft_atoi_check(*(str + 1));
	temp->y = ft_atoi_check(*(str + 2));
}

void	ft_check_coord(t_room *temp, char *str, int x, int y)
{
	while (temp)
	{
		if (x == temp->x && y == temp->y)
		{
			if (ft_strcmp(str, temp->name))
				ft_error();
		}
		temp = temp->next;
	}
}
