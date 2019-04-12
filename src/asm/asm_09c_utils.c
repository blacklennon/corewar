/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_09c_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdouniol <jdouniol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 14:22:03 by llopez            #+#    #+#             */
/*   Updated: 2019/04/12 17:29:25 by llopez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include "libft.h"
#include "common.h"
#include "op.h"
#include "asm.h"

int		print_binary(int fd, t_binary *bin)
{
	return (write(fd, bin->table, bin->size));
}

char	*ft_strjstr(char const *str, char const *search)
{
	int i;
	int b;

	b = 0;
	i = 0;
	if (!search || !str)
		return (NULL);
	while (str && str[i])
	{
		b = 0;
		while (str[i + b] && search[b] && search[b] == str[i + b])
			b++;
		if ((size_t)b == ft_strlen(search) && ((!i\
			|| ft_isspace(str[i - 1]))\
				&& ft_isspace(str[i + b])))
			return ((char *)&str[i]);
		i++;
	}
	return (NULL);
}

char	*get_label(char *param)
{
	char	*label;

	if (param[0] == DIRECT_CHAR)
		label = (where_is(&param[1], ',') > 0) ? ft_strsub(param, 2,\
			where_is(&param[1], ',')) : ft_strsub(param, 2,\
				ft_strlen(param) - 2);
	else
		label = (where_is(&param[1], ',') > 0) ? ft_strsub(param, 1,\
			where_is(&param[1], ',')) : ft_strsub(param, 1,\
				ft_strlen(param) - 1);
	return (label);
}
