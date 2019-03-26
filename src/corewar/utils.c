/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcarles <pcarles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 17:19:24 by pcarles           #+#    #+#             */
/*   Updated: 2019/03/26 19:57:14 by pcarles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include "libft.h"
#include "ft_printf.h"
#include "corewar.h"

void		mem_dump(uint8_t *p, size_t size, size_t octet_highlight)
{
	size_t	i;

	i = 0;
	ft_printf("\n \e[31m=== MEMORY DUMP ===\e[0m\n\n");
	while (i < size)
	{
		if ((i % 64) == 0)
		{
			if (i != 0)
				ft_printf("\n");
			ft_printf("0x%.4zx: ", i);
		}
		if (i == octet_highlight)
			ft_printf("\e[31;1m%.2x\e[0m ", *p);
		else
			ft_printf("%.2x ", *p);
		p++;
		i++;
	}
	ft_printf("\n");
}

void		reg_dump(t_process *process)
{
	size_t	i;

	ft_printf("\n \e[31m=== REGISTERS DUMP ===\e[0m\n");
	i = 0;
	ft_printf("\nFor player %s\n", process->champion->name);
	while (i < REG_NUMBER)
	{
		ft_printf("r%-2zd: 0x%x\n", i + 1, process->registers[i]);
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
	if (str == NULL)
		str = "Error";
	if (process != NULL)
	{
		ft_printf("\n \e[31;1m=== CRASH error: %s ===\e[0m\n\n"
		"Champion: %s\nCycle: %zu", \
		str, process->champion->name, get_vm(NULL)->cycle);
		reg_dump(process);
		mem_dump(vm->memory, sizeof(vm->memory), process->program_counter);
	}
	else
		ft_printf("corewar: %s\n", str);
	free_process(vm->process);
	exit(EXIT_FAILURE);
}
