/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_01_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llopez <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 13:07:48 by llopez            #+#    #+#             */
/*   Updated: 2019/04/12 13:12:37 by llopez           ###   ########.fr       */
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

void    clean_data(char **data)
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
