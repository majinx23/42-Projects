#include <unistd.h>

unsigned char reverse(unsigned char b)
{
	b = (b * 0x0202020202ULL & 0x010884422010ULL) % 1023;
	return (b);
}

int	main(void)
{
	unsigned char c;

	c = '.';
	write (1, &c, 1);
	c = reverse(c);
	write (1, &c, 1);
	return (0);
}

