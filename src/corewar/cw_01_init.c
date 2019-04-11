/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_01_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcarles <pcarles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 16:53:16 by pcarles           #+#    #+#             */
/*   Updated: 2019/04/11 22:57:51 by pcarles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "corewar.h"
#include "op.h"

static void	init_opcode(t_op *op_tab)
{
	op_tab[LIVE].func = &op_live;
	op_tab[LD].func = &op_ld;
	op_tab[ST].func = &op_st;
	op_tab[ADD].func = &op_add;
	op_tab[SUB].func = &op_sub;
	op_tab[AND].func = &op_and;
	op_tab[OR].func = &op_or;
	op_tab[XOR].func = &op_xor;
	op_tab[ZJMP].func = &op_zjmp;
	op_tab[LDI].func = &op_ldi;
	op_tab[STI].func = &op_sti;
	op_tab[FORK].func = &op_fork;
	op_tab[LLD].func = &op_lld;
	op_tab[LLDI].func = &op_lldi;
	op_tab[LFORK].func = &op_lfork;
	op_tab[AFF].func = &op_aff;
}

static void	init_champion(t_champion *champion)
{
	champion->file_path = NULL;
	ft_bzero(champion->name, sizeof(champion->name));
	ft_bzero(champion->comment, sizeof(champion->comment));
}

void		init_vm(t_vm *vm)
{
	size_t	i;

	i = 0;
	vm->cycle = 0;
	vm->cycle_to_check = CYCLE_TO_DIE;
	vm->size_cycle = CYCLE_TO_DIE;
	vm->last_alive = NULL;
	vm->process = NULL;
	vm->nb_check = 0;
	vm->cycle_limit = 0;
	vm->verbose = 0;
	ft_bzero(vm->memory, sizeof(vm->memory));
	while (i < MAX_PLAYERS)
		init_champion(&vm->champions[i++]);
	init_opcode(g_op_tab);
	get_vm(vm);
}
