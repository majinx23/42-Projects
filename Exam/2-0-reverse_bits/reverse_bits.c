#include <unistd.h>

unsigned char reverse(unsigned char b)
{
	b = (b & 0xF0) >> 4 | (b & 0x0F) << 4;
	b = (b & 0xCC) >> 2 | (b & 0x33) << 2;
	b = (b & 0xAA) >> 1 | (b & 0x55) << 1;
	return b;
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

