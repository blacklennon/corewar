/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcarles <pcarles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:43:01 by zaz               #+#    #+#             */
/*   Updated: 2019/01/23 17:22:24 by pcarles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

/*
{"op_name (char*)", "nb parametres (int)", {"parametres (enum de t_arg_type)"}, "op_code (int)", cycles (int), "description (char*)", "ocp", 0}


encoding ocp:
T_REG	r				01
T_DIR	%				10
T_IND	[number|label]	11

operation encoding: 

[op_code] [ocp] [parameters]
*/

t_op	g_op_tab[17] =
{
	{"live",	1, {T_DIR},													1,	10,		"alive",								0, 0, TOKEN_OP_LIVE},
	{"ld",		2, {T_DIR | T_IND, T_REG},									2,	5,		"load",									1, 0, TOKEN_OP_LD},
	{"st",		2, {T_REG, T_IND | T_REG},									3,	5,		"store",								1, 0, TOKEN_OP_ST},
	{"add",		3, {T_REG, T_REG, T_REG},									4,	10,		"addition",								1, 0, TOKEN_OP_ADD},
	{"sub",		3, {T_REG, T_REG, T_REG},									5,	10,		"soustraction",							1, 0, TOKEN_OP_SUB},
	{"and",		3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG},	6,	6,		"et (and r1, r2, r3 | r1 & r2 -> r3)",	1, 0, TOKEN_OP_AND},
	{"or",		3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG},	7,	6,		"ou (or r1, r2, r3 | r1 | r2 -> r3)",	1, 0, TOKEN_OP_OR},
	{"xor",		3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG},	8,	6,		"ou (xor r1, r2, r3 | r1 ^ r2 -> r3)",	1, 0, TOKEN_OP_XOR},
	{"zjmp",	1, {T_DIR},													9,	20,		"jump if zero",							0, 1, TOKEN_OP_ZJMP},
	{"ldi",		3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 			10,	25,		"load index",							1, 1, TOKEN_OP_LDI},
	{"sti",		3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 			11,	25,		"store index",							1, 1, TOKEN_OP_STI},
	{"fork",	1, {T_DIR},													12,	800,	"fork",									0, 1, TOKEN_OP_FORK},
	{"lld",		2, {T_DIR | T_IND, T_REG},									13,	10,		"long load",							1, 0, TOKEN_OP_LLD},
	{"lldi",	3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG},			14,	50,		"long load index",						1, 1, TOKEN_OP_LLDI},
	{"lfork",	1, {T_DIR},													15,	1000,	"long fork",							0, 1, TOKEN_OP_LFORK},
	{"aff",		1, {T_REG},													16,	2,		"display text message",					1, 0, TOKEN_OP_AFF},
	{0, 0, {0}, 0, 0, 0, 0, 0, TOKEN_MISC_UNDEFINED}
};