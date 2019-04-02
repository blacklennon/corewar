/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_00_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcarles <pcarles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 14:38:49 by pcarles           #+#    #+#             */
/*   Updated: 2019/04/02 19:27:04 by pcarles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_printf.h"
#include "corewar.h"

static void	set_nb_champs(t_vm *vm)
{
	int i;
	int res;

	i = 0;
	res = 0;
	while (i < MAX_PLAYERS)
	{
		if (vm->champions[i].file_path != NULL)
			res++;
		i++;
	}
	vm->nb_champs = res;
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
	check_options(ac, av, &vm);
	set_nb_champs(&vm);
	load_champs(&vm);
	vm.verbose= 3;
	if (vm.process == NULL)
		return (EXIT_FAILURE);
	ft_printf("process:%d\n",vm.process->champion->id);
	mem_dump(vm.memory, MEM_SIZE, MEM_SIZE + 1);
	launch(&vm);
	anounce_winner(&vm);
	ft_printf("cycle: %d\n",vm.cycle);
	free_process(vm.process);
	return (EXIT_SUCCESS);
}
