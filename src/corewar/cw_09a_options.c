/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_09a_options.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcarles <pcarles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 22:16:11 by jdouniol          #+#    #+#             */
/*   Updated: 2019/04/03 17:50:29 by pcarles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			ft_stris(char *str, int (*f)(int c))
{
	if (str == NULL || *str == '\0')
		return (0);
	while (*str)
	{
		if (!f((int)*str))
			return (0);
		str++;
	}
	return (1);
}

int			ft_strisnumber(char *str)
{
	if (*str == '-' || *str == '+')
		str++;
	return (ft_stris(str, &ft_isdigit));
}

void		ft_options_usage(char *av, int error)
{
	if (error == ERROR_IS_NOT_A_POSITIVE_INTEGER)
		ft_printf("Please put a positive integer, between 1 and \
			2147483647, not: %s\n", av);
	else if (error == ERROR_IS_NOT_A_VALID_NUMBER)
		ft_printf("Please put a real number not: %s\n", av);
	else if (error == ERROR_IS_NOT_A_VALID_OPTION)
		ft_printf("Please put a valid option (-dump + int or -n + int) \
			not: %s\n", av);
	else if (error == ERROR_IS_NOT_A_VALID_VERBOSE_INT)
		ft_printf("For Verbose (-v) you can only put option 1 (show only live\
			), 2 (show all op), 3 (show all op and values)");
	crash(NULL, NULL);
}

int			set_verbosity(char *av, t_vm *vm)
{
	long	tmp;

	if (ft_strisnumber(av))
	{
		if (ft_strlen(av) < 12)
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
				crash(NULL, NULL);
		}
		else
			ft_options_usage(av, ERROR_IS_NOT_A_VALID_VERBOSE_INT);
	}
	else
		ft_options_usage(av, ERROR_IS_NOT_A_VALID_NUMBER);
	return (1);
}

int			set_player_number(char **av, int ac, int i, t_vm *vm)
{
	long	tmp;

	if (ft_strisnumber(av[i]))
	{
		if (ft_strlen(av[i]) < 12)
		{
			tmp = ft_atol(av[i]);
			if (tmp >= 1 && tmp <= MAX_PLAYERS)
			{
				if (i + 1 >= ac)
					crash(NULL, "missing player after -n option");
				if (vm->champions[tmp - 1].file_path == NULL)
					vm->champions[tmp - 1].file_path = av[i + 1];
				else
				{
					ft_printf("tmp: %d, file_path: %s\n", tmp, vm->champions[tmp - 1].file_path);
					crash(NULL, "player redefinition");
				}
			}
			else
				crash(NULL, NULL);
		}
		else
			ft_options_usage(av[i], ERROR_IS_NOT_A_POSITIVE_INTEGER);
	}
	else
		ft_options_usage(av[i], ERROR_IS_NOT_A_VALID_NUMBER);
	return (2);
}

int			set_cycle_dump(char *av, t_vm *vm)
{
	long	tmp;

	if (ft_strisnumber(av))
	{
		if (ft_strlen(av) < 12)
		{
			tmp = ft_atol(av);
			if (tmp > 0 && tmp <= __LONG_MAX__)
			{
				vm->cycle_limit = (size_t)tmp;
				ft_printf("cycle limit is: %zu\n", vm->cycle_limit);
			}
			else
				crash(NULL, NULL);
		}
		else
			ft_options_usage(av, ERROR_IS_NOT_A_POSITIVE_INTEGER);
	}
	else
		ft_options_usage(av, ERROR_IS_NOT_A_VALID_NUMBER);
	return (1);
}

void		add_player(char *file_path, t_vm *vm)
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
