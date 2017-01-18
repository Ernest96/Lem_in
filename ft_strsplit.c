#include "header.h"

short	is_ok(char c, char ok)
{
	if (c && c != '\t' && c != '\n' && c != ok)
		return (1);
	else
		return (0);
}

int		get_count(char const *str, char ok)
{
	int i;
	int count;

	i = -1;
	count = 0;
	while (str[++i])
		if (is_ok(str[i], ok) && (i ? !is_ok(str[i - 1], ok) : 1))
			++count;
	return (count);
}

int		get_size(char const *str, int i, char ok)
{
	int size;

	size = 0;
	while (is_ok(str[i], ok))
	{
		size++;
		i++;
	}
	return (size);
}

char			**ft_strsplit(char const *str, char ok)
{
	char	**tab;
	int		i[4];

	if (str == NULL)
		return (0);
	i[3] = get_count(str, ok);
	tab = (char **)malloc(sizeof(char*) * (i[3] + 1));
	if (tab == 0)
		return (NULL);
	i[0] = -1;
	i[1] = 0;
	while (++i[0] < i[3] && (i[2] = -1))
	{
		while (!is_ok(str[i[1]], ok))
			++i[1];
		tab[i[0]] = (char *)malloc(sizeof(char) * get_size(str, i[1], ok));
		while (is_ok(str[i[1]], ok))
		{
			tab[i[0]][++i[2]] = str[i[1]];
			i[1]++;
		}
		tab[i[0]][++i[2]] = '\0';
	}
	tab[i[0]] = NULL;
	return (tab);
}