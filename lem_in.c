#include "header.h"
#define INIT_DIJKSTRA int *m; int v; int k = -1; int i = -1; int8_t *marked;

void	ft_init_start_end(t_room **head, char *line, int8_t flag) // init pentru start (flagul 1)
{
	INIT_FOR_LIST;
	str = ft_split_check(line);
	if (*line == 'L')
		ft_error(8);
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
		if (!ft_strcmp(*str, temp->name)) // daca am gasit un nod cu acest nume, il setam ca start
		{
			ft_refresh_node(temp, str, flag);
			ft_free_split(&str);
			return ;
		}
		prev = temp;
		temp = temp->next;
	}
	ft_init_node(&prev,str);
	prev->type = flag;
	ft_free_split(&str);
}

void	ft_init_room(t_room **head, char *line) // aici initializam un room simplu, cu flag 0
{
	INIT_FOR_LIST;
	str = ft_split_check(line);
	if (*line == 'L')
		ft_error(9);
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
		if (!ft_strcmp(*str, temp->name)) // daca am gasit un nod cu acest nume, nu inseram unul nou
		{
			ft_refresh_node(temp , str, 0);
			ft_free_split(&str);
			return ;
		}
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

void	print_array()
{
	int i;
	int j;

	i = -1;
	while(++i < g_count)
	{
		j = -1;
		while(++j < g_count)
			printf("%10d",g_tab[i][j]);
		printf("\n");
	}
}

t_room *get_farm(int *furn)
{
	VAR_INIT_2;
	while(get_next_line(0, &line))
	{	
		if (flag == -1)
		{
			*furn = ft_atoi_check(line);
			if (!(*furn))
				ft_error(1);
			flag = 0;
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

int	find_min(int *d, int vertices, int8_t *marked, int *m)
{
	int min;
	int v;
	int i;

	min = INT_MAX;
	i = -1;
	while (++i < vertices)	
		if (d[i] < min && marked[i] == 0)
			{
				v = i;
				min = d[i];
			}
	m[g_m++] = v;
	marked[v] = 1;
	return (v);
}

void	find_path(int **d, int vert, int i, int *m)
{
	if (vert == 0)
	{
		return ;
	}
	if (d[vert - 1][i] != d[vert][i])
	{
		find_path(d, vert - 1, m[vert], m);
		ft_putstr(g_names[m[vert]]);
		write(1, " " , 1);
	}
	else
		find_path(d, vert - 1, i, m);
}

int *get_m(int vertices)
{
	int i;
	int *m;

	m = (int*)malloc(sizeof(int) * vertices);
	i = -1;
	while (++i < vertices)
		*(m + i) = 0;
	return (m);
}

int8_t *get_marked(int vertices)
{
	int i;
	int8_t *marked;

	marked = (int8_t*)malloc(sizeof(int8_t) * vertices);
	i = -1;
	while (++i < vertices)
		*(marked + i) = 0;
	return (marked);
}

void	dijkstra(int **d, int vertices, int start, int end)
{
	INIT_DIJKSTRA;
	m = get_m(vertices);
	marked = get_marked(vertices);
	while (++k < vertices)
	{
		if (k == 0)
		{
			ft_memcpy(d[k], g_tab[start], sizeof(int) * vertices);
			m[g_m++] = start;
			marked[start] = 1;
			v = find_min(d[k], vertices, marked, m);
		}
		else
		{
			i = -1;
			while (++i < vertices)
				if (marked[i] == 0)
					d[k][i] = ft_min(d[k - 1][i], d[k-1][v] + g_tab[v][i]);
				else
					d[k][i] = d[k - 1][i];
			v = find_min(d[k], vertices, marked, m);
		}	
	}
	--g_m;
	ft_putstr(g_names[start]);
	write(1, " ", 1);
	find_path(d, vertices - 1, end, m);
	ft_putstr(g_names[end]);
	write(1, " \n", 2);
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

int	main(void)
{
	VAR_INIT_1;
	int **d;
	int start;
	int end;
	head = get_farm(&furn);
	if (!g_rel)
		ft_error(27);
	ft_check_possible(head); // aici facem check daca avem start si end
	ft_print_farm(furn, head);
	print_array();
	ft_get_start_end(head, &start, &end, -1);
		ft_free_list(&head);
	ft_create_d(&d);
	dijkstra(d, g_count, start, end);
}