/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcarles <pcarles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 16:53:16 by pcarles           #+#    #+#             */
/*   Updated: 2019/03/16 17:55:27 by pcarles          ###   ########.fr       */
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
//	op_tab[LD].func = &op_ld;
//	op_tab[ST].func = &op_st;
	op_tab[ADD].func = &op_add;
	op_tab[SUB].func = &op_sub;
//	op_tab[AND].func = &op_and;
//	op_tab[OR].func = &op_or;
//	op_tab[XOR].func = &op_xor;
	op_tab[ZJMP].func = &op_zjmp;
//	op_tab[LDI].func = &op_ldi;
//	op_tab[STI].func = &op_sti;
//	op_tab[FORK].func = &op_fork;
//	op_tab[LLD].func = &op_lld;
//	op_tab[LLDI].func = &op_lldi;
//	op_tab[LFORK].func = &op_lfork;
	op_tab[AFF].func = &op_aff;
}

static void	init_process(t_process *process)
{
	process->file_path = NULL;
	process->program_counter = 0;
	process->carry = 0;
	process->live_counter = 0;
	process->next_op = 0;
	ft_bzero(process->name, sizeof(process->name));
	ft_bzero(process->comment, sizeof(process->comment));
	ft_bzero(process->registers, sizeof(process->registers));
}

void		init_vm(t_vm *vm)
{
	size_t	i;

	i = 0;
	vm->cycle = 0;
	ft_bzero(vm->memory, sizeof(vm->memory));
	while (i < MAX_PLAYERS)
		init_process(&vm->process[i++]);
	init_opcode(op_tab);
	get_vm(vm);
}

// TODO protect everything
void		load_champs(t_vm *vm)
{
	t_process	*tmp;
	t_header	header;
	int			fd;
	int			i;

	i = 0;
	while (i < MAX_PLAYERS && (tmp = &(vm->process[i++]))->file_path != NULL)
	{
		errno = 0;
		if ((fd = open(tmp->file_path, O_RDONLY)) < 0)
		{
			perror("corewar");
			exit(EXIT_FAILURE);
		}
		read(fd, &header, sizeof(header));
		if (swap_int32(header.magic) != COREWAR_EXEC_MAGIC)
		{
			ft_putstr_fd("corewar: wrong exec format", 2);
			exit(EXIT_FAILURE);
		}
		if ((header.prog_size = swap_int32(header.prog_size)) > CHAMP_MAX_SIZE)
		{
			ft_putstr_fd("corewar: champion too big", 2);
			exit(EXIT_FAILURE);
		}
		read(fd, &vm->memory[(i - 1) * (MEM_SIZE / vm->nb_champs)], header.prog_size);
		tmp->program_counter = (i - 1) * (MEM_SIZE / vm->nb_champs);
		tmp->registers[0] = (int32_t)i;
		ft_strcpy(tmp->name, (char *)&header.prog_name);
		ft_strcpy(tmp->comment, (char *)&header.comment);
		close(fd);
		ft_printf("CHAMP %d\nname: %s\ncomment: %s\n prog_size: %d\n\n", i, tmp->name, tmp->comment, header.prog_size);
	}
}