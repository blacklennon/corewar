/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcarles <pcarles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 17:50:33 by pcarles           #+#    #+#             */
/*   Updated: 2019/03/19 18:31:17 by llopez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

t_op	op_tab[17] =
{
	{NULL, 0, {0}, 0, 0, NULL, 0, 0, NULL},
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
