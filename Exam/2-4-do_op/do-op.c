#include <stdio.h>
#include <stdlib.h>

int		main(int argc, char **argv)
{
	if  (argc != 4)
		printf("\n");
	if (argv[2][0] == '+')
		printf("%d\n", atoi(argv[1]) + atoi(argv[3]));
	if (argv[2][0] == '-')
		printf("%d\n", atoi(argv[1]) - atoi(argv[3]));
	if (argv[2][0] == '*')
		printf("%d\n", atoi(argv[1]) * atoi(argv[3]));
	if (argv[2][0] == '/')
		printf("%d\n", atoi(argv[1]) / atoi(argv[3]));
	if (argv[2][0] == '%')
		printf("%d\n", atoi(argv[1]) % atoi(argv[3]));

	return (0);
}
