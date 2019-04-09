/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_09a_options.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcarles <pcarles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 22:16:11 by jdouniol          #+#    #+#             */
/*   Updated: 2019/04/09 10:26:09 by pcarles          ###   ########.fr       */
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
			crash(NULL, "verbosity level must be between 1 and 3");
	}
	else
		crash(NULL, "not a valid number");
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
				crash(NULL, "missing player after -n option");
			if (vm->champions[tmp - 1].file_path == NULL)
				vm->champions[tmp - 1].file_path = av[i + 1];
			else
				crash(NULL, "player redefinition");
		}
		else
			crash(NULL, "player number must be between 1 and 4");
	}
	else
		crash(NULL, "not a valid number");
	return (2);
}

static int	set_cycle_dump(char *av, t_vm *vm)
{
	long	tmp;

	if (ft_strlen(av) < 12 && ft_strisnumber(av))
	{
		tmp = ft_atol(av);
		if (tmp > 0 && tmp <= __LONG_MAX__)
		{
			vm->cycle_limit = (size_t)tmp;
			ft_printf("cycle limit is: %zu\n", vm->cycle_limit);
		}
		else
			crash(NULL, "dumple cycle too big");
	}
	else
		crash(NULL, "not a valid number");
	return (1);
}

static void	add_player(char *file_path, t_vm *vm)
{
	int		i;

	i = 0;
	while (i < MAX_ARGS_NUMBER)
	{
		if (vm->champions[i].file_path == NULL)
		{
			vm->champions[i].file_path = file_path;
			return ;
		}
		i++;
	}
	crash(NULL, "too many players");
}

void		parse_arguments(int ac, char **av, t_vm *vm)
{
	int		i;

	i = 0;
	while (++i < ac - 1)
	{
		if (*(av[i])++ == '-' && ft_strlen(av[i]) == 1)
		{
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
		if (ft_strstr(av[i], ".cor") != NULL)
			add_player(av[i], vm);
		else
			crash(NULL, NULL);
		i++;
	}
}
