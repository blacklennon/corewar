/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcarles <pcarles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:33:27 by zaz               #+#    #+#             */
/*   Updated: 2019/03/12 14:31:52 by pcarles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Toutes les tailles sont en octets.
** On part du principe qu'un int fait 32 bits. Est-ce vrai chez vous ?
*/

#ifndef OP_H
# define OP_H

# include <stdint.h>

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
	void				(*op_func)(struct s_process*, struct s_vm*);
}						t_op;

t_op		op_tab[17] =
{
	{NULL, 0, {0}, 0, 0, 0, 0, 0, NULL},
	{"live", 1, {T_DIR}, LIVE, 10, "alive", 0, 0, NULL},
	{"ld", 2, {T_DIR | T_IND, T_REG}, LD, 5, "load", 1, 0, NULL},
	{"st", 2, {T_REG, T_IND | T_REG}, ST, 5, "store", 1, 0, NULL},
	{"add", 3, {T_REG, T_REG, T_REG}, ADD, 10, "addition", 1, 0, NULL},
	{"sub", 3, {T_REG, T_REG, T_REG}, SUB, 10, "soustraction", 1, 0, NULL},
	{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, AND, 6, "et (and  r1, r2, r3   r1&r2 -> r3", 1, 0, NULL},
	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, OR, 6, "ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0, NULL},
	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, XOR, 6, "ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0, NULL},
	{"zjmp", 1, {T_DIR}, ZJMP, 20, "jump if zero", 0, 1, NULL},
	{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, LDI, 25, "load index", 1, 1, NULL},
	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, STI, 25, "store index", 1, 1, NULL},
	{"fork", 1, {T_DIR}, FORK, 800, "fork", 0, 1, NULL},
	{"lld", 2, {T_DIR | T_IND, T_REG}, LLD, 10, "long load", 1, 0, NULL},
	{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, LLDI, 50, "long load index", 1, 1, NULL},
	{"lfork", 1, {T_DIR}, LFORK, 1000, "long fork", 0, 1, NULL},
	{"aff", 1, {T_REG}, AFF, 2, "aff", 1, 0, NULL}
};

#endif
