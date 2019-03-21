/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llopez <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 17:49:49 by llopez            #+#    #+#             */
/*   Updated: 2019/03/19 18:49:47 by llopez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include "../../lib/libft/includes/libft.h"
#include "../../includes/op.h"
#include "../../includes/asm.h"

int			tokenizer(char *str)
{
	int	ret;
	int	i;

	i = 0;
	ret = 1;
	while (str[i])
	{
		ret += (i+1) * str[i];
		i++;
	}
	return (ret);
}

uint32_t	*interpret(char **program, int fd)
{
	int			i;
	int			a;
	uint32_t	*table;

	table = NULL;
	a = 0;
	(void)fd;
	while (program[a])
	{
		i = 1;
		while (i < 17)
		{
			i++;
		}
		a++;
	}
	return (table);
}
