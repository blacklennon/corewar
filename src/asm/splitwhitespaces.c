/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitwhitespaces.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llopez <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 14:55:03 by llopez            #+#    #+#             */
/*   Updated: 2019/03/19 18:49:04 by llopez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "../../lib/libft/includes/libft.h"
#include "../../includes/asm.h"

static int	sws_count_words(char *txt)
{
	int	i;
	int	count_words;

	count_words = 0;
	i = -1;
	while (txt[++i])
	{
		if (txt[i] == '"')
			count_words++;
		if (txt[i] == '#' || txt[i] == '"')
			while (txt[i] != '\n')
				i++;
		if (ft_strchr(", \t\n", txt[i]))
			continue;
		count_words++;
		while (!ft_strchr(", \t\n", txt[i + 1]))
			i++;
	}
	return (count_words);
}

char		**split_whitespaces(char *txt)
{
	char	**table;
	int		count_words;
	int		i;
	int		length;

	length = 0;
	i = 0;
	if (!txt)
		return (NULL);
	count_words = sws_count_words(txt);
	table = (char **)malloc(sizeof(char *) * (count_words + 2));
	count_words = 0;
	while (i <= (int)ft_strlen(txt))
	{
		if (txt[i] && txt[i] == '#')
			while (txt[i] && txt[i] != '\n')
				i++;
		if (!txt[i] || ft_strchr(", \t\n", txt[i]))
		{
			if (length)
			{
				table[count_words] = (char *)malloc(sizeof(char) * length + 1);
				ft_strncpy(table[count_words], &txt[i - length], length);
				table[count_words][length] = 0;
				length = 0;
				count_words++;
			}
			i++;
			continue;
		}
		length++;
		i++;
	}
	table[count_words] = NULL;
	return (table);
}
