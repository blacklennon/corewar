/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcarles <pcarles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 17:19:24 by pcarles           #+#    #+#             */
/*   Updated: 2019/03/22 19:59:51 by pcarles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "libft.h"
#include "ft_printf.h"
#include "corewar.h"

void		mem_dump(uint8_t *p, size_t size, size_t octet_highlight)
{
	size_t	i;

	i = 0;
	printf("\n \e[31m=== MEMORY DUMP ===\e[0m\n\n");
	while (i < size)
	{
		if ((i % 64) == 0)
		{
			if (i != 0)
				printf("\n");
			printf("0x%.4zx: ", i);
		}
		if (i == octet_highlight)
			printf("\e[31m%.2x\e[0m ", *p);
		else
			printf("%.2x ", *p);
		p++;
		i++;
	}
	printf("\n");
}

void		reg_dump(t_process *process, size_t nb_process)
{
	size_t	i;
	size_t	j;

	i = 0;
	printf("\n \e[31m=== REGISTERS DUMP ===\e[0m\n");
	while (i < nb_process)
	{
		j = 0;
		printf("\n\e[%lumPlayer %zd (%s)\e[0m\n", 32 + i, i + 1, process[i].name);
		while (j < REG_NUMBER)
		{
			printf("r%-2zd: 0x%x\n", j + 1, process[i].registers[j]);
			j++;
		}
		i++;
	}
}

t_vm		*get_vm(t_vm *new_vm)
{
	static t_vm		*vm;

	if (new_vm != NULL)
		vm = new_vm;
	return (vm);
}

void		free_process(t_process *process_list)
{
	t_process	*tmp;

	while (process_list != NULL)
	{
		tmp = process_list->next;
		free(process_list);
		process_list = tmp;
	}
}

void		crash(t_process *process, char *str)
{
	t_vm	*vm;

	vm = get_vm(NULL);
	printf("\n \e[31m=== CRASH error: %s ===\e[0m\n\nProcess: %s\n", str, process->name);
	reg_dump(process, vm->nb_champs);
	mem_dump(vm->memory, sizeof(vm->memory), process->program_counter);
	free_process(vm->forked_process);
	exit(1);
}

int32_t		swap_int32(int32_t value)
{
	value = ((value << 8) & 0xFF00FF00) | ((value >> 8) & 0xFF00FF);
	return ((value << 16) | ((value >> 16) & 0xFFFF));
}

int16_t		swap_int16(int16_t value)
{
	return ((int16_t)(value << 8) + ((uint16_t)value >> 8));
}