#include <unistd.h>

void	ft_putchar(char c)
{	
	write(1, &c, 1);
}


int		letter_count(char c)
{
	int repeat;

	if (c >= 'A' && c <= 'Z')
		repeat = c - 64;
	if (c >= 'a' && c <= 'z')
		repeat = c - 96;
	else
		repeat = 1;
	return (repeat);
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
			repeat = letter_count(av[1][i]);
			while (repeat > 0)
			{
				ft_putchar(av[1][i]);
				repeat--;
			}
		i++;
		}
	}
	ft_putchar('\n');
}
