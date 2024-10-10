/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helauren <helauren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 18:57:57 by helauren          #+#    #+#             */
/*   Updated: 2023/11/07 13:53:35 by helauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	out_var_declare(char ***dict)
{
	int	i;

	i = 0;
	while (dict[i])
	{
		if (dict[i][0] == NULL || dict[i][0][0] == 0)
		{
			i++;
			continue ;
		}
		if (dict[i][1] == NULL || dict[i][1][0] == 0)
			printf("declare -x %s\n", dict[i][0]);
		else
			printf("declare -x %s=\"%s\"\n", dict[i][0], dict[i][1]);
		i++;
	}
	return (1);
}

void	real_exec_export(char *read, t_data *data)
{
	char	*variable;
	char	*value;
	int		i;

	variable = find_var6(read);
	if (variable == NULL)
		return ;
	value = find_value6(read);
	if (value == NULL)
	{
		data->exp_var = only_var(variable, data->exp_var);
		return ;
	}
	i = find_exp_var(variable, data->exp_var);
	if (i != -1)
	{
		data->exp_var = replace_var(data, value, i);
		free(variable);
		return ;
	}
	data->exp_var = ft_join_var(data->exp_var, variable, value);
}

int	export_no_equal(char *read)
{
	int	i;

	i = 6;
	while (read[i] && read[i] != '\n')
	{
		if (read[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

int	export_only(char *read)
{
	int	i;

	if (ft_strlen(read) < 6)
		return (0);
	i = 6;
	while (read[i] && read[i] != '\n')
	{
		if (read[i] != ' ')
			return (1);
		i++;
	}
	return (0);
}

int	exec_export(char *read, t_cmd *curr, t_data *data)
{
	int	i;

	i = 1;
	if (export_only(read) == 0)
	{
		out_var_declare(data->exp_var);
		return (1);
	}
	while (curr->cmd_options[i])
	{
		read = ft_strjoin_nofree("export", " ");
		read = ft_strjoin(read, curr->cmd_options[i]);
		real_exec_export(read, data);
		free(read);
		i++;
	}
	return (1);
}
