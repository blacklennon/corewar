/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llopez <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 17:49:49 by llopez            #+#    #+#             */
/*   Updated: 2019/03/19 17:27:27 by llopez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include "../../lib/libft/includes/libft.h"
#include "../../includes/op.h"
#include "asm.h"

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

uint32_t	*interpret(char **program)
{
	int			i;
	uint32_t	*table;

	table = NULL;
	i = 0;
	while (program[i])
	{
		printf("string = '%s'\t\ttoken = %d\n", program[i], \
				tokenizer(program[i]));
		i++;
	}
	return (table);
}
