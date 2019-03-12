/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_process.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcarles <pcarles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 16:43:08 by pcarles           #+#    #+#             */
/*   Updated: 2019/03/12 12:12:15 by pcarles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef S_PROCESS_H
# define S_PROCESS_H

# include <stddef.h>
# include <stdint.h>
#include <stdio.h>
# include "op.h"

#define T_REG					1
#define T_DIR					2
#define T_IND					4
#define T_LAB					8

# define REG_CODE				1
# define DIR_CODE				2
# define IND_CODE				3

typedef enum	e_type
{
	LIVE = 1,
	LD = 2,
	ST = 3,
	ADD = 4,
	SUB = 5,
	AND = 6,
	OR = 7,
	XOR = 8,
	ZJMP = 9,
	LDI = 10,
	STI = 11,
	FORK = 12,
	LLD = 13,
	LLDI = 14,
	LFORK = 15,
	AFF = 16
}				t_type;

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

// recuperer le premier param ocp si c'etait un int_8
// t_ocp ocp;  ocp->first_param.regist; 
// recuperer le premier param ocp si cetait un int_16
// t_ocp ocp;  ocp->first_param.direct_16; 

typedef char			t_arg_type;

typedef struct			s_op
{
	char				*name;
	uint8_t				nb_params;
	t_arg_type			params[MAX_ARGS_NUMBER];
	uint8_t				code;
	uint32_t			cycles;
	char				*description;
	uint8_t				ocp; // booleen 1/0 est-ce que je dois lire l'ocp
	uint8_t				little_dir; // boolean 1/0 est-ce que c'est un direct de taille 16/32 bits 2/4 BYTES; 
} 						t_op;

t_op		op_tab[17] =
{
	{"live", 1, {T_DIR}, LIVE, 10, "alive", 0, 0},
	{"ld", 2, {T_DIR | T_IND, T_REG}, LD, 5, "load", 1, 0},
	{"st", 2, {T_REG, T_IND | T_REG}, ST, 5, "store", 1, 0},
	{"add", 3, {T_REG, T_REG, T_REG}, ADD, 10, "addition", 1, 0},
	{"sub", 3, {T_REG, T_REG, T_REG}, SUB, 10, "soustraction", 1, 0},
	{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, AND, 6, "et (and  r1, r2, r3   r1&r2 -> r3", 1, 0},
	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, OR, 6, "ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0},
	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, XOR, 6, "ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0},
	{"zjmp", 1, {T_DIR}, ZJMP, 20, "jump if zero", 0, 1},
	{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, LDI, 25, "load index", 1, 1},
	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, STI, 25, "store index", 1, 1},
	{"fork", 1, {T_DIR}, FORK, 800, "fork", 0, 1},
	{"lld", 2, {T_DIR | T_IND, T_REG}, LLD, 10, "long load", 1, 0},
	{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, LLDI, 50, "long load index", 1, 1},
	{"lfork", 1, {T_DIR}, LFORK, 1000, "long fork", 0, 1},
	{"aff", 1, {T_REG}, AFF, 2, "aff", 1, 0},
	{NULL, 0, {0}, 0, 0, 0, 0, 0}
};

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
	void				(*op_table[17])(t_process*, struct s_vm*);
}						t_vm;

/*
** STRUCTURES FUNCTIONS
*/
// t_instruct				*create_instruct(void);
// void					add_to_end_instruct_chain(t_instruct **begin_chain, t_instruct *elem);
// t_process				*create_process(void);
// t_process   			**create_all_process(int nbr_players);
/*
**	UTILS
// */
// void					*ft_malloc(size_t size);
// void					print_instruct_type(t_instruct *instruct);

#endif
