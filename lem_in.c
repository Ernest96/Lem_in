#include "header.h"
#define INIT_DIJKSTRA int *m; int v; int k = -1; int i = -1; int8_t *marked;

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
					d[k][i] = ft_min(d[k - 1][i], d[k - 1][v] + g_temp[v][i]);
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

int	ft_check_solution_1(int start, int end, int *path)
{
	if(*path== start && *(path + 1) == end)
		if (g_temp[start][end] == 9999)
			return (0);
	return(1);
}

int	ft_check_solution_2(int start, int end, int *path)
{
	if(*(path + 1) == start && *(path + 2) == end)
	{
		if (g_temp[start][end] == 9999)
			return (0);
	}
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
	paths[0][0] = g_p;
	while(++i <= g_p)
		paths[0][i] = g_path[i - 1];
	paths[1] = NULL;
	return(paths);
}

void	reset_sim(int *sim)
{
	int i;

	i = -1;
	while (++i < g_count)
	{
		sim[i] = 0;
		g_pos[i] = 0;
	}
}

void	ft_put_change(int coord)
{
	ft_putstr("L");
	ft_putnbr(g_pos[coord]);
	ft_putchar('-');
	ft_putstr(g_names[coord]);
	ft_putchar(' ');
}

int	ft_simulate(int **paths, int furn, int end, int8_t param)
{
	int *sim;
	int step;
	int i;
	int j;
	int f_temp;
	int n;

	n = 1;
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
				if(sim[paths[i][j]] == i+1 && paths[i][j] != end)
				{
					if(paths[i][j+1] == end)
					{
						sim[paths[i][j + 1]]++;
						g_pos[paths[i][j + 1]] = g_pos[paths[i][j]];
						if(param == 1)
							ft_put_change(paths[i][j+1]);
						sim[paths[i][j]] = 0;
					}
					else if(sim[paths[i][j+1]] == 0 && paths[i][j] != end)
					{
						sim[paths[i][j + 1]] = i+1;
						g_pos[paths[i][j + 1]] = g_pos[paths[i][j]];
						if(param == 1)
							ft_put_change(paths[i][j+1]);
						sim[paths[i][j]] = 0;
					}
				}
			}
			if ((furn >= paths[i][0] - paths[0][0]) && furn)
			{
				if(sim[paths[i][2]] == 0 || paths[i][2] == end)
				{
				if(paths[i][2] != end)
					sim[paths[i][2]] = i+1;
				else
					sim[end]++;
				g_pos[paths[i][2]] = n;
				if(param == 1)
					ft_put_change(paths[i][2]);
				--furn;
				n++;
				}
			}
		}
		if(param == 1)
			ft_putchar('\n');
		++step;
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
			{
				if (paths[k - 1][i] == paths[j][m])
				{
					mark_node(paths, 1, paths[j][m], paths[k-1][i-1]);
					g_p = 0; //De facut inainte de fiecare Dijkstra
					g_path[g_p++] = start;
					dijkstra(g_d, paths[k-1][2], end);
					for(int i = 0; i<g_p; i++)
					if (!(g_path[2] == end))
						found_path = copy_in_lpath(paths, k);
				}
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

int	try_all(int ***paths, int furn, int start, int end)
{
	int n;
	int **temp_path;
	static int flag = 0;
	int flag2;

	flag2 = 0;
	temp_path = *paths;
	if(flag == 0 && (flag2 = 1))
		g_step = ft_simulate(*paths, furn, end, 0);
	else
	{
		n = ft_simulate(*paths, furn, end, 0);
		if(g_step > n && (flag2 = 1))
			g_step = n;
	}
	while(temp_path = find_another(temp_path, start, end))
	{		
		n = ft_simulate(temp_path, furn, end, 0);
		if(g_step > n && (flag2 = 1))
		{
			g_step = n;
			*paths = temp_path;
		}
	}
	flag++;
	copy_back();
	return(flag2);
}

void	delete_node(int **paths)
{
	int i;

	i = -1;
	while(paths[++i])
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
		paths[k][i] = g_path[i-1];
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
		if(flag == 0)
			delete_node(paths);			
		add_path(paths, start, end);
		if(flag)
			nr++;
	}
	paths[nr - 1] = NULL;
	ft_putchar(10);
	ft_simulate(paths, furn, end, 1);
}

int	main(void)
{
	VAR_INIT_1;
	int start;
	int end;

	head = get_farm(&furn);
	if (!g_rel)
		ft_error();
	ft_check_possible(head);
	ft_get_start_end(head, &start, &end, -1);
	ft_create_d_path();
	g_p = 0;
	dijkstra(g_d, start, end);
	if (!ft_check_solution_1(start, end, g_path))
		ft_error();
	ft_print_farm(furn, head);
	ft_free_list(&head);
	lem_in(start, end, furn);
}