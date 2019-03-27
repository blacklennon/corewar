/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdouniol <jdouniol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 22:16:11 by jdouniol          #+#    #+#             */
/*   Updated: 2019/03/26 23:09:34 by jdouniol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		ft_options_usage(char *av, int error)
{
	if (error == ERROR_IS_NOT_A_POSITIVE_INTEGER)
		ft_printf("Please put a positive integer, between 1 and \
			2147483647, not :%s\n", av);
	else if (error == ERROR_IS_NOT_A_VALID_NUMBER)
		ft_printf("Please put a real number not :%s\n", av);
	else if (error == ERROR_IS_NOT_A_VALID_OPTION)
		ft_printf("Please put a valid option (-dump + int or -n + int) \
			not :%s\n", av);
}


int			ft_attribute_number(char *av, t_vm *vm)
{
	long long tmp;

	if (ft_str_is_number(av))
	{
		if (ft_strlen(av) < 12)
		{
			tmp = ft_atoll(av);
			if (tmp >= 1 && tmp <= 2147483647)
			{
				//	ft_set_champion_number(ft_atoi(av), vm);
				vm->nb_options += 2;
			}
		}
		else
			ft_options_usage(av, ERROR_IS_NOT_A_POSITIVE_INTEGER);
	}
	else
		ft_options_usage(av, ERROR_IS_NOT_A_VALID_NUMBER);
	return (1);
}


int			ft_cycle_dump(char *av, t_vm *vm)
{
	long long tmp;

	if (ft_str_is_number(av))
	{
		if (ft_strlen(av) < 12)
		{
			tmp = ft_atoll(av);
			if (tmp >= 1 && tmp <= 2147483647)
			{
				vm->cycle_limit = ft_atoi(av);
				ft_printf("cycle limit is : %d\n", vm->cycle_limit);
				vm->nb_options += 2;
			}
		}
		else
			ft_options_usage(av, ERROR_IS_NOT_A_POSITIVE_INTEGER);
	}
	else
		ft_options_usage(av, ERROR_IS_NOT_A_VALID_NUMBER);
	return (1);
}

int			check_options(int ac, char **av, t_vm *vm)
{
	int i;

	i = 0;
	while (++i < ac)
	{
		if (ft_strcmp(av[i], "-dump") == 0)
			i++ && ft_cycle_dump(av[i], vm);
		else if (ft_strcmp(av[i], "-n") == 0)
			i++ && ft_attribute_number(av[i], vm);
		else if (ft_strcmp(av[i], "-v") == 0)
		{
			i++ && ft_verbose(av[i], vm);
		}
		else if (ft_strstr(av[i], ".cor"))
			i++;
		else
		{
			ft_options_usage(av[i], ERROR_IS_NOT_A_VALID_OPTION);
		}
	}
	return (i);
}
