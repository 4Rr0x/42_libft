/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopedro- <jopedro-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 13:18:50 by jopedro-          #+#    #+#             */
/*   Updated: 2024/11/07 13:19:20 by jopedro-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_checkformat(va_list args, const char format)
{
	int	len;

	len = 0;
	if (format == 'c')
		len += ft_putchar_fd((va_arg(args, int)), 1);
	else if (format == 's')
		len += ft_putstr_fd((va_arg(args, char *)), 1);
	else if (format == 'p')
		len += ft_printptr((va_arg(args, unsigned long long)));
	else if (format == 'd' || format == 'i')
		len += ft_printnbr((va_arg(args, int)));
	else if (format == 'u')
		len += ft_printunsigned((va_arg(args, unsigned int)));
	else if (format == 'x' || format == 'X')
		len += ft_printhex((va_arg(args, unsigned int)), format);
	else if (format == '%')
		len += write (1, "%", 1);
	return (len);
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		len;

	len = 0;
	va_start(ap, format);
	while (*format)
	{
		if (*format == '%')
		{
			len += ft_checkformat(ap, *(format + 1));
			format++;
		}
		else
			len += ft_putchar_fd(*format, 1);
		if (*format)
			format++;
	}
	va_end(ap);
	return (len);
}
