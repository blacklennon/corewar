/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llopez <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 14:22:03 by llopez            #+#    #+#             */
/*   Updated: 2019/03/22 14:55:48 by llopez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include "../../lib/libft/includes/libft.h"
#include "../../includes/op.h"
#include "../../includes/asm.h"

int32_t	swap_int32(int32_t value)
{
	value = ((value << 8) & 0xFF00FF00) | ((value >> 8) & 0xFF00FF);
	return ((value << 16) | ((value >> 16) & 0xFFFF));
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
	return (i);
}


char		*get_header(char **data, char *cmd_string)
{
	int	i;
	char	*line;

	i = 0;
	printf("cmd str = %s\n", cmd_string);
	if (!data)
		return (NULL);
	while (data[i] && !ft_strstr(cmd_string, data[i]))
		i++;
	if (data[i] && ft_strstr(cmd_string, data[i]))
	{
		line = ft_strsub(data[i], (uint32_t)where_is(data[i], '"') + 1,\
		(size_t)where_is(&data[i][where_is(data[i], '"') + 1], '"'));
		return (line);
	}
	return (NULL);
}

int		write_header(int fd, char **data, char *cmd_str, int size)
{
	char	*champ_header;
	uint8_t	zero;

	zero = 0x0;
	champ_header = get_header(data, cmd_str);
	printf("\033[41m%s = %s\033[0m\n", cmd_str, champ_header);
	if (!write(fd, champ_header, ft_strlen(champ_header)))
	{
		printf("ERROR\n");
		return (0);
	}
	size -= ft_strlen(champ_header);
	printf("size : %d\n", size);
	while (size >= 0)
	{
		if (!write(fd, &zero, 1))
		{
			printf("ERROR\n");
			return (0);
		}
		size--;
	}
	free(champ_header);
	return (1);
}
