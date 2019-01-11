/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   octal.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcarles <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 17:35:30 by pcarles           #+#    #+#             */
/*   Updated: 2018/03/21 15:36:49 by pcarles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "private_ft_printf.h"

static int	ft_printf_octal(char *nb, t_arg *arg)
{
	int		res;

	res = ft_strlen(nb);
	if (arg->hashtag && (*nb != '0' || (arg->got_precision && !arg->precision)))
		res++;
	else if (arg->precision == 1 && *nb == '0')
		res++;
	res = ft_printf_check_precision(res, arg);
	res = ft_printf_put_width(res, arg, 0);
	if (arg->hashtag && (*nb != '0' || (arg->got_precision && !arg->precision)))
		ft_putchar('0');
	if (!(arg->got_precision && !arg->precision && *nb == '0'))
	{
		while (arg->precision--)
			ft_putchar('0');
		ft_putstr(nb);
	}
	else
		res--;
	res = ft_printf_put_width(res, arg, 1);
	free(nb);
	return (res);
}

int			ft_printf_o(va_list ap, t_arg *arg)
{
	int		res;
	char	*nb;

	nb = ft_printf_itoa_base(ft_printf_unsigned_conv(ap, arg), 8, 'a');
	res = ft_printf_octal(nb, arg);
	return (res);
}

int			ft_printf_lo(va_list ap, t_arg *arg)
{
	int		res;
	char	*nb;

	nb = ft_printf_itoa_base(va_arg(ap, long int), 8, 'a');
	res = ft_printf_octal(nb, arg);
	return (res);
}
