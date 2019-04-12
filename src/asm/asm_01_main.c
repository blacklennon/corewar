/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_01_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llopez <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 13:07:48 by llopez            #+#    #+#             */
/*   Updated: 2019/04/12 15:10:11 by llopez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include "libft.h"
#include "ft_printf.h"
#include "common.h"
#include "op.h"
#include "asm.h"

int		ft_str_is_ascii(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isascii(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	clean_data(char **data)
{
	int		i;
	char	*tmp;

	i = 0;
	while (data[i])
	{
		tmp = ft_strtrim(data[i]);
		free(data[i]);
		data[i] = tmp;
		i++;
	}
}
