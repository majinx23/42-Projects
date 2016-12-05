#include <unistd.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

int		main(int ac, char **av)
{
	int i;
	int a;

	i = 96;
	while (i++ < 122)
	{
		if (i % 2 == 0)
			a = i - 32;
		else
			a = i;
		ft_putchar(a);
	}
	ft_putchar('\n');	
	return (0);
}
