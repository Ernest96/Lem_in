#include "header.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i == 0 && (*(s1 + j) != 0 || *(s2 + j) != 0))
	{
		i = *(unsigned char *)(s1 + j) - *(unsigned char *)(s2 + j);
		j++;
	}
	return (i);
}

void	ft_print_room(t_room *temp)
{
	ft_putstr(temp->name);
	write(1, " ", 1);
	ft_putnbr(temp->x);
	write(1, " ", 1);
	ft_putnbr(temp->y);
	write(1, "\n", 1);
}

void	ft_print_farm(int furn, t_room *head)
{
	t_room *temp;

	W_F;
	write(1, "\n", 1);
	W_S;
	temp = head;
	while (temp->type != 1)
		temp = temp->next;
	ft_print_room(temp);
	W_E;
	temp = head;
	while (temp->type != 2)
		temp = temp->next;
	ft_print_room(temp);
	temp = head;
	while (temp)
	{
		if (!temp->type)
			ft_print_room(temp);
		temp = temp->next;
	}
}

void	ft_check_command(int8_t *flag, int8_t to_set)
{
	if (*flag)
		ft_error();
	*flag = to_set;
}

void	ft_reset(t_room *temp, int8_t flag) // aici resetam toate flagurile la room la 0, tipa nu e start
{
	while (temp)
	{
		if (temp->type == flag)
			temp->type = 0;
		temp = temp->next;
	}
}
