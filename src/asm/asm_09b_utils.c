/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_09b_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdouniol <jdouniol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 14:22:03 by llopez            #+#    #+#             */
/*   Updated: 2019/04/12 15:12:27 by jdouniol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include "libft.h"
#include "common.h"
#include "op.h"
#include "asm.h"

long	ft_latoi(char const *s)
{
	int		flag;
	long	res;

	flag = 0;
	res = 0;
	while ((*s >= 9 && *s <= 13) || *s == ' ')
		s++;
	if (*s == '-' || *s == '+')
	{
		if (*s == '-')
			flag = 1;
		s++;
	}
	while (*s <= '9' && *s >= '0')
	{
		res *= 10;
		res += *s - '0';
		s++;
	}
	if (flag)
		res = -res;
	return (res);
}

uint8_t	*bytes_conv(uint32_t content, uint8_t *table)
{
	(*(uint32_t*)table) = (uint32_t)swap_int32(content);
	return (table);
}

char	*get_new_path(char *path)
{
	char	*newpath;
	int		i;

	i = ft_strlen(path);
	while (path[i] != '.')
		i--;
	if (!ft_strstr(&path[i], ".s"))
		return (NULL);
	newpath = malloc(sizeof(char) * (i + 5));
	ft_strncpy(newpath, path, i);
	newpath[i] = 0;
	ft_strcat(newpath, ".cor");
	return (newpath);
}

int		where_is(char *str, int c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return ((str[i] == c) ? i : -1);
}

char	*get_header(char **data, char *cmd_string)
{
	int		i;
	char	*line;

	i = 0;
	if (!data)
		return (NULL);
	while (data[i] && !ft_strjstr(data[i], cmd_string))
		i++;
	if (data[i] && ft_strjstr(data[i], cmd_string))
	{
		line = ft_strsub(data[i], (uint32_t)where_is(data[i], '"') + 1,\
			(size_t)where_is(&data[i][where_is(data[i], '"') + 1], '"'));
		return (line);
	}
	return (NULL);
}
