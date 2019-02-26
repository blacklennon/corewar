/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcarles <pcarles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 16:08:29 by pcarles           #+#    #+#             */
/*   Updated: 2019/01/23 14:58:26 by pcarles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"
#include "utils.h"

void		init_instruction(t_instruction *instruction)
{
	ft_bzero(instruction->buffer, MAX_INSTRUCTION_SIZE);
	instruction->size = 0;
}

void		init_asm(t_asm *env)
{
	env->header.magic = COREWAR_EXEC_MAGIC;
	ft_bzero(env->header.prog_name, PROG_NAME_LENGTH + 1);
	env->header.prog_size = 0;
	ft_bzero(env->header.comment, COMMENT_LENGTH + 1);
	env->inst_list = NULL;
	env->label_list = NULL;
	env->index = 0;
}