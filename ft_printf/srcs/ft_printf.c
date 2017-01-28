/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/28 19:18:44 by angavrel          #+#    #+#             */
/*   Updated: 2017/01/28 20:41:36 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	new_flags(t_flags *flags)
{
	flags->printed = 0;

	flags->a_sharp = 0;
	flags->a_zero= 0;
	flags->a_minus = 0;
	flags->a_plus = 0;
	flags->a_space = 0;

	flags->min_length = 0;
	flags->precision = 1;

	flags->l_long = 0;
	flags->l_short = 0;
	flags->l_intmax = 0;
	flags->l_sizet = 0;

	flags->uppercase = 0;
	flags->apply_precision = 0;
}

char		*percent(char *format, va_list ap, int *flag_len)
{
	t_flags	*flags;

	if (!(flags = (t_flags *)malloc(sizeof(t_flags))))
		return (NULL);
	new_flags(flags);
	format = search_flags((char *)format, flags);
	//fait les conversions, et retourne un pointeur sur la suite du texte.
	if (*format == 'C' || *format == 'D' || *format == 'S')
		flags->l_long = 1; //flag long (raccourcis)
	if (*format == '%')
	{
		ft_putstr("%");
		return (format);
	}
	if (*format == '{')
		return (color(format));
	(*format == 'S' || *format == 's') ? string(ap, flags) : 0;
	(*format == 'D' || *format == 'd' || *format == 'i') ? number(ap, flags) : 0;
	(*format == 'p') ? pointer(ap, flags) : 0;
	(*format == 'C' || *format == 'c') ? character(ap, flags) : 0;
	(*format == 'o' || *format == 'O') ? nbr_base(8, ap, flags) : 0;
	(*format == 'u' || *format == 'U') ? nbr_base(10, ap, flags) : 0;
	(*format == 'X') ? flags->uppercase = 1 : 0;
	(*format == 'x' || *format == 'X') ? nbr_base(16, ap, flags) : 0;
	//msg_die("Format is not recognized");
	*flag_len = (int)ft_strlen(format);
	return(format);
}

int			ft_printf(const char *restrict format, ...)
{
	va_list	ap;
	char	*s;
	int		len;
	int		flag_len;

	len = 0;
	va_start(ap, format);
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			if (!(s = percent((char *)format, ap, &flag_len)))
				return (-1);
			write(1, s, flag_len);
			free(s);
			len += flag_len - 1;
		}
		ft_putchar(*format++);
		++len;
	}
	va_end(ap);
	return (len);
}



