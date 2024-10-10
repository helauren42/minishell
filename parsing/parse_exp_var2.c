/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_exp_var2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helauren <helauren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 15:21:47 by helauren          #+#    #+#             */
/*   Updated: 2023/11/05 19:03:44 by helauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*init_this_ret(char *read, int *i)
{
	int		j;
	char	*ret;

	j = 0;
	while (read[*i] == ' ')
		(*i)++;
	while (read[*i + j] != ' ' && read[*i + j] != '\n' && read[*i + j]
		&& read[*i + j] != '=')
		j++;
	if (read[*i + j] != '=' && read[*i + j - 1] == ' ')
	{
		find_var_error(read);
		return (NULL);
	}
	ret = malloc(sizeof(char) * j + 1);
	return (ret);
}

char	*find_var(char *read)
{
	int		i;
	int		j;
	char	*ret;

	i = 0;
	j = 0;
	ret = init_this_ret(read, &i);
	if (ret == NULL)
		return (NULL);
	while (read[i + j] != '=')
	{
		ret[j] = read[i + j];
		j++;
	}
	ret[j] = 0;
	return (ret);
}

char	*find_value(char *read)
{
	int		i;
	int		j;
	char	*ret;

	i = 0;
	while (read[i] && read[i] != '=')
		i++;
	i++;
	if (read[i] == '\"' || read[i] == '\'')
		i++;
	j = 0;
	while (read[i + j] != '\"' && read[i + j] != '\'' && read[i + j] != '\n'
		&& read[i + j])
		j++;
	ret = malloc(sizeof(char) * j + 1);
	j = 0;
	while (read[i + j] != '\"' && read[i + j] != '\'' && read[i + j] != '\n'
		&& read[i + j])
	{
		ret[j] = read[i + j];
		j++;
	}
	ret[j] = 0;
	return (ret);
}
