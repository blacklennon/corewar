/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcarles <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 15:32:59 by pcarles           #+#    #+#             */
/*   Updated: 2018/03/08 14:53:08 by pcarles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"
#include "private_ft_printf.h"

static int	ft_printf_find_params(char const **format, va_list ap)
{
	char	*next_arg;
	int		ret;
	int		(*converter[256])(va_list, t_arg*);
	t_arg	arg;

	ft_printf_init_handlers(converter);
	ft_printf_reset_arg(&arg);
	ret = 0;
	while ((next_arg = ft_strchr(*format, '%')))
	{
		ret += next_arg - *format;
		ft_putnstr(*format, next_arg - *format);
		*format = ft_printf_parse_arg(next_arg, &arg);
		if (ft_printf_check_conv(**format))
		{
			ret += converter[(int)**format](ap, &arg);
			*format += 1;
		}
		ft_printf_reset_arg(&arg);
	}
	ft_putstr(*format);
	return (ret + ft_strlen(*format));
}

int			ft_printf(char const *format, ...)
{
	va_list		ap;
	int			ret;

	if (!format)
		return (0);
	va_start(ap, format);
	ret = ft_printf_find_params(&format, ap);
	va_end(ap);
	return (ret);
}
