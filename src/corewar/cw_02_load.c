/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_02_load.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcarles <pcarles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 17:49:44 by pcarles           #+#    #+#             */
/*   Updated: 2019/04/12 14:59:54 by pcarles          ###   ########.fr       */
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
		crash(NULL, "Failed to malloc process :(");
	new_process->carry = 0;
	new_process->next_op = NULL;
	new_process->do_op = 0;
	ft_bzero(new_process->registers, sizeof(new_process->registers));
	new_process->champion = champion;
	new_process->live_counter = 0;
	new_process->program_counter = (id - 1) * (MEM_SIZE / vm->nb_champs);
	new_process->registers[0] = (int32_t)id;
	new_process->next = vm->process;
	vm->process = new_process;
}

static void	init_champ(t_champion *champion, t_header *header, int fd)
{
	int id;

	ft_strcpy(champion->name, header->prog_name);
	ft_strcpy(champion->comment, header->comment);
	id = champion->id;
	ft_printf(" \e[%dm=== CHAMPION %d ===\e[0m\n     name: %s\n"
		"  comment: %s\nprog_size: %d\n\n", \
		31 + id, id, champion->name, champion->comment, header->prog_size);
	close(fd);
}

void		load_champs(t_vm *vm)
{
	t_champion	*tmp;
	t_header	header;
	int			fd;
	int			i;

	i = 0;
	while (i < MAX_PLAYERS && (tmp = &(vm->champions[i++]))->file_path != NULL)
	{
		if (tmp->file_path == NULL)
			continue ;
		errno = 0;
		if ((fd = open(tmp->file_path, O_RDONLY)) < 0)
			crash(NULL, strerror(errno));
		if (read(fd, &header, sizeof(header)) < 0)
			crash(NULL, strerror(errno));
		if (swap_int32(header.magic) != COREWAR_EXEC_MAGIC)
			crash(NULL, "Wrong exec format");
		if ((header.prog_size = swap_int32(header.prog_size)) > CHAMP_MAX_SIZE)
			crash(NULL, "Champion too big");
		if (read(fd, &vm->memory[(tmp->id - 1) * (MEM_SIZE / vm->nb_champs)], \
			header.prog_size) != (int)header.prog_size)
			crash(NULL, "Bad file size");
		new_process(vm, tmp->id, tmp);
		init_champ(tmp, &header, fd);
	}
}
