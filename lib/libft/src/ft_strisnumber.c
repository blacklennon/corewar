/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strisnumber.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcarles <pcarles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 22:16:11 by pcarles           #+#    #+#             */
/*   Updated: 2019/04/09 10:25:08 by pcarles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_strisnumber(char *str)
{
	if (*str == '-' || *str == '+')
		str++;
	return (ft_stris(str, &ft_isdigit));
}