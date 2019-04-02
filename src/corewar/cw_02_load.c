/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_02_load.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcarles <pcarles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 17:49:44 by pcarles           #+#    #+#             */
/*   Updated: 2019/04/02 19:10:54 by pcarles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include "libft.h"
#include "ft_printf.h"
#include "common.h"
#include "op.h"
#include "corewar.h"

static void	new_process(t_vm *vm, int id, t_champion *champion)
{
	t_process	*new_process;

	if ((new_process = (t_process*)malloc(sizeof(t_process))) == NULL)
		crash(NULL, "failed to malloc process :(");
	new_process->carry = 0;
	new_process->next_op = NULL;
	new_process->do_op = 0;
	ft_bzero(new_process->registers, sizeof(new_process->registers));
	new_process->champion = champion;
	new_process->program_counter = (id - 1) * (MEM_SIZE / vm->nb_champs);
	new_process->registers[0] = (int32_t)id;
	new_process->next = vm->process;
	vm->process = new_process;
}

static void	init_champ(t_champion *champion, int id, char *name, char *comment)
{
	champion->id = id;
	ft_strcpy(champion->name, name);
	ft_strcpy(champion->comment, comment);
}

static void	print_champ(t_champion *champion, unsigned int prog_size)
{
	int		id;

	id = champion->id;
	ft_printf(" \e[%dm=== CHAMPION %d ===\e[0m\n     name: %s\n"
		"  comment: %s\nprog_size: %d\n\n", \
		31 + id, id, champion->name, champion->comment, prog_size);
}

void		load_champs(t_vm *vm)
{
	t_champion	*tmp;
	t_header	header;
	int			fd;
	int			i;

	i = 0;
	while (i < MAX_PLAYERS && (tmp = &(vm->champions[i++])))
	{
		if (tmp->file_path == NULL)
			continue ;
		errno = 0;
		if ((fd = open(tmp->file_path, O_RDONLY)) < 0)
			crash(NULL, strerror(errno));
		if (read(fd, &header, sizeof(header)) < 0)
			crash(NULL, strerror(errno));
		if (swap_int32(header.magic) != COREWAR_EXEC_MAGIC)
			crash(NULL, "wrong exec format");
		if ((header.prog_size = swap_int32(header.prog_size)) > CHAMP_MAX_SIZE)
			crash(NULL, "champion too big");
		if (read(fd, &vm->memory[(i - 1) * (MEM_SIZE / vm->nb_champs)], \
			header.prog_size) != (int)header.prog_size)
			crash(NULL, "bad file size");
		new_process(vm, i, tmp);
		init_champ(tmp, i, header.prog_name, header.comment);
		print_champ(tmp, header.prog_size);
		close(fd);
	}
}
