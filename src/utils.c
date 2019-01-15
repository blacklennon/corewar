/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcarles <pcarles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 16:08:29 by pcarles           #+#    #+#             */
/*   Updated: 2019/01/15 18:27:45 by pcarles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"
#include "utils.h"

void		print_usage(void)
{
	ft_putstr("usage: ./asm source_file.s\n");
}

void		init_instruction(t_instruction *instruction)
{
	ft_bzero(instruction->buffer, MAX_INSTRUCTION_SIZE);
	instruction->size = 0;
}