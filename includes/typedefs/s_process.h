/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_process.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcarles <pcarles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 16:43:08 by pcarles           #+#    #+#             */
/*   Updated: 2019/03/12 14:29:16 by pcarles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef S_PROCESS_H
# define S_PROCESS_H

# include <stddef.h>
# include <stdint.h>
# include <stdio.h>
# include "op.h"

typedef union			u_int_types
{
	int8_t				reg;
	int16_t				ind;
	int16_t				dir_16;
	int32_t				dir_32;
}						t_int_types;

typedef enum			u_int_types_enum
{
	int_8, int_16, int_32
}						t_int_types_enum;

typedef	struct 			s_arguments
{
	t_int_types_enum	first_param_type;
	t_int_types			first_param;
	t_int_types_enum	second_param_type;
	t_int_types			second_param;
	t_int_types_enum	third_param_type;
	t_int_types 		third_param;
}						t_arguments;

typedef struct			s_process
{
	char				*file_path;
	char				name[PROG_NAME_LENGTH + 1];
	char				comment[COMMENT_LENGTH + 1];
	size_t				program_counter;
	uint8_t				carry;
	int32_t				registers[REG_NUMBER]; // c est bien ici qu on doit set les valeurs des registres
	size_t				live_counter;
	size_t				next_op;
}						t_process;

typedef struct			s_vm
{
	uint8_t				memory[MEM_SIZE];
	size_t				nb_champs;
	struct s_process	process[MAX_PLAYERS];
	size_t				cycle;
}						t_vm;

#endif
