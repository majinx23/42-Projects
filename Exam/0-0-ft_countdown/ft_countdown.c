#include <unistd.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

int		main(int ac, char **av)
{
	int i;

	i = 10;
	while (i-- > 0)
		ft_putchar(i + '0');
	ft_putchar('\n');	
	return (0);
}
