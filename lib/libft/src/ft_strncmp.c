/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcarles <pcarles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 15:41:49 by pcarles           #+#    #+#             */
/*   Updated: 2019/01/22 19:45:39 by pcarles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(char const *s1, char const *s2, size_t n)
{
	unsigned char	*s1_uc;
	unsigned char	*s2_uc;
	size_t			tmp;

	if (!n)
		return (0);
	s1_uc = (unsigned char *)s1;
	s2_uc = (unsigned char *)s2;
	if ((tmp = ft_strlen(s1)) < n)
		n = tmp;
	if ((tmp = ft_strlen(s2)) < n)
		n = tmp;
	while (--n && *s1_uc == *s2_uc)
	{
		s1_uc++;
		s2_uc++;
	}
	return ((int)(*s1_uc - *s2_uc));
}
