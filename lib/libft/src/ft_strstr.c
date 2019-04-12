/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcarles <pcarles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 10:45:59 by llopez            #+#    #+#             */
/*   Updated: 2019/04/08 19:18:45 by pcarles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(char const *str, char const *search)
{
	int i;
	int b;

	b = 0;
	i = 0;
	if (!*search)
		return ((char *)str);
	while (str[i])
	{
		b = 0;
		while (b + 1 <= ft_strlen(search) && search[b] == str[i + b])
			b++;
		if (b == ft_strlen(search))
			return ((char *)&str[i]);
		i++;
	}
	return (NULL);
}
