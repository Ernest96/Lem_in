#include "func.c"
#include "get_next_line.c"
#define VAR_INIT char *line; int8_t flag = -1; t_room *head = NULL; int furn;

typedef struct 	s_room
{
	char *name;
	int8_t type;
	struct s_room *next;
}				t_room;

void	ft_reset(t_room *temp, int8_t flag) // aici resetam toate flagurile la room la 0, tipa nu e start
{
	while (temp)
	{
		if (temp->type == flag)
			temp->type = 0;
		temp = temp->next;
	}
}

void	ft_init_node(t_room **temp, char *line) // functie de initializare a nodului
{
	(*temp)->next = (t_room*)malloc(sizeof(t_room));
	*temp = (*temp)->next;
	(*temp)->name = ft_strdup(line);
	(*temp)->next = NULL;
}

void	ft_init_start(t_room **head, char *line) // init pentru start (flagul 1)
{
	t_room *temp;

	if (*line == 'L' || ft_strchr(line, '-'))
		ft_error();
	if (*head == NULL)
	{
		*head = (t_room*)malloc(sizeof(t_room));
		(*head)->name = ft_strdup(line);
		(*head)->type = 1;
		(*head)->next = NULL;
		return ;
	}
	temp = *head;
	ft_reset(temp, 1);
	while (temp->next)
	{
		if (!ft_strcmp(line, temp->name)) // daca am gasit un nod cu acest nume, il setam ca start
		{
			temp->type = 1;
			return ;
		}
		temp = temp->next;
	}
	ft_init_node(&temp, line);
	temp->type = 1;
}

void	ft_init_end(t_room **head, char *line)
{
	t_room *temp;

	if (*line == 'L' || ft_strchr(line, '-'))
		ft_error();
	if (*head == NULL)
	{
		*head = (t_room*)malloc(sizeof(t_room));
		(*head)->name = ft_strdup(line);
		(*head)->type = 2;
		(*head)->next = NULL;
		return ;
	}
	temp = *head;
	ft_reset(temp, 2);
	while (temp->next)
	{
		if (!ft_strcmp(line, temp->name)) // daca am gasit un nod cu acest nume, il setam ca start
		{
			temp->type = 2;
			return ;
		}
		temp = temp->next;
	}
	ft_init_node(&temp, line);
	temp->type = 2;
}

void	ft_init_room(t_room **head, char *line) // aici initializam un room simplu, cu flag 0
{
	t_room *temp;

	if (*line == 'L' || ft_strchr(line, '-'))
		ft_error();
	if (*head == NULL)
	{
		*head = (t_room*)malloc(sizeof(t_room));
		(*head)->name = ft_strdup(line);
		(*head)->type = 0;
		(*head)->next = NULL;
		return ;
	}
	temp = *head;
	while (temp->next)
	{
		if (!ft_strcmp(line, temp->name)) // daca am gasit un nod cu acest nume, nu inseram unul nou
			return ;
		temp = temp->next;
	}
	ft_init_node(&temp, line);
	temp->type = 0;
}

int8_t ft_first_check(char *line)
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

int	main(void)
{
	VAR_INIT;
	while(get_next_line(1, &line))
	{	
		if (ft_first_check(line))
				;
		else if (!ft_strcmp(line, "##start"))
			flag = 1;
		else if(!ft_strcmp(line, "##end"))
			flag = 2;
		else if (!flag)
			ft_init_room(&head, line);
		else if (flag == 1)
		{
			ft_init_start(&head, line);
			flag = 0;
		}
		else if (flag == 2)
		{
			ft_init_end(&head, line);
			flag = 0;
		}
		else if (flag == -1)
		{
			furn = ft_atoi_check(line);
			flag = 0;
		}
		free(line);
	}
	ft_check_possible(head); // aici facem check daca avem start si end
	while (head)
	{
		printf("\n_____\n");
		printf("name = %s\n", head->name);
		printf("type = %d\n", head->type);
		head = head->next;
	}
}