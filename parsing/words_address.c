/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   words_address.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helauren <helauren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 18:25:53 by helauren          #+#    #+#             */
/*   Updated: 2023/11/04 18:23:09 by helauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	redir_word_end(char *read, int i)
{
	if (read[i] == '<')
	{
		i++;
		if (read[i] == '<')
			i++;
		return (i);
	}
	else if (read[i] == '>')
	{
		i++;
		if (read[i] == '>')
			i++;
		return (i);
	}
	else
		return (i + 1);
}

int	word_end(char *read, int i, int *sign)
{
	if (*sign == 1)
	{
		while (read[i] != '\'' && read[i])
			i++;
		i++;
		while (read[i] != '\'' && read[i])
			i++;
	}
	else if (*sign == 2)
	{
		while (read[i] != '\"' && read[i])
			i++;
		i++;
		while (read[i] != '\"' && read[i])
			i++;
	}
	if (*sign == 0 && (read[i] == '<' || read[i] == '>' || read[i] == '|'))
		return (redir_word_end(read, i));
	while (read[i] != ' ' && read[i] && read[i] != '<' && read[i] != '>'
		&& read[i] != '|')
		i++;
	return (i);
}

int	word_start(char *read, int i, int *sign)
{
	int	start;

	while (read[i] && read[i] == ' ')
		i++;
	start = i;
	while (read[i] && read[i] != ' ' && read[i] != '<' && read[i] != '>'
		&& read[i] != '|')
	{
		if (read[i] == '\'')
		{
			*sign = 1;
			return (start);
		}
		if (read[i] == '\"')
		{
			*sign = 2;
			return (start);
		}
		i++;
	}
	return (start);
}

int	**init_words_addr(char *read, int *len)
{
	int	**ret;
	int	i;
	int	malloc_len;

	i = 0;
	malloc_len = ft_strlen(read);
	malloc_len = (malloc_len / 2 + 5);
	ret = malloc(sizeof(int *) * (malloc_len));
	if (!ret)
		return (NULL);
	while (1)
	{
		ret[i] = malloc(sizeof(int) * 2);
		ret[i][0] = -1;
		ret[i][1] = -1;
		*len = i;
		if (i >= (malloc_len) / 2 + 1)
			break ;
		i++;
	}
	return (ret);
}

int	**words_addr(char *read, int *len)
{
	int	i;
	int	**words_addr;
	int	word;
	int	sign;

	words_addr = init_words_addr(read, len);
	output_addr(words_addr);
	word = 0;
	i = 0;
	while (1)
	{
		sign = 0;
		i = word_start(read, i, &sign);
		words_addr[word][0] = i;
		i = word_end(read, i, &sign);
		words_addr[word][1] = i - 1;
		i = find_next_word(read, i);
		if (i == 0 || read[i] == 0)
			break ;
		word++;
	}
	return (words_addr);
}
