/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llopez <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 14:22:03 by llopez            #+#    #+#             */
/*   Updated: 2019/03/31 21:50:26 by llopez           ###   ########.fr       */
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
	while (data[i] && !ft_strstr(data[i], cmd_string))
		i++;
	if (data[i] && ft_strstr(data[i], cmd_string))
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

uint8_t		param_encode(char **param)
{
	int	i;
	uint8_t	content;

	content = 0x0;
	i = 0;
	while (param[i])
	{
		content = content << (i+1);
		printf("reading param |%s|\n", param[i]);
		if (param[i][0] == DIRECT_CHAR)
			content |= DIR_CODE;
		if (ft_isdigit(param[i][0]))
			content |= IND_CODE;
		if (param[i][0] == 'r' && ft_atoi(&param[i][1]) <= REG_NUMBER)
			content |= REG_CODE;
		i++;
	}
	printf("param encode = %x\n", content);
	return (content);
}

uint8_t		*add_data(char **param, t_binary *bin, int i_op_tab)
{
	int	i;
	int	value;

	value = 0;
	(void)i_op_tab;
	i = 0;
	while (param[i])
	{
		if (param[i][0] == DIRECT_CHAR)
		{
			/*if (param[i][1] == LABEL_CHAR)
				bin->table = 
			else*/
			value = ft_atoi(&param[i][1]);
			printf("sent to atoi : %s\n", &param[i][1]);
			printf("value : %d\n", value);
			bin->table = add_byte((value & 0xFF000000) >> 24, bin);
			bin->table = add_byte((value & 0x00FF0000) >> 16, bin);
			bin->table = add_byte((value & 0x0000FF00) >> 8, bin);
			bin->table = add_byte((value & 0x000000FF), bin);
		}
		if (ft_isdigit(param[i][0]))
		{
			value = ft_atoi(param[i]);
			bin->table = add_byte((value & 0xFF00) >> 8, bin);
			bin->table = add_byte((value & 0x00FF), bin);
		}
		if (param[i][0] == 'r' && ft_atoi(&param[i][1]) <= REG_NUMBER)
			bin->table = add_byte((uint8_t)ft_atoi(&param[i][1]), bin);
		i++;
	}
	return (bin->table);
}

uint8_t		*add_param(char	*str, int i_op_tab, t_binary *bin)
{
	int	i;
	char	*clean;
	char	**param;
	char	*tmp;

	i = 0;
	str = ft_strjstr(str, op_tab[i_op_tab].name);
	str += ft_strlen(op_tab[i_op_tab].name) + 1;
	clean = ft_strtrim(str);
	param = ft_strsplit(clean, ',');
	free(clean);
	while (param[i])
	{
		tmp = ft_strtrim(param[i]);
		free(param[i]);
		param[i] = tmp;
		i++;
	}
	if (i-1 > op_tab[i_op_tab].nb_params)
	{
		i = 0;
		while (param[i])
			free(param[i++]);
		return (bin->table);
	}
	if (op_tab[i_op_tab].nb_params > 1)
		bin->table = add_byte((param_encode(param) << \
			(8 - op_tab[i_op_tab].nb_params * 2)), bin);
	bin->table = add_data(param, bin, i_op_tab);
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
			if (ft_strjstr(data[i], op_tab[j].name))
			{
				printf("found op_code %s\n", op_tab[j].name);
				table->table = add_byte(op_tab[j].code, table);
				table->table = add_param(data[i], j, table);
			}
			j++;
		}
		i++;
	}
	return (table);
}

char	*ft_strjstr(char const *str, char const *search)
{
	int i;
	int b;

	b = 0;
	i = 0;
	if (!*search)
		return ((char *)str);
	while (str[i])
	{
		b = 0;
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
