/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcarles <pcarles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/11 20:02:59 by pcarles           #+#    #+#             */
/*   Updated: 2019/02/26 14:37:30 by pcarles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stddef.h>
# include <stdint.h>
# include "typedefs/s_label.h"
# include "op.h"

# define MAX_INSTRUCTION_SIZE 14

typedef struct s_asm
{
	t_header		header;
	struct s_instruction	*inst_list;
	t_label			*label_list;
	size_t			index;
}				t_asm;

typedef struct	s_instruction
{
	int8_t					buffer[MAX_INSTRUCTION_SIZE];
	size_t					size;
	t_arg_type				args_type[MAX_ARGS_NUMBER];
	t_label					*label;
	struct s_instruction	*next;
}				t_instruction;

void			create_label(char *name, int index, t_label **label_listp);
int				find_label(char *begin_pointer, char *end_pointer);
int				parse_line(char *line, t_asm *env);

#endif