#include "header.h"

char	*ft_strchr(const char *s, int c)
{
	int i;
	int size;

	i = -1;
	while (*(s + ++i))
		;
	size = i;
	i = -1;
	while (++i <= size)
		if (*(s + i) == c)
			return (char*)(s + i);
	return (NULL);
}

char	*ft_strdup(const char *src)
{
	unsigned int	i;
	char			*mem;
	unsigned int	j;

	i = 0;
	while (*(src + i))
		i++;
	mem = (char*)malloc(i + 1);
	if (!mem)
		return (0);
	j = -1;
	while (++j < i)
		*(mem + j) = *(src + j);
	*(mem + j) = 0;
	return (mem);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		len;
	char	*str;
	int		i;

	if (!s1 || !s2)
		return (0);
	len = ft_strlen(s1) + ft_strlen(s2);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (*s1)
	{
		str[i] = *s1;
		i++;
		s1++;
	}
	while (*s2)
	{
		str[i] = *s2;
		i++;
		s2++;
	}
	str[i] = '\0';
	return (str);
}

int		ft_atoi_check(const char *str)
{
	INIT_ATOI;
	while ((str[i] == '\t') || (str[i] == '\n') || (str[i] == ' ') ||
			(str[i] == '\f') || (str[i] == '\v') || (str[i] == '\r'))
		i++;
	if (str[i] == '-')
		ft_error();
	if ((str[i] == '+') || (str[i] == '-'))
		i++;
	while (str[i] && (str[i] >= '0') && (str[i] <= '9'))
	{
		if (!(str[i] >= '0') && (str[i] <= '9'))
			ft_error();
		nr *= 10;
		nr += (int)str[i] - '0';
		i++;
	}
	if (str[i] != 0)
		ft_error();
	if (n == 1)
		return (-nr);
	return (nr);
}

void	ft_putnbr(int nb)
{
	if (nb == 0)
		ft_putchar('0');
	else if (nb > 0 && nb < 10)
	{
		ft_putchar('0' + nb);
		return ;
	}
	else if (nb == -2147483648)
	{
		ft_putchar('-');
		ft_putnbr(nb / (-10));
		ft_putchar('0' + 8);
	}
	else if (nb < 0)
	{
		ft_putchar('-');
		ft_putnbr(-nb);
	}
	else
	{
		ft_putnbr(nb / 10);
		ft_putchar('0' + nb % 10);
	}
}
