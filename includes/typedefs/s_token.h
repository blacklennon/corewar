/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_token.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcarles <pcarles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 14:47:54 by pcarles           #+#    #+#             */
/*   Updated: 2019/01/23 17:16:39 by pcarles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef S_TOKEN_H
# define S_TOKEN_H

# include <stdint.h>

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

#endif