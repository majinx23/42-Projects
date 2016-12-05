#include <stdio.h>

int isblank(char c)
{
	if (c <= 32)
		return (1);
	return (0);
}

int		isvalid(char c, int base)
{
	char digits[17] = "0123456789abcdef";
	char digits2[17] = "0123456789ABCDEF";
	int i;

	i = 0;
	while (i < base)
	{
		if (digits[i] == c || digits2[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int		value_of(char c)
{
	if (c >= '0' && c <= '9')
		return (c - '0');
	if (c == 'a' || c == 'A')
		return (10);
	if (c == 'b' || c == 'B')
		return (11);
	if (c == 'c' || c == 'C')
		return (12);
	if (c == 'd' || c == 'D')
		return (13);
	if (c == 'e' || c == 'E')
		return (14);
	if (c == 'f' || c == 'F')
		return (15);
	return (0);
}



int		ft_atoi_base(const char *str, int str_base)
{
	int result;
	int sign;

	result = 0;
	sign = 1;
	while (isblank(*str))
		str++;
	if (*str == '-' || *str == '+')
		if (*str++ == '-')
			sign = -1;
	while (isvalid(*str, str_base))
		result = result * str_base + value_of(*str++);
	return (result * sign);
}

int		main(void)
{
	printf("result: %d\n", ft_atoi_base("-22", 5));
	return (0);
}
