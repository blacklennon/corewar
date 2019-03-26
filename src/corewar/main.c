/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcarles <pcarles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 14:38:49 by pcarles           #+#    #+#             */
/*   Updated: 2019/03/26 20:19:54 by pcarles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_printf.h"
#include "corewar.h"

static void	parse_flags(int ac, char **av, t_vm *vm)
{
	int		i;

	i = 1;
	while (i <= MAX_PLAYERS && i < ac)
	{
		vm->champions[i - 1].file_path = av[i];
		vm->nb_champs = i++;
	}
}

static void	anounce_winner(t_vm *vm)
{
	if (vm->last_alive != NULL)
		ft_printf("And the winner is champion %d, %s\n", \
		vm->last_alive->id, vm->last_alive->name);
	else
		ft_printf("Nobody wins\n");
}

int			main(int ac, char **av)
{
	t_vm	vm;

	if (ac < 2)
		return (EXIT_FAILURE);
	init_vm(&vm);
	parse_flags(ac, av, &vm);
	load_champs(&vm);
	if (vm.process == NULL)
		return (EXIT_FAILURE);
	launch(&vm);
	anounce_winner(&vm);
	mem_dump(vm.memory, MEM_SIZE, MEM_SIZE + 1);
	free_process(vm.process);
	return (EXIT_SUCCESS);
}
