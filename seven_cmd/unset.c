/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helauren <helauren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 19:59:49 by helauren          #+#    #+#             */
/*   Updated: 2023/11/07 20:53:56 by helauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**parse_unset_var(char *all, t_data *data)
{
	char	**ret;
	int		w;

	w = 0;
	data->words = count_words(all);
	ret = malloc(sizeof(char *) * (data->words + 1));
	if (ret == NULL)
	{
		write_error("malloc parse unset var failed\n");
		return (NULL);
	}
	while (w < data->words)
	{
		ret[w] = extract_word(all);
		all = next_word(all);
		if (all[0] == 0)
		{
			ret[w + 1] = NULL;
			return (ret);
		}
		w++;
	}
	ret[w] = NULL;
	return (ret);
}

int	valid_name_var(char *s)
{
	int	i;

	if (ft_isalpha(s[0]) == 0 || ft_strlen(s) < 1)
		return (1);
	i = 1;
	while (s[i])
	{
		if (s[i] == '=' && (i == 0 || (i > 0 && s[i - 1] == ' ')))
			return (1);
		if (s[i] == '&' || s[i] == '!' || s[i] == '(' || s[i] == ')'
			|| s[i] == '#' || s[i] == '`' || s[i] == '@' || s[i] == ' '
			|| s[i] == '$' || s[i] == '*' || s[i] == '^' || s[i] == '%')
			return (1);
		i++;
	}
	return (0);
}

char	**unset_var(char *read, t_data *data)
{
	int		i;
	char	*all;
	char	**var;

	i = 6;
	while (read[i] == ' ')
		i++;
	all = ft_strdup(&read[i]);
	var = parse_unset_var(all, data);
	free(all);
	return (var);
}

int	find_exp_var(char *var, char ***dict)
{
	int	i;
	int	cmp;

	i = 0;
	if (dict == NULL)
		return (-1);
	while (dict[i])
	{
		cmp = ft_strcmp(dict[i][0], var);
		if (cmp == 0)
			return (i);
		i++;
	}
	i = 0;
	while (dict[i])
	{
		if (dict[i][1] != NULL && dict[i][1][0] != 0)
			cmp = ft_strcmp(dict[i][1], var);
		if (cmp == 0)
			return (i);
		i++;
	}
	return (-1);
}

int	exec_unset(char *read, t_data *data)
{
	char	**var;
	int		found;
	int		i;

	i = 0;
	var = unset_var(read, data);
	if (var == NULL)
		return (1);
	while (i < data->words)
	{
		found = find_exp_var(var[i], data->exp_var);
		if (found != -1)
			eliminate_var(found, data->exp_var);
		else if (valid_name_var(var[i]) == 1)
		{
			printf("unset: %s: invalid parameter name\n", var[i]);
			free_double_str(&var[i]);
			return (1);
		}
		free(var[i]);
		i++;
	}
	free(var);
	return (1);
}
