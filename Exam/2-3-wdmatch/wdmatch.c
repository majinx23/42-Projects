#include <unistd.h>

void	wdmatch(char *str, char *str2)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (str2[j])
	{
		if (str2[j] == str[i])
		{
			write(1, &str[i], 1);
			i++;
		}
		j++;
	}
}

int		main(int ac, char **av)
{
	if (ac == 3)
		wdmatch(av[1], av[2]);
	write(1, "\n", 1);
	return (0);
}
