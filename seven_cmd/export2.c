/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttaneski <ttaneski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 14:47:14 by ttaneski          #+#    #+#             */
/*   Updated: 2023/10/31 14:47:14 by ttaneski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	***only_var(char *variable, char ***dict)
{
	int		i;
	char	***new;

	i = 0;
	while (dict[i])
		i++;
	new = malloc(sizeof(char **) * (i + 2));
	i = 0;
	while (dict[i])
	{
		new[i] = dict[i];
		i++;
	}
	new[i] = malloc(sizeof(char *) * 3);
	new[i][0] = variable;
	new[i][1] = ft_strdup("\0");
	new[i][2] = NULL;
	new[i + 1] = NULL;
	free(dict);
	return (new);
}

char	***ft_join_var(char ***s, char *variable, char *value)
{
	int		i;
	char	***ret;

	i = 0;
	while (s != NULL && s[i])
		i++;
	ret = malloc(sizeof(char **) * (i + 2));
	if (ret == NULL)
		return (NULL);
	i = 0;
	while (s != NULL && s[i])
	{
		ret[i] = s[i];
		i++;
	}
	ret[i] = malloc(sizeof(char *) * 3);
	ret[i][0] = variable;
	ret[i][1] = value;
	ret[i][2] = NULL;
	ret[i + 1] = NULL;
	free(s);
	return (ret);
}

char	*find_var6(char *read)
{
	int		i;
	int		j;
	char	*ret;

	i = 0;
	j = 0;
	while (read[6 + i] == ' ')
		i++;
	while (read[6 + i + j] && read[6 + i + j] != ' ' && read[6 + i + j] != '=')
		j++;
	ret = malloc(sizeof(char) * j + 1);
	j = 0;
	while (read[6 + i + j] && read[6 + i + j] != '=')
	{
		ret[j] = read[6 + i + j];
		j++;
	}
	ret[j] = 0;
	if (valid_name_var(ret) == 1)
	{
		printf("./minishell: export: `%s': not a valid identifier\n", ret);
		free(ret);
		return (NULL);
	}
	return (ret);
}

char	*find_value6(char *read)
{
	int		i;
	int		j;
	char	*ret;

	i = 0;
	while (read[i] && read[i] != '=')
		i++;
	if (read[i] == 0)
		return (NULL);
	i++;
	if (read[i] == '\"' || read[i] == '\'')
		i++;
	j = 0;
	while (read[i + j] != '\"' && read[i + j] != '\'' && read[i + j])
		j++;
	ret = malloc(sizeof(char) * j + 1);
	j = 0;
	while (read[i + j] != '\"' && read[i + j] != '\'' && read[i + j])
	{
		ret[j] = read[i + j];
		j++;
	}
	ret[j] = 0;
	return (ret);
}

char	***replace_var(t_data *data, char *value, int i)
{
	free(data->exp_var[i][1]);
	data->exp_var[i][1] = value;
	return (data->exp_var);
}
