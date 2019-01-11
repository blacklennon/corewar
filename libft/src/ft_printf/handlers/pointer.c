/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pointer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcarles <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/04 16:29:47 by pcarles           #+#    #+#             */
/*   Updated: 2018/06/05 23:41:04 by pcarles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "private_ft_printf.h"

int			ft_printf_p(va_list ap, t_arg *arg)
{
	int		res;
	char	*nb;

	nb = ft_printf_itoa_base((uintmax_t)va_arg(ap, void *), 16, 'a');
	res = ft_strlen(nb) + 2;
	res = ft_printf_put_width(res, arg, 0);
	ft_putstr("0x");
	if (!(arg->got_precision && !arg->precision))
	{
		ft_putstr(nb);
		arg->precision = arg->precision ? arg->precision - 1 : arg->precision;
		while (arg->precision--)
		{
			ft_putchar('0');
			res++;
		}
	}
	else
		res--;
	res = ft_printf_put_width(res, arg, 1);
	free(nb);
	return (res);
}
