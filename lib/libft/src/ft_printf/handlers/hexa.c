/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hexa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcarles <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 17:54:03 by pcarles           #+#    #+#             */
/*   Updated: 2018/06/04 17:14:13 by pcarles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "private_ft_printf.h"

static int	ft_printf_put_prec(t_arg *arg, char *nb, int res)
{
	while (arg->precision--)
		ft_putchar('0');
	if (!(arg->force_hashtag && *nb == '0'))
		ft_putstr(nb);
	res = ft_printf_put_width(res, arg, 1);
	free(nb);
	return (res);
}

static int	ft_printf_hexa(char *nb, t_arg *arg, char *format)
{
	int		res;
	int		flag;

	flag = 0;
	if (arg->got_precision && !arg->precision && *nb == '0')
	{
		while (++flag <= arg->width)
			ft_putchar(' ');
		return (arg->width);
	}
	res = ft_strlen(nb);
	res = ft_printf_check_precision(res, arg);
	if (arg->hashtag && (*nb != '0' || arg->force_hashtag))
	{
		if ((arg->zero && !arg->got_precision) || arg->force_hashtag)
		{
			ft_putstr(format);
			flag = 1;
		}
		res += 2;
	}
	res = ft_printf_put_width(res, arg, 0);
	if (arg->hashtag && !flag && (*nb != '0' || arg->force_hashtag))
		ft_putstr(format);
	return (ft_printf_put_prec(arg, nb, res));
}

int			ft_printf_x(va_list ap, t_arg *arg)
{
	int		res;
	char	*nb;

	nb = ft_printf_itoa_base(ft_printf_unsigned_conv(ap, arg), 16, 'a');
	res = ft_printf_hexa(nb, arg, "0x");
	return (res);
}

int			ft_printf_lx(va_list ap, t_arg *arg)
{
	int		res;
	char	*nb;

	nb = ft_printf_itoa_base(ft_printf_unsigned_conv(ap, arg), 16, 'A');
	res = ft_printf_hexa(nb, arg, "0X");
	return (res);
}
