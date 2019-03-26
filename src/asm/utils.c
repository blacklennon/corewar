/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llopez <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 14:22:03 by llopez            #+#    #+#             */
/*   Updated: 2019/03/25 23:30:38 by llopez           ###   ########.fr       */
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
	return ((str[i] == c) ? i : -1);
}


char		*get_header(char **data, char *cmd_string)
{
	int	i;
	char	*line;

	i = 0;
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

uint32_t		get_prog_size(char **data)
{
	uint32_t	size;
	int		i;
	int		b;

	i = 0;
	size = 0;
	while (data[i])
	{
		b = 1;
		while (b < 17)
		{
			if (ft_strstr(op_tab[b].name, data[i]))
				size += (op_tab[b].little_dir) ? 2 : 4;
			b++;
		}
		i++;
	}
	size *= 4;
	printf("program size = %u\n", size);
	return (size);
}

int		write_header(int fd, char **data, char *cmd_str, int size)
{
	char	*champ_header;
	uint8_t	zero;

	zero = 0x0;
	champ_header = get_header(data, cmd_str);
	if (!champ_header)
		return (0);
	if (ft_strlen(champ_header)\
		&& !write(fd, champ_header, ft_strlen(champ_header)))
	{
		printf("ERROR: (%s)\n", cmd_str);
		return (0);
	}
	size -= ft_strlen(champ_header)-2;
	while (size >= 0)
	{
		if (!write(fd, &zero, 1))
		{
			printf("ERROR: can't write 0x0 to fill cmd %s\n", cmd_str);
			return (0);
		}
		size--;
	}
	free(champ_header);
	return (1);
}

uint8_t		*add_byte(uint8_t content, t_binary *bin)
{
	size_t	i;
	uint8_t	*tmp;

	i = 0;
	tmp = (uint8_t *)malloc(sizeof(uint8_t) * (bin->size + 1));
	while (i < bin->size && bin->table)
	{
		tmp[i] = bin->table[i];
		i++;
	}
	bin->size++;
	tmp[i] = content;
	free(bin->table);
	return (tmp);
}

uint8_t		*add_param(char	*str, int i_op_tab, t_binary *bin)
{
	int	i;
	char	*clean;
	char	**param;
	char	*tmp;

	i = 0;
	str = ft_strstr(str, op_tab[i_op_tab].name);
	str += ft_strlen(op_tab[i_op_tab].name) + 1;
	while (*str && (*str == ' ' || *str == '\t'))
		str++;
	clean = ft_strtrim(str);
	param = ft_strsplit(str, ',');
	free(clean);
	while (param[i])
	{
		tmp = ft_strtrim(param[i]);
		free(param[i]);
		param[i] = tmp;
		i++;
	}
	if (i > op_tab[i_op_tab])
	{
		printf("Too many arguments.\n");
		return (bin->table);
	}
	i = 0;
	while (param[i])
	{
		if (param[i][0] == DIRECT_CHAR)
		{
			bin->table = add_byte(, bin);
			bin->table = add_byte(, bin);
			bin->table = add_byte(, bin);
			bin->table = add_byte(, bin);
			bin->table = add_byte(, bin);
		}
		i++;
	}
	i = 0;
	while (param[i])
		free(param[i++]);
	free(param);
	return (bin->table);
}

int		print_binary(int fd, t_binary *bin)
{
	return (write(fd, bin->table, bin->size));
}

t_binary	*interpret(char **data)
{
	int		i;
	int		j;
	t_binary	*table;

	table = (t_binary *)malloc(sizeof(t_binary));
	table->size = 0;
	table->table = NULL;
	i = 0;
	while (data[i])
	{
		j = 1;
		while (j < 17)
		{
			if (ft_strstr(data[i], op_tab[j].name))
			{
				table->table = add_byte(op_tab[j].code, table);
				table->table = add_param(data[i], j, table);
			}
			j++;
		}
		i++;
	}
	return (table);
}
