/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdouniol <jdouniol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 14:38:49 by pcarles           #+#    #+#             */
/*   Updated: 2019/03/26 22:55:05 by jdouniol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_printf.h"
#include "corewar.h"

static void	parse_flags(int ac, char **av, t_vm *vm)
{
	int		i;

	i = 1 + vm->nb_options;
	while (i <= (MAX_PLAYERS + vm->nb_options) && i < ac)
	{
		vm->champions[i - 1 - vm->nb_options].file_path = av[i];
		vm->nb_champs = i++ - vm->nb_options;
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
	check_options(ac, av, &vm);
	parse_flags(ac, av, &vm);
	load_champs(&vm);
	if (vm.process == NULL)
		return (EXIT_FAILURE);
	launch(&vm);
	anounce_winner(&vm);
	free_process(vm.process);
	return (EXIT_SUCCESS);
}
