/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcarles <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 15:25:47 by pcarles           #+#    #+#             */
/*   Updated: 2018/05/17 15:23:29 by pcarles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "private_ft_printf.h"

static uintmax_t	ft_printf_pow(unsigned int nb, unsigned int pow)
{
	uintmax_t	res;

	res = nb;
	pow--;
	while (pow--)
		res *= nb;
	return (res);
}

char				*ft_printf_itoa_base(uintmax_t nb, int base, char c)
{
	int		length;
	int		tmp;
	char	*res;
	char	*tmp_res;

	length = 1;
	while (ft_printf_pow(base, length) - 1 < nb)
		length++;
	res = ft_strnew(length);
	while (length-- > 0)
	{
		tmp = nb % base;
		res[length] = tmp + (tmp > 9 ? c - 10 : '0');
		nb /= base;
	}
	if (*res == '0' && res[1] != '\0')
	{
		tmp_res = res;
		while (*res == '0')
			res++;
		res = ft_strdup(res);
		free(tmp_res);
	}
	return (res);
}

int					ft_printf_check_precision(int nblen, t_arg *arg)
{
	if (arg->precision >= nblen)
		arg->precision -= nblen;
	else
		arg->precision = 0;
	nblen += arg->precision;
	return (nblen);
}

int					ft_printf_put_width(int nblen, t_arg *arg, int check)
{
	while (arg->width > nblen && !arg->minus)
	{
		ft_putchar(arg->zero && !arg->got_precision ? '0' : ' ');
		nblen++;
	}
	while (arg->width > nblen && arg->minus && check)
	{
		ft_putchar(' ');
		nblen++;
	}
	return (nblen);
}

void				ft_printf_reset_arg(t_arg *arg)
{
	arg->len = 0;
	arg->hashtag = 0;
	arg->force_hashtag = 0;
	arg->zero = 0;
	arg->minus = 0;
	arg->plus = 0;
	arg->space = 0;
	arg->width = 0;
	arg->got_precision = 0;
	arg->precision = 0;
	arg->hh = 0;
	arg->h = 0;
	arg->ll = 0;
	arg->l = 0;
	arg->j = 0;
	arg->z = 0;
}
