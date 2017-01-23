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
			printf("%7d",g_tab[i][j]);
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

int	find_min(int *d, int8_t *marked, int *m)
{
	int min;
	int v;
	int i;

	min = INT_MAX;
	i = -1;
	while (++i < g_count)	
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
		return ;
	if (d[vert - 1][i] != d[vert][i])
	{
		find_path(d, vert - 1, m[vert], m);
		g_path[g_p++] = m[vert];
	}
	else
		find_path(d, vert - 1, i, m);
}

int *get_m()
{
	int i;
	int *m;

	m = (int*)malloc(sizeof(int) * g_count);
	i = -1;
	while (++i < g_count)
		*(m + i) = 0;
	return (m);
}

int8_t *get_marked()
{
	int i;
	int8_t *marked;

	marked = (int8_t*)malloc(sizeof(int8_t) * g_count);
	i = -1;
	while (++i < g_count)
		*(marked + i) = 0;
	return (marked);
}

void	dijkstra(int **d, int start, int end)
{
	INIT_DIJKSTRA;
	m = get_m();
	g_m = 0;
	marked = get_marked();
	while (++k < g_count)
	{
		if (k == 0)
		{
			ft_memcpy(d[k], g_temp[start], sizeof(int) * g_count);
			m[g_m++] = start;
			marked[start] = 1;
			v = find_min(d[k], marked, m);
		}
		else
		{
			i = -1;
			while (++i < g_count)
				if (marked[i] == 0)
					d[k][i] = ft_min(d[k - 1][i], d[k-1][v] + g_temp[v][i]);
				else
					d[k][i] = d[k - 1][i];
			v = find_min(d[k], marked, m);
		}	
	}
	--g_m;
	g_path[g_p++] = start;
	find_path(d, g_count - 1, end, m);
	g_path[g_p++] = end;
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

void	ft_print_path(void)
{
	int i;

	i = -1;
	printf("am intrat\n");
	while (++i < g_p)
		printf("%s ", g_names[g_path[i]]);
	printf("stop\n");
}

int	ft_check_solution_1(int start, int end, int *path)
{
	if(*path== start && *(path + 1) == end)
		if (g_temp[start][end] == 9999)
			return (0);
	return(1);
}

int	ft_check_solution_2(int start, int end, int *path)
{
	int i;
	i = -1;	
//	while(++i < 5)
//		printf("Nodul [%d] = %s\n",i,g_names[path[i]]);	
	if(*(path + 1) == start && *(path + 2) == end)
		if (g_temp[start][end] == 9999)
			return (0);

	return (1);
}

int	**ft_init_path(int start)
{
	int **paths;
	int i;
	int j;
	int n;

	n = 0;
	i = 0;
	j = -1;
	while (++j < g_count)
		if (g_temp[start][j] == 1)
			++n;

	paths = (int**)malloc(sizeof(int *) * (n + 1));
	j = -1;
	*paths  = (int*)malloc(sizeof(int) * (g_count + 1));
	paths[0][0] = g_p - 1;
	while(++i <= g_p)
		paths[0][i] = g_path[i-1];
	paths[1] = NULL;
	return(paths);
}

void	reset_sim(int *sim)
{
	int i;

	i = -1;
	while (++i < g_count)
		sim[i] = 0;
}

int	ft_simulate(int **paths, int furn, int end)
{
	int *sim;
	int step;
	int i;
	int j;
	int f_temp;

	step = 0;
	f_temp = furn;
	sim = (int*)malloc(sizeof(int) * g_count);
	reset_sim(sim);
	while (sim[end] != f_temp)
	{
		i = -1;
		while (*(paths + ++i))
		{
			j = paths[i][0] + 1;
			while(--j > 1)
			{
				if(sim[paths[i][j]] == i+1)
				{
					if(paths[i][j+1] == end)
					{
						printf("L%d-%d ",paths[i][j]+1,paths[i][j+1]+1);
						sim[paths[i][j + 1]]++;
						sim[paths[i][j]] = 0;
					}
					else if(sim[paths[i][j+1]] == 0)
					{
						printf("L%d-%d ",paths[i][j]+1,paths[i][j+1]+1);
						sim[paths[i][j + 1]] = i+1;
						sim[paths[i][j]] = 0;
					}
				}
			}
			if ((furn >= paths[i][0] - paths[0][0]) && furn)
			{
				if(sim[paths[i][2]] == 0)
				{
				printf("L%d-%d ",paths[i][1]+1,paths[i][2]+1);
				sim[paths[i][2]] = i+1;
				--furn;
				}
			}
		}
		++step;
		printf("\n");
	}
	return(step);
}

void mark_node(int **paths, int option, int to_mark, int prev)
{
	int k;
	int i;

	k = -1;
	i = -1;
	while (paths[++k])
		;
	if(option == 0)
	{
		while(++i < k)
		{
			g_temp[paths[i][1]][paths[i][2]] = 9999;
			g_temp[paths[i][2]][paths[i][1]] = 9999;
		}
	}
	else
	{
		g_temp[paths[k-1][1]][paths[k-1][2]] = 9999;
		g_temp[paths[k-1][1]][paths[k-1][2]] = 9999;
		g_temp[to_mark][prev] = 9999;
		g_temp[prev][to_mark] = 9999;
	}
}

int **copy_in_lpath(int **paths, int k)
{
	int i;
	int j;
	int **found_path;

	i = -1;
	found_path = (int**)malloc(sizeof(int*)*(k+1));
	while(++i < k)
		found_path[i] = (int*)malloc(sizeof(int) * g_count);
	i = -1;
	while(++i < k)
	{
		j = -1;
		while(++j < paths[i][0] + 1)
			found_path[i][j] = paths[i][j];
	}
	found_path[k] = NULL;
	while(++i < k)
	i = 0;
	found_path[k-1][0] = g_p;
	while(++i <= g_p)
		found_path[k-1][i] = g_path[i-1];
	return (found_path);
}

int **find_another(int **paths, int start, int end)
{
	int i;
	int j;
	int k;
	int m;
	int **found_path;

	k = -1;
	i = 1;
	found_path = NULL;
	while (paths[++k])
		;
	while (++i < paths[k-1][0])
	{
		j = -1;
		while (++j < k - 1)
		{
			m = 1;
			while (++m < paths[j][0])
				if (paths[k - 1][i] == paths[j][m])
				{
					mark_node(paths, 1, paths[j][m], paths[k-1][i-1]);
					g_p = 0; //De facut inainte de fiecare Dijkstra
					g_path[g_p++] = start;
					dijkstra(g_d, paths[k-1][2], end);
					if (ft_check_solution_2(start, end, g_path))
						found_path = copy_in_lpath(paths, k);
				}
		}
	}
	return (found_path);
}

void copy_back(void)
{
	int i;
	int j;

	i = -1;
	while(++i < g_count)
	{
		j = -1;
		while(++j < g_count)
			g_temp[i][j] = g_tab[i][j];
	}
}

int	try_all(int **paths, int furn, int start, int end)
{
	int n;
	int **temp_path;
	static int flag = 0;
	int flag2;

	flag2 = 0;
	printf("\n\nflag = %d\n\n",flag);
	temp_path = paths;
	if(flag == 0 && (flag2 = 1))
		g_step = ft_simulate(paths, furn, end);
	else
	{
		n = ft_simulate(paths, furn, end);
		if(g_step > n && (flag2 = 1))
			g_step = n;
	}
	while(temp_path = find_another(temp_path, start, end))
	{		
		n = ft_simulate(temp_path, furn, end);
		if(g_step > n && (flag2 = 1))
		{
			g_step = n;
			paths = temp_path;
		}
		//free la temp_path
	}
	flag++;
	copy_back();
	printf("flag2 = %d\n", flag2);
	return(flag2);
}

void	delete_node(int **paths)
{
	int i;

	i = -1;
	printf("BANG BANG BATYA V ZDANIE\n");
	while(paths[++i])
		;
	printf("i = %d\n", i);
	g_tab[paths[i-1][1]][paths[i -1][2]] = 9999;
	g_tab[paths[i-1][2]][paths[i -1][1]] = 9999;
	paths[i-1] = NULL;
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
	ft_print_path();
	paths[k][0] = g_p;
	while (++i <= g_p)
		paths[k][i] = g_path[i-1];
	paths[k + 1] = NULL;	
}

void	lem_in(int start, int end, int furn)
{
	int **paths;
	int nr;
	int flag;
	static int cont = 0;

	paths = ft_init_path(start);
	nr = 1;
	while (ft_check_solution_2(start, end, paths[nr - 1]))
	{

		flag = try_all(paths, furn, start, end);
		mark_node(paths, 0, 0, 0);
		if(flag == 0)
			delete_node(paths);			
		add_path(paths, start, end);
		if(flag)
			nr++;
	}
}

int	main(void)
{
	VAR_INIT_1;
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
	ft_create_d_path();
	g_p = 0;
	dijkstra(g_d, start, end);
	ft_print_path();
	printf("________\n");
	if (!ft_check_solution_1(start, end, g_path))
		ft_error(9999);
	lem_in(start, end, furn);
	printf("\n\n\nstep = %d\n\n\n", g_step);
}