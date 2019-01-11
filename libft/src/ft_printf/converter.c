/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   converter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcarles <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 14:02:28 by pcarles           #+#    #+#             */
/*   Updated: 2018/03/08 14:52:49 by pcarles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_ft_printf.h"

intmax_t	ft_printf_signed_conv(va_list ap, t_arg *arg)
{
	if (arg->hh)
		return ((char)va_arg(ap, int));
	if (arg->h)
		return ((short int)va_arg(ap, int));
	if (arg->ll)
		return (va_arg(ap, long long int));
	if (arg->l)
		return (va_arg(ap, long int));
	if (arg->j)
		return (va_arg(ap, intmax_t));
	if (arg->z)
		return (va_arg(ap, ssize_t));
	return (va_arg(ap, int));
}

uintmax_t	ft_printf_unsigned_conv(va_list ap, t_arg *arg)
{
	if (arg->hh)
		return ((unsigned char)va_arg(ap, unsigned int));
	if (arg->h)
		return ((unsigned short int)va_arg(ap, unsigned int));
	if (arg->ll)
		return (va_arg(ap, unsigned long long int));
	if (arg->l)
		return (va_arg(ap, unsigned long int));
	if (arg->j)
		return (va_arg(ap, uintmax_t));
	if (arg->z)
		return (va_arg(ap, size_t));
	return (va_arg(ap, unsigned int));
}
