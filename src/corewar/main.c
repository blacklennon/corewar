/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcarles <pcarles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 14:38:49 by pcarles           #+#    #+#             */
/*   Updated: 2019/02/26 20:03:55 by pcarles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

	if (ac < 1)
		return (EXIT_FAILURE);
	init_vm(&vm);
	parse_flags(ac, av, &vm);
	load_champs(&vm);
	mem_dump(vm.memory, MEM_SIZE);
	return (EXIT_SUCCESS);
}