/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wchar.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcarles <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 15:19:16 by pcarles           #+#    #+#             */
/*   Updated: 2018/03/08 15:01:10 by pcarles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "private_ft_printf.h"

static char	*ft_printf_wchar(wchar_t wc, char *c)
{
	if (wc <= 0x7f)
		c[0] = wc;
	else if (wc <= 0x7ff)
	{
		c[0] = ((wc & 0x7c0) >> 6) + 0xc0;
		c[1] = (wc & 0x3f) + 0x80;
	}
	else if (wc <= 0xffff)
	{
		c[0] = ((wc & 0xf000) >> 12) + 0xe0;
		c[1] = ((wc & 0xfc) >> 6) + 0xc8;
		c[2] = (wc & 0x3f) + 0x80;
	}
	else if (wc <= 0x1fffff)
	{
		c[0] = ((wc & 0x1c0000) >> 18) + 0xf0;
		c[1] = ((wc & 0x3f000) >> 12) + 0x80;
		c[2] = ((wc & 0xfc) >> 6) + 0x80;
		c[3] = (wc & 0x3f) + 0x80;
	}
	return (c);
}

int			ft_printf_lc(va_list ap, t_arg *arg)
{
	wchar_t		wc;
	char		*c;
	int			res;

	wc = va_arg(ap, wchar_t);
	c = ft_strnew(4);
	res = ft_printf_put_width(1, arg, 1);
	c = ft_printf_wchar(wc, c);
	ft_putstr(c);
	free(c);
	return (res);
}

int			ft_printf_ls(va_list ap, t_arg *arg)
{
	wchar_t		*wc;
	char		*c;
	int			i;

	(void)arg;
	c = ft_strnew(4);
	i = 0;
	wc = va_arg(ap, wchar_t*);
	while (*wc)
	{
		ft_printf_wchar(*wc, c);
		ft_putstr(c);
		ft_bzero(c, 4);
		i++;
		wc++;
	}
	free(c);
	return (i);
}
