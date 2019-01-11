/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_handlers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcarles <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/16 19:11:05 by pcarles           #+#    #+#             */
/*   Updated: 2018/05/17 16:03:30 by pcarles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "private_ft_printf.h"

void	ft_printf_init_handlers(int (*converter[256])(va_list ap, t_arg *arg))
{
	converter['x'] = &ft_printf_x;
	converter['X'] = &ft_printf_lx;
	converter['p'] = &ft_printf_p;
	converter['o'] = &ft_printf_o;
	converter['O'] = &ft_printf_lo;
	converter['u'] = &ft_printf_u;
	converter['U'] = &ft_printf_lu;
	converter['c'] = &ft_printf_c;
	converter['s'] = &ft_printf_s;
	converter['i'] = &ft_printf_d;
	converter['d'] = &ft_printf_d;
	converter['D'] = &ft_printf_ld;
	converter['C'] = &ft_printf_lc;
	converter['S'] = &ft_printf_ls;
	converter['%'] = &ft_printf_pourcent;
}

int		ft_printf_check_conv(char c)
{
	if (c == 'x' || c == 'X' || c == 'p' || c == 'o' || c == 'O' || c == 'u' \
		|| c == 'U' || c == 'c' || c == 's' || c == 'i' || c == 'd' \
		|| c == 'D' || c == 'C' || c == 'S' || c == '%')
		return (1);
	else
		return (0);
}
