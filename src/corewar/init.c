/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdouniol <jdouniol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 16:53:16 by pcarles           #+#    #+#             */
/*   Updated: 2019/03/16 17:49:01 by jdouniol         ###   ########.fr       */
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

//jac 12032019
static void	init_opcode(t_op *op_tab)
{
	op_tab[LIVE].func = &op_live; //ok
	op_tab[LD].func = &op_ld;
	op_tab[ST].func = &op_st;
	op_tab[ADD].func = &op_add;	//ok
	op_tab[SUB].func = &op_sub; //ok
	op_tab[AND].func = &op_and; //ok
	op_tab[OR].func = &op_or; //ok
	op_tab[XOR].func = &op_xor; //ok
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
	process->file_path = NULL;
	process->program_counter = 0;
	process->carry = 0;
	process->live_counter = 0;
	process->next_op = 0;
	ft_bzero(process->name, sizeof(process->name));
	ft_bzero(process->comment, sizeof(process->comment));
	ft_bzero(process->registers, sizeof(process->registers));
	process->next = NULL;
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
		ft_strcpy(tmp->name, (char *)&header.prog_name);
		ft_strcpy(tmp->comment, (char *)&header.comment);
		close(fd);
		ft_printf("CHAMP %d\nname: %s\ncomment: %s\n prog_size: %d\n\n", i, tmp->name, tmp->comment, header.prog_size);
	}
}