#include "header.h"

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
		ft_error();
	if (*(str + 1) == NULL)
		ft_error();
	if (*(str + 2) == NULL)
		ft_error();
	if (*(str + 3) != NULL)
		ft_error();
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
