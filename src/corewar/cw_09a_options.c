/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_09a_options.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcarles <pcarles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 22:16:11 by jdouniol          #+#    #+#             */
/*   Updated: 2019/04/12 12:59:27 by pcarles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "corewar.h"

static int	set_verbosity(char *av, t_vm *vm)
{
	long	tmp;

	if (ft_strlen(av) < 12 && ft_strisnumber(av))
	{
		tmp = ft_atol(av);
		if (tmp >= 1 && tmp <= 3)
		{
			if (tmp == 1)
				vm->verbose = 1;
			else if (tmp == 2)
				vm->verbose = 2;
			else
				vm->verbose = 3;
		}
		else
			crash(NULL, "Verbosity level must be between 1 and 3");
	}
	else
		crash(NULL, "Not a valid number");
	return (1);
}

static int	set_player_number(char **av, int ac, int i, t_vm *vm)
{
	long	tmp;

	if (ft_strlen(av[i]) < 12 && ft_strisnumber(av[i]))
	{
		tmp = ft_atol(av[i]);
		if (tmp >= 1 && tmp <= MAX_PLAYERS)
		{
			if (i + 1 >= ac)
				crash(NULL, "Missing player after -n option");
			if (vm->champions[tmp - 1].file_path == NULL)
				vm->champions[tmp - 1].file_path = av[i + 1];
			else
				crash(NULL, "Player redefinition");
		}
		else
			crash(NULL, "Player number must be between 1 and 4");
	}
	else
		crash(NULL, "Not a valid number");
	return (2);
}

static int	set_cycle_dump(char *av, t_vm *vm)
{
	long	tmp;

	if (ft_strlen(av) < 12 && ft_strisnumber(av))
	{
		tmp = ft_atol(av);
		if (tmp > 0 && tmp <= __LONG_MAX__)
			vm->cycle_limit = (size_t)tmp;
		else
			crash(NULL, "Dump cycle too big");
	}
	else
		crash(NULL, "Not a valid number");
	return (1);
}

void		parse_arguments(int ac, char **av, t_vm *vm)
{
	int		i;

	i = 0;
	while (++i < ac - 1)
	{
		if (*av[i] == '-' && ft_strlen(av[i]) == 2)
		{
			av[i]++;
			if (*av[i] == 'd')
				i += set_cycle_dump(av[i + 1], vm);
			else if (*av[i] == 'v')
				i += set_verbosity(av[i + 1], vm);
			else if (*av[i] == 'n')
				i += set_player_number(av, ac, i + 1, vm);
			else
				crash(NULL, NULL);
		}
		else
			break ;
	}
	while (i < ac)
	{
		try_add_player(av[i], vm);
		i++;
	}
}
