/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_00_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdouniol <jdouniol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 14:38:49 by pcarles           #+#    #+#             */
/*   Updated: 2019/04/12 18:33:58 by jdouniol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_printf.h"
#include "common.h"
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
			vm->champions[i].id = ++res;
		else
			break ;
		i++;
	}
	vm->nb_champs = res;
}

static void	anounce_winner(t_vm *vm)
{
	t_champion	*winner;

	winner = vm->last_alive;
	if (winner != NULL)
		ft_printf("\e[%dmAnd the winner is champion %d, %s\e[0m\n",\
		31 + winner->id, winner->id, winner->name);
	else
		ft_printf("Nobody wins\n");
	ft_printf("Game ended at cycle %d\n", vm->cycle);
}

int			main(int ac, char **av)
{
	t_vm	vm;

	if (ac < 2)
	{
		corewar_usage();
		exit(EXIT_FAILURE);
	}
	init_vm(&vm);
	parse_arguments(ac, av, &vm);
	set_nb_champs(&vm);
	if (vm.nb_champs < 1)
		crash(NULL, "Not enough players");
	load_champs(&vm);
	if (vm.process == NULL)
		return (EXIT_FAILURE);
	launch(&vm);
	if (vm.cycle_limit != 0)
		mem_dump(vm.memory, MEM_SIZE, MEM_SIZE + 1);
	else
		anounce_winner(&vm);
	free_process(vm.process);
	return (EXIT_SUCCESS);
}
