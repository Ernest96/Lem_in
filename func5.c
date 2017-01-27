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
