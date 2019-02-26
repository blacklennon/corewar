/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcarles <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 11:05:36 by pcarles           #+#    #+#             */
/*   Updated: 2018/02/14 12:01:50 by pcarles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

void	ft_putnstr(char const *s, int len)
{
	int i;

	if (s)
	{
		i = ft_strlen(s);
		write(1, s, i < len ? i : len);
	}
}
