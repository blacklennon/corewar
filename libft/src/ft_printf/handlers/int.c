/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcarles <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 14:26:38 by pcarles           #+#    #+#             */
/*   Updated: 2018/05/17 15:56:11 by pcarles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "private_ft_printf.h"

static int		ft_printf_int_pos(t_arg *arg, char *nb, int res)
{
	if (arg->plus || arg->space)
		arg->width--;
	res = (*nb != '0' || arg->got_precision != 2) ? res + ft_strlen(nb) : res;
	res = ft_printf_check_precision(res, arg);
	if (arg->zero && arg->precision == 0)
		ft_printf_plusspace(arg);
	res = ft_printf_put_width(res, arg, 0);
	if (!arg->zero || (arg->zero && arg->precision))
		ft_printf_plusspace(arg);
	while (arg->precision--)
		ft_putchar('0');
	if (*nb != '0' || arg->got_precision != 2)
		ft_putstr(nb);
	res = ft_printf_put_width(res, arg, 1);
	res = (arg->plus || arg->space) ? res + 1 : res;
	return (res);
}

static int		ft_printf_int_neg(t_arg *arg, char *nb, int res)
{
	int			length;
	int			precision;

	length = ft_strlen(nb);
	arg->zero = (arg->precision > 0) ? 0 : arg->zero;
	precision = arg->precision;
	res += length;
	res = (!arg->zero) ? ft_printf_widthneg(arg, res, 0, length) : res;
	ft_putchar('-');
	res = (arg->zero && arg->width > 0) ? \
	ft_printf_widthneg(arg, res, 0, length) : res;
	while (precision-- > length)
	{
		ft_putchar('0');
		res++;
	}
	ft_putstr(nb);
	res = ft_printf_widthneg(arg, res, 1, length);
	return (res);
}

static int		ft_printf_int(intmax_t src_nb, t_arg *arg)
{
	int			res;
	int			neg;
	char		*nb;

	res = 0;
	neg = 0;
	arg->zero = (arg->minus == 1) ? 0 : arg->zero;
	if (src_nb < 0)
	{
		neg = 1;
		src_nb = -src_nb;
		res = 1;
	}
	nb = ft_printf_itoa_base(src_nb, 10, 'a');
	if (neg)
		res = ft_printf_int_neg(arg, nb, res);
	else
		res = ft_printf_int_pos(arg, nb, res);
	free(nb);
	return (res);
}

int				ft_printf_ld(va_list ap, t_arg *arg)
{
	int			res;

	res = ft_printf_int(va_arg(ap, long int), arg);
	return (res);
}

int				ft_printf_d(va_list ap, t_arg *arg)
{
	int			res;

	res = ft_printf_int(ft_printf_signed_conv(ap, arg), arg);
	return (res);
}
