/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcarles <pcarles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/11 20:02:59 by pcarles           #+#    #+#             */
/*   Updated: 2019/01/17 14:31:56 by pcarles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stddef.h>
# include <stdint.h>
# include "op.h"

# define MAX_INSTRUCTION_SIZE 14

typedef struct		s_label
{
	char			*name;
	size_t			index;
	struct s_instruction	*instruction;
	struct s_label	*next;
}					t_label;

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
t_label			*find_label(char *name, t_label *label_list);
int				parse_line(char *line, t_asm *env);

#endif