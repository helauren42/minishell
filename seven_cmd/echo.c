/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttaneski <ttaneski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 12:56:58 by ttaneski          #+#    #+#             */
/*   Updated: 2023/11/07 12:12:08 by ttaneski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_n(char *read)
{
	int	i;

	i = 0;
	if (read[i] != '-')
		return (1);
	i++;
	while (read[i] && read[i] != ' ')
	{
		if (read[i] != 'n')
			return (1);
		i++;
	}
	return (0);
}

char	*concat_strings(char *str1, char *str2)
{
	size_t	len1;
	size_t	len2;
	char	*result;

	len1 = ft_strlen(str1);
	len2 = ft_strlen(str2);
	result = (char *)malloc(len1 + len2 + 2);
	if (result)
	{
		ft_strcpy(result, str1);
		result[len1] = ' ';
		ft_strcpy(result + len1 + 1, str2);
	}
	return (result);
}

char	*split_return(char *read)
{
	int		i;
	char	**words;
	char	*res;
	char	*temp;

	i = 1;
	res = NULL;
	words = ft_split(read, ' ');
	while (words[i])
	{
		if (is_n(words[i]) == 1)
		{
			if (res == NULL)
				res = ft_strdup(words[i]);
			else
			{
				temp = concat_strings(res, words[i]);
				free(res);
				res = temp;
			}
		}
		i++;
	}
	free_split(words);
	return (res);
}

int	find_option(char *read)
{
	int	i;

	i = 4;
	while (read[i] == ' ')
		i++;
	if (read[i] != '-')
		return (0);
	if (read[i] == '-')
	{
		i++;
		if (read[i] != 'n')
			return (0);
		while (read[i] == 'n')
			i++;
		if (read[i] != ' ' && read[i])
			return (0);
		return (1);
	}
	printf("end\n");
	return (0);
}

int	exec_echo(char *read)
{
	char	*split_result;
	int		option;

	option = find_option(read);
	split_result = split_return(read);
	if (split_result != NULL)
	{
		if (option == 0)
		{
			printf("%s\n", split_result);
			free(split_result);
		}
		else
		{
			printf("%s", split_result);
			free(split_result);
		}
	}
	return (1);
}
