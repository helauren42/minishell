/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helauren <helauren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 14:04:35 by ttaneski          #+#    #+#             */
/*   Updated: 2023/11/07 14:39:03 by helauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	eliminate_var(int found, char ***dict)
{
	dict[found][0][0] = 0;
	if (dict[found][1] != NULL)
		dict[found][1][0] = 0;
}

int	count_words(char *s)
{
	int	i;
	int	boool;
	int	count;

	i = 0;
	if (s == NULL || s[i] == 0)
		return (0);
	boool = 0;
	count = 1;
	while (s[i])
	{
		if (s[i] == ' ')
			boool = 1;
		if (boool == 1 && s[i] != ' ')
		{
			boool = 0;
			count++;
		}
		i++;
	}
	return (count);
}

char	*extract_word(char *all)
{
	int		i;
	int		j;
	char	*word;

	i = 0;
	j = 0;
	if (all[i] == '\"' && all[i] != '\'')
		i++;
	while (all[i + j] && all[i + j] != ' ' && all[i + j] != '\"' 
		&& all[i + j] != '\'')
		j++;
	word = malloc(sizeof(char) * (j + 1));
	j = 0;
	while (all[i + j] && all[i + j] != ' ' && all[i + j] != '\"' 
		&& all[i + j] != '\'')
	{
		word[j] = all[i + j];
		j++;
	}
	word[j] = 0;
	return (word);
}

char	*next_word(char *all)
{
	int		i;
	char	*ret;

	i = 0;
	while (all[i] == ' ')
		i++;
	while (all[i] && all[i] != ' ')
		i++;
	if (all[i] == ' ')
	{
		while (all[i] == ' ')
			i++;
	}
	ret = &all[i];
	return (ret);
}
