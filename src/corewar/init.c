/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcarles <pcarles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 16:53:16 by pcarles           #+#    #+#             */
/*   Updated: 2019/03/24 22:29:05 by pcarles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "ft_printf.h"
#include "corewar.h"
#include "op.h"

//jac 12032019
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

static void	init_process(t_process *process)
{
	process->carry = 0;
	process->next_op = NULL;
	process->do_op = 0;
	ft_bzero(process->registers, sizeof(process->registers));
}

static void	init_champion(t_champion *champion)
{
	champion->file_path = NULL;
	champion->live_counter = 0;
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
	ft_bzero(vm->memory, sizeof(vm->memory));
	while (i < MAX_PLAYERS)
		init_champion(&vm->champions[i++]);
	init_opcode(g_op_tab);
	get_vm(vm);
}

// TODO protect everything
void		load_champs(t_vm *vm)
{
	t_champion	*tmp_c;
	t_process	*tmp_p;
	t_header	header;
	int			fd;
	int			i;

	i = 0;
	while (i < MAX_PLAYERS && (tmp_c = &(vm->champions[i++]))->file_path != NULL)
	{
		errno = 0;
		if ((fd = open(tmp_c->file_path, O_RDONLY)) < 0)
			crash(NULL, strerror(errno));
		read(fd, &header, sizeof(header));
		if (swap_int32(header.magic) != COREWAR_EXEC_MAGIC)
			crash(NULL, "wrong exec format");
		if ((header.prog_size = swap_int32(header.prog_size)) > CHAMP_MAX_SIZE)
			crash(NULL, "champion too big");
		read(fd, &vm->memory[(i - 1) * (MEM_SIZE / vm->nb_champs)], header.prog_size);
		if ((tmp_p = (t_process*)malloc(sizeof(t_process))) == NULL)
			crash(NULL, "failed to malloc process :(");
		init_process(tmp_p);
		tmp_p->champion = tmp_c;
		tmp_p->program_counter = (i - 1) * (MEM_SIZE / vm->nb_champs);
		tmp_p->registers[0] = (int32_t)i;
		tmp_p->next = vm->process;
		vm->process = tmp_p;
		tmp_c->id = i;
		ft_strcpy(tmp_c->name, (char *)&header.prog_name);
		ft_strcpy(tmp_c->comment, (char *)&header.comment);
		close(fd);
		ft_printf(" \e[%dm=== CHAMP %d ===\e[0m\n     name: %s\n  comment: %s\nprog_size: %d\n\n", 31 + i, i, tmp_c->name, tmp_c->comment, header.prog_size);
	}
}