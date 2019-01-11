/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcarles <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 19:22:39 by pcarles           #+#    #+#             */
/*   Updated: 2018/03/07 15:19:58 by pcarles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "private_ft_printf.h"

int		ft_printf_c(va_list ap, t_arg *arg)
{
	unsigned char	c;
	int				res;

	c = (unsigned char)va_arg(ap, int);
	res = 1;
	res = ft_printf_put_width(res, arg, 0);
	ft_putchar(c);
	res = ft_printf_put_width(res, arg, 1);
	return (res);
}

int		ft_printf_s(va_list ap, t_arg *arg)
{
	char	*str;
	int		res;

	str = va_arg(ap, char *);
	if (!str)
	{
		if (arg->got_precision && !arg->precision)
			str = "";
		else
			str = "(null)";
	}
	res = ft_strlen(str);
	if (arg->got_precision)
		res = arg->precision < res ? arg->precision : res;
	res = ft_printf_put_width(res, arg, 0);
	ft_putnstr(str, arg->got_precision ? arg->precision : res);
	res = ft_printf_put_width(res, arg, 1);
	return (res);
}

int		ft_printf_pourcent(va_list ap, t_arg *arg)
{
	int		res;

	(void)ap;
	res = 1;
	res = ft_printf_put_width(res, arg, 0);
	ft_putchar('%');
	res = ft_printf_put_width(res, arg, 1);
	return (res);
}
