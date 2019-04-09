/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llopez <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 15:23:56 by llopez            #+#    #+#             */
/*   Updated: 2019/04/09 18:29:04 by llopez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include "../../lib/libft/includes/libft.h"
#include "../../includes/op.h"
#include "../../includes/asm.h"

void	delete_comment(char *str)
{
	while (*str)
	{
		if (*str == '#')
		{
			while (*str && *str != '\n')
			{
				*str = ' ';
				str++;
			}
		}
		str++;
	}
}

char	*jump_spaces(char *file)
{
	while (ft_isalnum(*file))
		file++;
	while (ft_isspace(*file))
		file++;
	return (file);
}

int		check_name_comment(char *file)
{
	int		i;
	int		name;
	int		comment;

	i = 0;
	name = 0;
	comment = 0;
	while (file[i])
	{
		if (&file[i] == ft_strstr(&file[i], NAME_CMD_STRING))
		{
			if (name)
			{
				printf("name double declaration\n");
				return (0);
			}
			name = 1;
			if (where_is(ft_strchr(&file[i], '"') + 1, '"') > PROG_NAME_LENGTH)
			{
				printf("name too big (max %d) (have %d)\n", PROG_NAME_LENGTH, \
						where_is(ft_strchr(&file[i], '"') + 1, '"'));
				return (0);
			}
		}
		else if (&file[i] == ft_strstr(&file[i], COMMENT_CMD_STRING))
		{
			if (comment)
			{
				printf("comment double declaration\n");
				return (0);
			}
			comment = 1;
			if (where_is(ft_strchr(&file[i], '"') + 1, '"') > COMMENT_LENGTH)
			{
				printf("comment too big (max %d) (have %d)\n", \
				COMMENT_LENGTH, where_is(ft_strchr(&file[i], '"') + 1, '"'));
				return (0);
			}
		}
		else if (ft_isalnum(file[i]) && !name && !comment)
			return (0);
		while (file[i] != '\n')
			i++;
		i++;
	}
	return (1);
}

char	*ft_strjstr_line(char const *str, char const *search)
{
	int i;
	int b;

	b = 0;
	i = 0;
	if (!search || !str)
		return (NULL);
	while (str && str[i])
	{
		b = 0;
		if (str[i] == '\n')
			break;
		while (str[i + b] && search[b] && search[b] == str[i + b])
			b++;
		if ((size_t)b == ft_strlen(search) && ((!i\
						 || !ft_isalpha(str[i - 1]))\
					 && !ft_isalpha(str[i + b])))
			return ((char *)&str[i]);
		i++;
	}
	return (NULL);
}

int		find_op_line(char *str)
{
	int		i;
	char	*tmp;

	tmp = NULL;
	i = 1;
	while (i < 17)
	{
		tmp = ft_strjstr_line(str, g_op_tab[i].name);
		if (tmp && tmp < ft_strchr(str, '\n'))
			return (i);
		i++;
	}
	return (0);
}

int		check_param(int	i_op_tab, char *file)
{
	int		param;
	char	*max_index;

	max_index = ft_strchr(file, '\n');
	param = 0;
	printf("Checking param for op %s\n", g_op_tab[i_op_tab].name);
	while (file && *file && file < max_index)
	{
		if (*file == 'r' && (!(T_REG & g_op_tab[i_op_tab].params[param]) || (ft_atoi(file+1) > REG_NUMBER || ft_atoi(file+1) < 1)))
		{
			printf("Bad param : Registre\n");
			return (0);
		}
		else if ((ft_isdigit(*file) || (*file == '-' && ft_isdigit(*(file + 1)))) && !(T_IND & g_op_tab[i_op_tab].params[param]))
		{
			printf("Bad param : Indirect (%s) %d\n", file, param);
			return (0);
		}
		else if (*file == DIRECT_CHAR && ((*(file + 1) == '-' && ft_isdigit(*(file + 2))) || ft_isdigit(*(file + 1))) && !(T_DIR & g_op_tab[i_op_tab].params[param]))
		{
			printf("Bad param : Direct\n");
			return (0);
		}
		while (*file && (*file != '\n' || *file != ','))
			file++;
		param++;
	}
	return (1);
}

int		check_all(char *file)
{
	int	line;
	int	i_op_tab;

	i_op_tab = 0;
	line = 0;
	if (ft_strstr(file, COMMENT_CMD_STRING) < ft_strstr(file, \
				NAME_CMD_STRING))
		file = ft_strstr(file, NAME_CMD_STRING);
	else
		file = ft_strstr(file, COMMENT_CMD_STRING);
	file = ft_strchr(&file[where_is(file, '"') + 1], '"') + 1;
	file = jump_spaces(file);
	while (file && find_op_line(file))
	{
		printf("%s\n", g_op_tab[find_op_line(file)].name);
		i_op_tab = find_op_line(file);
		file = jump_spaces(file);
		if (!check_param(i_op_tab, file))
		{
			printf("Bad param at instruction %d\n", line);
			return (0);
		}
		while (*file && *file != '\n')
			file++;
		file++;
		//file = jump_spaces(file);
		line++;
	}
	if ((*file))
		printf("bad op (%s)\n", file);
	return (1);
}

int		check_file(char *file)
{
	int		i;

	i = 0;
	delete_comment(file);
	if (!check_name_comment(file) || !check_all(file))
		return (0);
	return (1);
}
