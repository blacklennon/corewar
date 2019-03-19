/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_process.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcarles <pcarles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 16:43:08 by pcarles           #+#    #+#             */
/*   Updated: 2019/03/19 17:59:26 by llopez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef S_PROCESS_H
# define S_PROCESS_H

# include <stddef.h>
# include <stdint.h>
# include <stdio.h>
# include "op.h"

// We should rename those two typedefs (enum and union) to a more comprehensive name
// typedef union			u_int_types
// {
// 	int8_t				u_reg;
// 	int16_t				u_ind;
// 	int16_t				u_dir16;
// 	int32_t				u_dir32;
// }						t_int_types;

// typedef enum			u_int_types_enum
// {
// 	e_none, e_reg, e_ind, e_dir
// }						t_int_types_enum;

// typedef	struct 			s_args
// {
// 	t_int_types_enum	type[3];
// 	t_int_types			value[3];
// }						t_args;

// typedef struct			s_process
// {
// 	char				*file_path;
// 	char				name[PROG_NAME_LENGTH + 1];
// 	char				comment[COMMENT_LENGTH + 1];
// 	size_t				program_counter;
// 	uint8_t				carry;
// 	int32_t				registers[REG_NUMBER]; // c est bien ici qu on doit set les valeurs des registres
// 	size_t				live_counter;
// 	size_t				next_op;
// }						t_process;

// typedef struct			s_vm
// {
// 	uint8_t				memory[MEM_SIZE];
// 	size_t				nb_champs;
// 	struct s_process	process[MAX_PLAYERS];
// 	size_t				cycle;
// }						t_vm;

// typedef struct			s_op
// {
// 	char				*name;
// 	uint8_t				nb_params;
// 	t_arg_type			params[MAX_ARGS_NUMBER];
// 	t_op_code			code;
// 	uint32_t			cycles;
// 	char				*description;
// 	uint8_t				ocp; // booleen 1/0 est-ce que je dois lire l'ocp
// 	uint8_t				little_dir; // boolean 1/0 est-ce que c'est un direct de taille 16/32 bits 2/4 BYTES; 
// 	void				(*func)(t_process*, t_args*, t_vm*);
// }						t_op;

#endif
