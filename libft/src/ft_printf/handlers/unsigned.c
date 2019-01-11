/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsigned.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcarles <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 18:59:40 by pcarles           #+#    #+#             */
/*   Updated: 2018/03/08 15:00:54 by pcarles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "private_ft_printf.h"

static int	ft_printf_unsigned(char *nb, t_arg *arg)
{
	int		res;

	if (arg->got_precision && !arg->precision && *nb == '0')
		return (0);
	res = ft_strlen(nb);
	res = ft_printf_check_precision(res, arg);
	res = ft_printf_put_width(res, arg, 0);
	while (arg->precision--)
		ft_putchar('0');
	ft_putstr(nb);
	res = ft_printf_put_width(res, arg, 1);
	free(nb);
	return (res);
}

int			ft_printf_u(va_list ap, t_arg *arg)
{
	int		res;
	char	*nb;

	nb = ft_printf_itoa_base(ft_printf_unsigned_conv(ap, arg), 10, 'a');
	res = ft_printf_unsigned(nb, arg);
	return (res);
}

int			ft_printf_lu(va_list ap, t_arg *arg)
{
	int		res;
	char	*nb;

	nb = ft_printf_itoa_base(va_arg(ap, long int), 10, 'a');
	res = ft_printf_unsigned(nb, arg);
	return (res);
}
