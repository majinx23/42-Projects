#include <unistd.h>

void	ft_putchar(char c)
{	
	write(1, &c, 1);
}


int		ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}


int		main(int ac, char **av)
{
	int len;

	len = ft_strlen(av[1]);
	if (ac == 2)
		while (len >= 0)
		{
			ft_putchar(av[1][len]);
			len--;
		}
	ft_putchar('\n');
}
