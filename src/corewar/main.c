/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcarles <pcarles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 14:38:49 by pcarles           #+#    #+#             */
/*   Updated: 2019/03/22 20:36:26 by pcarles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include <stdlib.h>
#include "corewar.h"

static void	parse_flags(int ac, char **av, t_vm *vm)
{
	int		i;

	i = 1;
	while (i <= MAX_PLAYERS && i < ac)
	{
		vm->process[i - 1].file_path = av[i];
		vm->nb_champs = i++;
	}
}

int			main(int ac, char **av)
{
	t_vm	vm;
	//t_process	*tmp;

	if (ac < 1)
		return (EXIT_FAILURE);
	init_vm(&vm);
	parse_flags(ac, av, &vm);
	load_champs(&vm);
	launch(&vm);
	reg_dump(vm.process);
	mem_dump(vm.memory, MEM_SIZE, 0);
	// tmp = vm.forked_process;
	// while (tmp != NULL)
	// {
	// 	printf("Forked process: %s\n", tmp->name);
	// 	tmp = tmp->next;
	// }
	free_process(vm.forked_process);
	return (EXIT_SUCCESS);
}