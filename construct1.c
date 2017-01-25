#include "header.h"

void	ft_init_start_end(t_room **head, char *line, int8_t flag)
{
	INIT_FOR_LIST;
	str = ft_split_check(line);
	if (*line == 'L')
		ft_error();
	if (*head == NULL)
	{
		ft_init_head(head, str, flag);
		ft_free_split(&str);
		return ;
	}
	temp = *head;
	x = ft_atoi_check(*(str + 1));
	y = ft_atoi_check(*(str + 2));
	ft_reset(temp, flag);
	while (temp)
	{
		ft_check_coord(*head, *str, x, y);
		if (!ft_strcmp(*str, temp->name))
			RE1;
		prev = temp;
		temp = temp->next;
	}
	ft_init_node(&prev,str);
	prev->type = flag;
	ft_free_split(&str);
}

void	ft_init_room(t_room **head, char *line)
{
	INIT_FOR_LIST;
	str = ft_split_check(line);
	if (*line == 'L')
		ft_error();
	if (*head == NULL)
	{
		ft_init_head(head, str, 0);
		ft_free_split(&str);
		return ;
	}
	temp = *head;
	x = ft_atoi_check(*(str + 1));
	y = ft_atoi_check(*(str + 2));
	while (temp)
	{
		ft_check_coord(*head, *str, x, y);
		if (!ft_strcmp(*str, temp->name))
			RE2;
		prev = temp;
		temp = temp->next;
	}
	ft_init_node(&prev, str);
	prev->type = 0;
	ft_free_split(&str);
}

void	ft_create_array(t_room *room)
{
	t_room 	*temp;
	short	i;

	temp = room;
	g_count = 0;
	while (temp)
	{
		g_count++;
		temp = temp->next;
	}
	g_tab = (int**)malloc(sizeof(int*) * g_count);
	i = -1;
	while (++i < g_count)
		*(g_tab + i) = (int*)malloc(sizeof(int) * g_count);
	ft_res_array();
	g_names = (char**)malloc(sizeof(char*) * g_count);
	temp = room;
	i = -1;
	while (temp)
	{
		*(g_names + ++i) = ft_strdup(temp->name);
		temp = temp->next;
	}
	g_rel = 1;
}

t_room *get_farm(int *furn)
{
	VAR_INIT_2;
	while(get_next_line(0, &line))
	{	
		if (flag == -1)
		{
			F1;
		}
		else if (ft_strchr(line, '-') && !flag)
			ft_create_relation(head, line);
		else if (ft_first_check(line))
				;
		else if (!ft_strcmp(line, "##start") && !g_rel)
			ft_check_command(&flag, 1);
		else if(!ft_strcmp(line, "##end") && !g_rel)
			ft_check_command(&flag, 2);
		else if (!flag)
			ft_init_room(&head, line);
		else if ((flag == 1 || flag == 2) && !g_rel)
		{
			ft_init_start_end(&head, line, flag);
			flag = 0;
		}
		free(line);
	}
	return (head);
}

void	ft_get_start_end(t_room *head, int *start, int *end, int i)
{
	while (head)
	{
		if (head->type == 1)
		{
			i = -1;
			while (++i < g_count)
				if (!ft_strcmp(head->name, g_names[i]))
				{
					*start = i;
					break ;
				}
		}
		if (head->type == 2)
		{
			i = -1;
			while (++i < g_count)
				if (!ft_strcmp(head->name, g_names[i]))
				{
					*end = i;
					break ;
				}
		}
		head = head->next;
	}
}