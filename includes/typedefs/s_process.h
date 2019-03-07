/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_process.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcarles <pcarles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 16:43:08 by pcarles           #+#    #+#             */
/*   Updated: 2019/03/02 17:48:00 by pcarles          ###   ########.fr       */
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

typedef enum 	e_type
{
	LIVE = 0, 
	LD = 1, 
	ST = 2, 
	ADD = 3, 
	SUB = 4,
	AND = 5, OR, XOR, ZJMP, LDI, STI, FORK, LLD, LLDI,\
	LFORK, AFF
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

typedef char			t_arg_type;

typedef struct            s_op
{
    char                *name;
    t_type				type;
    int8_t              nb_params;
    t_arg_type          params[MAX_ARGS_NUMBER];
    int8_t              code;
    int                 cycles;
    char                *description;
    char                ocp; // booleen 1/0 est-ce que je dois lire l'ocp
    char                little_dir; // boolean 1/0 est-ce que c'est un direct de taille 16/32 bits 2/4 BYTES; 
} 						t_op;

typedef	struct 			s_ocp
{
	t_int_types_enum	first_param_type;
	t_int_types			first_param;
	t_int_types_enum	second_param_type;
	t_int_types			second_param;
	t_int_types_enum	third_param_type;
	t_int_types 		third_param;
}						t_ocp;

// recuperer le premier param ocp si c'etait un int_8
// t_ocp ocp;  ocp->first_param.regist; 
// recuperer le premier param ocp si cetait un int_16
// t_ocp ocp;  ocp->first_param.direct_16; 

t_op    op_tab[17] =
{
	{"live", LIVE, 1, {T_DIR}, 1, 10, "alive", 0, 0},
	{"ld", LD, 2, {T_DIR | T_IND, T_REG}, 2, 5, "load", 1, 0},
	// TODO : PAS OUBLIER DE RAJOUTER LE TYPE EN 2IEME PARAM
	{"st", 2, {T_REG, T_IND | T_REG}, 3, 5, "store", 1, 0},
	{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 1, 0},
	{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction", 1, 0},
	{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6,
		"et (and  r1, r2, r3   r1&r2 -> r3", 1, 0},
	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6,
		"ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0},
	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6,
		"ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0},
	{"zjmp", 1, {T_DIR}, 9, 20, "jump if zero", 0, 1},
	{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25,
		"load index", 1, 1},
	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25,
		"store index", 1, 1},
	{"fork", 1, {T_DIR}, 12, 800, "fork", 0, 1},
	{"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, "long load", 1, 0},
	{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50,
		"long load index", 1, 1},
	{"lfork", 1, {T_DIR}, 15, 1000, "long fork", 0, 1},
	{"aff", 1, {T_REG}, 16, 2, "aff", 1, 0},
	{NULL, 0, {0}, 0, 0, 0, 0, 0}
};





typedef struct 			s_instruct
{
	t_type				type;
//	int					tab_utils[9];
	uint8_t				ocp;
	uint32_t			nb_champ;
	uint8_t				reg_1_0;
	uint8_t				reg_2_1;
	uint8_t				reg_3_2;
	uint16_t			ind_1_3;
	uint16_t			ind_2_4;
	uint16_t			dir_16_1_5;
	uint16_t			dir_16_2_6;
	uint32_t			dir_32_1_7;
	uint32_t			dir_32_2_8;
	struct s_instruct	*prev; // inutile
	struct s_instruct	*next; // inutile
	int32_t				value_arg1;
	int32_t				value_arg2;
	int32_t				value_arg3;/*
	int32_t				value_reg1;
	int32_t				value_reg2;
	int32_t				value_reg3;
	int32_t				value_ind1;
	int32_t				value_ind2;
	int32_t				value_dir1;
	int32_t				value_dir2;*/
}						t_instruct;

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
	struct s_instruct	instruct;
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
t_instruct				*create_instruct(void);
void					add_to_end_instruct_chain(t_instruct **begin_chain, t_instruct *elem);
t_process				*create_process(void);
t_process   			**create_all_process(int nbr_players);
/*
**	UTILS
*/
void					*ft_malloc(size_t size);
void					print_instruct_type(t_instruct *instruct);

#endif
