/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcarles <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 15:34:48 by pcarles           #+#    #+#             */
/*   Updated: 2018/05/21 11:15:49 by pcarles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "private_ft_printf.h"

static int	ft_printf_parse_flags(char argc, t_arg *arg)
{
	if (argc == '#')
		arg->hashtag = 1;
	else if (argc == '0')
		arg->zero = 1;
	else if (argc == '-')
		arg->minus = 1;
	else if (argc == '+')
		arg->plus = 1;
	else if (argc == ' ')
		arg->space = 1;
	else
		return (0);
	return (1);
}

static char	*ft_printf_parse_width(char *argc, t_arg *arg)
{
	int		res;

	res = 0;
	while (ft_isdigit(*argc))
	{
		res = res * 10 + *argc - '0';
		argc++;
	}
	arg->width = res;
	return (argc);
}

static char	*ft_printf_parse_precision(char *argc, t_arg *arg)
{
	int		res;

	res = 0;
	if (*argc == '.')
	{
		arg->got_precision = 1;
		argc++;
		while (ft_isdigit(*argc))
		{
			res = res * 10 + *argc - '0';
			argc++;
		}
		arg->precision = res;
		if (res == 0)
			arg->got_precision = 2;
	}
	return (argc);
}

static char	*ft_printf_parse_cast(char *argc, t_arg *arg)
{
	if (*argc == 'h')
	{
		if (*(argc + 1) == 'h')
			arg->hh = 1;
		else
			arg->h = 1;
	}
	else if (*argc == 'l')
	{
		if (*(argc + 1) == 'l')
			arg->ll = 1;
		else
			arg->l = 1;
	}
	else if (*argc == 'j')
		arg->j = 1;
	else if (*argc == 'z')
		arg->z = 1;
	else
		return (argc);
	if (arg->ll || arg->hh)
		return (argc + 2);
	return (argc + 1);
}

char		*ft_printf_parse_arg(char *argc, t_arg *arg)
{
	argc++;
	while (ft_printf_parse_flags(*argc, arg))
		argc++;
	argc = ft_printf_parse_width(argc, arg);
	argc = ft_printf_parse_precision(argc, arg);
	argc = ft_printf_parse_cast(argc, arg);
	return (argc);
}
