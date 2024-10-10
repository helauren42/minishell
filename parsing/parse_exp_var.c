/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_exp_var.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helauren <helauren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 12:26:14 by helauren          #+#    #+#             */
/*   Updated: 2023/11/07 19:47:13 by helauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	process_env_value(t_data *data, char **env)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (env[i] != NULL)
		i++;
	data->env_value = (char **)malloc((i + 1) * sizeof(char *));
	if (data->env_value == NULL)
	{
		perror("no memory for u friend");
		exit(1);
	}
	while (j < i)
	{
		data->env_value[j] = find_value(env[j]);
		j++;
	}
	data->env_value[j] = NULL;
}

void	process_env_variables(t_data *data, char **env)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (env[i] != NULL)
		i++;
	data->env_var = (char **)malloc((i + 1) * sizeof(char *));
	if (data->env_var == NULL)
	{
		perror("no memory for env_var");
		exit(1);
	}
	while (j < i)
	{
		data->env_var[j] = find_var(env[j]);
		j++;
	}
	data->env_var[j] = NULL;
}

void	parse_into_exp_var(t_data *data, char **env)
{
	int	i;

	process_env_variables(data, env);
	process_env_value(data, env);
	i = 0;
	while (data->env_var[i])
		i++;
	data->exp_var = malloc(sizeof(char **) * (i + 1));
	i = 0;
	while (data->env_var[i])
	{
		data->exp_var[i] = malloc(sizeof(char *) * 4);
		data->exp_var[i][0] = data->env_var[i];
		data->exp_var[i][1] = data->env_value[i];
		data->exp_var[i][2] = ft_strdup("env");
		data->exp_var[i][3] = NULL;
		i++;
	}
	free(data->env_value);
	free(data->env_var);
	data->exp_var[i] = NULL;
}
