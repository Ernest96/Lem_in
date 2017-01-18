#include "header.h"

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

int	find_min(int *D, int vertices, int8_t *marked, int *M)
{
	int min = INT_MAX;
	int v;

	for (int i = 0; i < vertices; i++)
		if (D[i] < min && marked[i] == 0)
			{
				v = i;
				min = D[i];
			}
	M[g_m++] = v;
	marked[v] = 1;
	return v;
}

void	find_path(int **D, int vert, int i, int *M)
{
	if (vert == 0)
	{
		return ;
	}
	if (D[vert - 1][i] != D[vert][i])
	{
		find_path(D, vert - 1, M[vert], M);
		printf("%s ", g_names[M[vert]]);
	}
	else
		find_path(D, vert - 1, i, M);
}

void	Dijkstra(int **D, int vertices, int start)
{
	int *M;
	int v;
	int temp;
	int8_t *marked;

	M = (int*)calloc(vertices, sizeof(int));
	marked = (int8_t*)calloc(vertices, sizeof(int8_t));
	g_m = 0;
	for (int k = 0; k < vertices; k++)
	{
		if (k == 0)
		{
			ft_memcpy(D[k], g_tab[start], sizeof(int) * vertices);
			M[g_m++] = start;
			marked[start] = 1;
			v = find_min(D[k], vertices, marked, M);
		}
		else
			{
		for(int i = 0; i < vertices; i++)
		if (marked[i] == 0)
		D[k][i] = ft_min(D[k - 1][i], D[k-1][v] + g_tab[v][i]);
				else
			D[k][i] = D[k - 1][i];
			v = find_min(D[k], vertices, marked, M);
			}
		
	}
	--g_m;
	for (int i = 0; i < vertices; i++)
	{
		if (i == start)
			continue ;
		printf("%s ", g_names[start]);		
		find_path(D, vertices - 1, i, M);
		printf("%s\n", g_names[i]);		
	}
}

void	ft_get_start_end(t_room *head, int *start, int *end)
{
	int i;

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
	int **D;
	int start;
	int end;
	head = get_farm(&furn);
	if (!g_rel)
		ft_error(27);
	ft_check_possible(head); // aici facem check daca avem start si end
	ft_print_farm(furn, head);
	print_array();
	ft_get_start_end(head, &start, &end);
		ft_free_list(&head);
	ft_create_D(&D);
	Dijkstra(D, g_count, start);
}