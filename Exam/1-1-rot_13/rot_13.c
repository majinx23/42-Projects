#include <unistd.h>

void	ft_putchar(char c)
{	
	write(1, &c, 1);
}


int		rot(char c)
{
	if (c >= 'A' && c <= 'M')
		c += 13;
	else if (c >= 'N' && c <= 'Z')
		c = c - 26 + 13;
	else if (c >= 'a' && c <= 'm')
		c += 13;
	else if(c >= 'n' && c <= 'z')
		c = c - 26 + 13;
	return (c);
}



int		main(int ac, char **av)
{
	int i;
	int repeat;

	i = 0;
	if (ac == 2)
	{
		while (av[1][i])
		{
			ft_putchar(rot(av[1][i]));
			i++;
		}
	}
	ft_putchar('\n');
	return (0);
}
