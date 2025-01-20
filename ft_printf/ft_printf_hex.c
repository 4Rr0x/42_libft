/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopedro- <jopedro-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 13:18:54 by jopedro-          #+#    #+#             */
/*   Updated: 2024/11/07 13:19:19 by jopedro-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_hex_len(unsigned int nbr)
{
	int	len;

	len = 0;
	if (nbr == 0)
		return (1);
	while (nbr != 0)
	{
		nbr /= 16;
		len++;
	}
	return (len);
}

void	ft_puthex(unsigned int nbr, char *hex)
{
	if (nbr >= 16)
	{
		ft_puthex(nbr / 16, hex);
		ft_puthex(nbr % 16, hex);
	}
	else
		ft_putchar_fd(hex[nbr], 1);
}

int	ft_printhex(unsigned int nbr, const char format)
{
	char	*hex;

	if (format == 'x')
		hex = "0123456789abcdef";
	else
		hex = "0123456789ABCDEF";
	ft_puthex(nbr, hex);
	return (ft_hex_len(nbr));
}
