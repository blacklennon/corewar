/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcarles <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 17:23:51 by pcarles           #+#    #+#             */
/*   Updated: 2018/05/17 15:57:39 by pcarles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "private_ft_printf.h"

void	ft_printf_plusspace(t_arg *arg)
{
	if (arg->plus)
		ft_putchar('+');
	else if (arg->space && !arg->plus)
		ft_putchar(' ');
}

int		ft_printf_widthneg(t_arg *arg, int res, int n, int length)
{
	int	width;

	width = arg->width - 1;
	if (arg->minus == n)
	{
		if (arg->precision > -1 && arg->precision > length)
			width -= arg->precision;
		else
			width -= length;
		while (width > 0)
		{
			ft_putchar((arg->zero) ? '0' : ' ');
			++res;
			--width;
		}
	}
	return (res);
}
