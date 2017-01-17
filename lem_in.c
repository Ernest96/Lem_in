#include "func.c"
#include "get_next_line.c"
#include "ft_strsplit.c"
#define VAR_INIT_1 t_room *head = NULL; int furn; g_rel = 0; g_tab = NULL;
#define VAR_INIT_2 char *line; int8_t flag = -1; t_room *head = NULL; 
#define INIT_FOR_LIST t_room	*temp, *prev; char	**str; uint8_t x, y;
#define W_S write(1, AC_G, 5); write(1, "##start\n", 8); write(1, AC_RES, 4); 
#define	W_E write(1, AC_C, 5); write(1, "##end\n", 6); write(1, AC_RES, 4);
#define W_F write(1, AC_Y, 5); ft_putnbr(furn); write(1, AC_RES, 4);
#define C_REL char *temp; char **str; t_room *room; int8_t count;
int8_t	g_rel;
int **g_tab;
char **g_names;
int g_count;

typedef struct 	s_room
{
	char *name;
	int8_t type;
	uint8_t x;
	uint8_t y;
	struct s_room *next;
}				t_room;

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
		ft_error(2);
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

void	ft_free_list(t_room **head)
{
	t_room *temp;

	while (*head)
	{
		temp = *head;
		*head = (*head)->next;
		free(temp->name);
		free(temp);
	}
}

void	ft_init_node(t_room **temp, char **str) // functie de initializare a nodului
{
	(*temp)->next = (t_room*)malloc(sizeof(t_room));
	*temp = (*temp)->next;
	(*temp)->name = ft_strdup(*str);
	(*temp)->x = ft_atoi_check(*(str + 1));
	(*temp)->y = ft_atoi_check(*(str + 2));
	(*temp)->next = NULL;
}

char **ft_split_check(char *line)
{
	char **str;

	str = ft_strsplit(line, ' ');

	if (*str == NULL)
		ft_error(3);
	if (*(str + 1) == NULL)
		ft_error(4);
	if (*(str + 2) == NULL)
		ft_error(5);
	if (*(str + 3) != NULL)
		ft_error(6);

	return (str);
}

void	ft_free_split(char ***str)
{
	int i;

	i = -1;
	while (*(*str + ++i))
		free(*(*str + i));
	free (*str);		
}

void	ft_init_head(t_room **head, char **str, int8_t flag)
{
	*head = (t_room*)malloc(sizeof(t_room));
	(*head)->name = ft_strdup(*str);
	(*head)->x = ft_atoi_check(*(str + 1));
	(*head)->y = ft_atoi_check(*(str + 2));
	(*head)->type = flag;
	(*head)->next = NULL;
}

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
				ft_error(7);
		}
		temp = temp->next;
	}
}

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

int8_t ft_first_check(char *line)
{
	if (*line == 0)
			ft_error(10);
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
		ft_error(11);
}

void	ft_res_array()
{
	int i;
	int j;

	i = -1;
	while(++i < g_count)
	{
		j = -1;
		while(++j < g_count)
			g_tab[i][j] = 0;
	}
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

void	ft_insert(char **str)
{
	int i;
	int m;
	int n;

	i = -1;
	while(++i < g_count)
	{
		if(!ft_strcmp(*str, g_names[i]))
			m = i;
		if(!ft_strcmp(*(str + 1), g_names[i]))
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
		ft_error(12);
	if (!g_rel)
		ft_create_array(head);
	str = ft_strsplit(line, '-');
	if (*str == NULL || *(str + 1) == NULL)
		ft_error(13);
	room = head;
	count = 0;
	while (room)
	{
		if(!ft_strcmp(room->name, *str) || !ft_strcmp(room->name, *(str + 1)))
			++count;
		room = room->next;
	}
	if (count != 2)
		ft_error(14);
	ft_insert(str);
	ft_free_split(&str);
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

int	main(void)
{
	sleep(5);
	VAR_INIT_1;
	head = get_farm(&furn);
	ft_check_possible(head); // aici facem check daca avem start si end
	ft_print_farm(furn, head);
	sleep(5);
	ft_free_list(&head);
	print_array();
	sleep(5);
}