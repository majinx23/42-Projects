#include "libft.h"

int	ft_putwchar(unsigned wchar)
{
	int nb_bytes;

	nb_bytes = ft_wcharlen(wchar);
	if (nb_bytes == 1)
		ft_putchar(wchar);
	else if (nb_bytes == 2)
	{
		ft_putchar(((wchar & (0x1f << 6)) >> 6) + 0xC0);
		ft_putchar(((wchar & 0x3f)) + 0x80);
	}
	else if (nb_bytes == 3)
	{
		ft_putchar(((wchar & (0xf << 12)) >> 12) + 0xE0);
		ft_putchar(((wchar & (0x3f << 6)) >> 6 ) + 0x80);
		ft_putchar(((wchar & 0x3f)) + 0x80);
	}
	else
	{
		ft_putchar(((wchar & ( 0x7 << 18)) >> 18) + 0xF0);
		ft_putchar(((wchar & (0x3f << 12)) >> 12) + 0x80);
		ft_putchar(((wchar & (0x3f << 6 )) >> 6)  + 0x80);
		ft_putchar(((wchar & 0x3f))  + 0x80);
	}
	return (nb_bytes);
}