/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/28 19:18:44 by angavrel          #+#    #+#             */
/*   Updated: 2017/02/13 06:33:59 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/ft_printf.h"

/*
** 						~ PRINTF LOOP ~
**
** printf will return p.len: the total len of what was displayed by printf
** if there is a % we will parse user input, else we will display it.
*/

int		ft_printf(char *format, ...)
{
	va_list		ap;
	t_printf	p;

	va_start(ap, format);
	p.len = 0;
	while (*format)
	{
		if (*format == '%')
		{
			p.printed = 0;
			if (!format[1])
				break;
			format = parse_optionals(++format, &p);
			if (*format == '%')
				p.len += percent_char(&p);
			format = conversion_specifier(format, ap, &p);
		//	ft_putchar(*format);
		}
		
		else
			p.len += p_putchar(*format);
		++format;
	}
	va_end(ap);
	return (p.len);
}

/*
** 						~ CONVERSION SPECIFIER ~
**
** A character that specifies the type of conversion to be applied
** if the character following % is a % then is it acts as an ESC char
** The conversion specifiers and their meanings are:
** 1) d, i, D : signed int
** 2) o, u, x, X : unsigned octal, uns. decimal, uns. hexa lower and uppercase
** 3) b, B for unsigned binary
** 3) c, C : char and large char
** 4) s : pointer to a string
** 5) n : the number of characters written so far is stored into the integer
** indicated by the int * pointer argument. No argument is converted.
** 6) m : Print output of strerror(errno). no arg. required
** 7) {} : adds color
** if the character is uppercase then p->cs.uppercase will be set to 1.
*/

char	*conversion_specifier(char *format, va_list ap, t_printf *p)
{
	p->cs.upcase = 0;
	(*format == 'd' || *format == 'D' || *format == 'i') ?
		p->len += p_putnb(ap, p) : 0;
	(*format == 'b' || *format == 'B') ? p->len += p_putnb_base(2, ap, p) : 0;
	(*format == 'o' || *format == 'O') ? p->len += p_putnb_base(8, ap, p) : 0;
	(*format == 'u' || *format == 'U') ? p->len += p_putnb_base(10, ap, p) : 0;
	(*format == 'X') ? p->cs.upcase = 1 : 0;
	(*format == 'x' || *format == 'X') ? p->len += p_putnb_base(16, ap, p) : 0;
	if (*format == 'C' || *format == 'D' || *format == 'S' || *format == 'U')
		p->lm.llong = 1;
	(*format == 'c' || *format == 'C') ? p->len += character(ap, p) : 0;
	if (*format == 's' || *format == 'S')
		p->len += p->lm.llong ? wide_string(ap, p) : string(ap, p);
	(*format == 'p') ? p->len += print_pointer_address(ap, p) : 0;
	(*format == 'n') ? print_len(ap, p->len) : 0;
	(*format == 'm') ? p->len += ft_printf_putstr(strerror(errno)) : 0;
	if (*format == '{')
		return (color(format, p));
	if (!ft_strchr("sSpdDibBoOuUxXcC%nm", *format))
		ft_putnchar(p->min_length, ((p->flags.zero) ?
			'0' : ' '));
			//ft_putnchar(p->min_length - MIN(1, p->min_length), ((p->flags.zero) ?
			//'0' : ' '));
	return (format);
}

/*
** small function that displays printf current value
*/

void	print_len(va_list ap, int len)
{
	int *pointer;

	pointer = va_arg(ap, int *);
	*pointer = len;
}

/*
** function used to adjust length for padding due to the flag -
*/

void	ft_putnchar(int len, char c)
{
	while (len--)
		ft_putchar(c);
}

/*
** bonus function that handles colors
*/

char	*color(char *format, t_printf *p)
{
	p->printed = 5;
	if (!ft_strncmp(format, "{red}", ft_strlen("{red}")))
		COLOR(PF_RED, 5);
	else if (!ft_strncmp(format, "{green}", ft_strlen("{green}")))
		COLOR(PF_GREEN, 7);
	else if (!ft_strncmp(format, "{yellow}", ft_strlen("{yellow}")))
		COLOR(PF_YELLOW, 8);
	else if (!ft_strncmp(format, "{blue}", ft_strlen("{blue}")))
		COLOR(PF_BLUE, 6);
	else if (!ft_strncmp(format, "{purple}", ft_strlen("{purple}")))
		COLOR(PF_PURPLE, 8);
	else if (!ft_strncmp(format, "{cyan}", ft_strlen("{cyan}")))
		COLOR(PF_CYAN, 6);
	else if (!ft_strncmp(format, "{eoc}", ft_strlen("{eoc}")))
		COLOR(PF_EOC, 5);
	else
		p->printed = 0;
	p->len += p->printed;
	return (format - 1);
}