/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcarles <pcarles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:33:27 by zaz               #+#    #+#             */
/*   Updated: 2019/01/22 18:06:00 by pcarles          ###   ########.fr       */
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
# define REG_CODE				1
# define DIR_CODE				2
# define IND_CODE				3

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

typedef enum			e_token_type {
	TOKEN_OP_LIVE,
	TOKEN_OP_LD,
	TOKEN_OP_ST,
	TOKEN_OP_ADD,
	TOKEN_OP_SUB,
	TOKEN_OP_AND,
	TOKEN_OP_OR,
	TOKEN_OP_XOR,
	TOKEN_OP_ZJMP,
	TOKEN_OP_LDI,
	TOKEN_OP_STI,
	TOKEN_OP_FORK,
	TOKEN_OP_LLD,
	TOKEN_OP_LLDI,
	TOKEN_OP_LFORK,
	TOKEN_OP_AFF,
	TOKEN_MISC_LABEL,
	TOKEN_PARAM_REGISTER,
	TOKEN_PARAM_DIRECT,
	TOKEN_PARAM_INDIRECT,
	TOKEN_MISC_SEPARATOR,
	TOKEN_MISC_NAME,
	TOKEN_MISC_COMMENT,
	TOKEN_MISC_EOL,
	TOKEN_MISC_UNDEFINED = 0
}						t_token_type;

typedef struct			s_token
{
	enum e_token_type	type;
	int32_t				value;
	struct s_label		*label;
}						t_token;

typedef struct			s_header
{
	unsigned int		magic;
	char				prog_name[PROG_NAME_LENGTH + 1];
	unsigned int		prog_size;
	char				comment[COMMENT_LENGTH + 1];
}						t_header;

typedef struct			s_op
{
	char				*name;
	int8_t				nb_params;
	t_arg_type			params[MAX_ARGS_NUMBER];
	int8_t				code;
	int					cycles;
	char				*description;
	char				ocp;
	char				j;
	t_token				token;
}						t_op;

#endif
