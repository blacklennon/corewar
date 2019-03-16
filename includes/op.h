/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdouniol <jdouniol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:33:27 by zaz               #+#    #+#             */
/*   Updated: 2019/03/16 17:49:32 by jdouniol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Toutes les tailles sont en octets.
** On part du principe qu'un int fait 32 bits. Est-ce vrai chez vous ?
*/

#ifndef OP_H
# define OP_H

# include <stdint.h>
# include "typedefs/s_process.h"

# define IND_SIZE				2
# define REG_SIZE				4
# define DIR_SIZE				REG_SIZE

/* OCP */
# define REG_CODE				1 //01
# define DIR_CODE				2 //10
# define IND_CODE				3 //11

# define MAX_ARGS_NUMBER		4

# define MAX_PLAYERS			4
# define MEM_SIZE				(4*1024)
# define IDX_MOD				(MEM_SIZE / 8)
# define CHAMP_MAX_SIZE			(MEM_SIZE / 6)

# define COMMENT_CHAR			'#'
# define LABEL_CHAR				':'
# define DIRECT_CHAR			'%'
# define SEPARATOR_CHAR			','

# define LABEL_CHARS			"abcdefghijklmnopqrstuvwxyz_0123456789"

# define NAME_CMD_STRING		".name"
# define NAME_CMD_STR_LENGTH	5
# define COMMENT_CMD_STRING		".comment"
# define COMMENT_CMD_STR_LENGTH	8

# define REG_NUMBER				16

# define CYCLE_TO_DIE			1536
# define CYCLE_DELTA			50
# define NBR_LIVE				21
# define MAX_CHECKS				10

/*
** Type d'argument
*/

typedef char					t_arg_type;

# define T_REG					1
# define T_DIR					2
# define T_IND					4
# define T_LAB					8

/*
**
*/

# define PROG_NAME_LENGTH		(128)
# define COMMENT_LENGTH			(2048)
# define COREWAR_EXEC_MAGIC		0xea83f3

typedef struct			s_header
{
	unsigned int		magic;
	char				prog_name[PROG_NAME_LENGTH + 1];
	unsigned int		prog_size;
	char				comment[COMMENT_LENGTH + 1];
}						t_header;

typedef enum 			e_op_code
{
	LIVE	= 1,
	LD		= 2,
	ST		= 3,
	ADD		= 4,
	SUB		= 5,
	AND		= 6,
	OR		= 7,
	XOR		= 8,
	ZJMP	= 9,
	LDI		= 10,
	STI		= 11,
	FORK	= 12,
	LLD		= 13,
	LLDI	= 14,
	LFORK	= 15,
	AFF		= 16
}						t_op_code;

typedef union			u_int_types
{
	int8_t				u_reg;
	int16_t				u_ind;
	int16_t				u_dir16;
	int32_t				u_dir32;
}						t_int_types;

typedef enum			u_int_types_enum
{
	e_none, e_reg, e_ind, e_dir
}						t_int_types_enum;

typedef	struct 			s_args
{
	t_int_types_enum	type[3];
	t_int_types			value[3];
}						t_args;

typedef struct			s_process
{
	char				*file_path;
	char				name[PROG_NAME_LENGTH + 1];
	char				comment[COMMENT_LENGTH + 1];
	uint16_t			program_counter;
	uint8_t				carry;
	int32_t				registers[REG_NUMBER]; // c est bien ici qu on doit set les valeurs des registres
	size_t				live_counter;
	size_t				next_op;
	struct s_process	*next;
}						t_process;

typedef struct			s_vm
{
	uint8_t				memory[MEM_SIZE];
	size_t				nb_champs;
	struct s_process	process[MAX_PLAYERS];
	size_t				cycle;
}						t_vm;

typedef struct			s_op
{
	char				*name;
	uint8_t				nb_params;
	t_arg_type			params[MAX_ARGS_NUMBER];
	t_op_code			code;
	uint32_t			cycles;
	char				*description;
	uint8_t				ocp; // booleen 1/0 est-ce que je dois lire l'ocp
	uint8_t				little_dir; // boolean 1/0 est-ce que c'est un direct de taille 16/32 bits 2/4 BYTES; 
	void				(*func)(t_process*, t_args*);
}						t_op;

extern t_op				op_tab[17];

#endif
