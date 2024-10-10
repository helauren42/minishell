/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helauren <helauren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 13:23:04 by ttaneski          #+#    #+#             */
/*   Updated: 2023/11/07 19:29:37 by helauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_split(char **words)
{
	int	i;

	i = 0;
	if (words == NULL)
		return ;
	while (words[i] != NULL)
	{
		free(words[i]);
		i++;
	}
	free(words);
}

void	free_the_rest(t_data *data)
{
	free(data->previous_path);
	free(data->f_p);
	free(data->exit);
	free(data->t);
	free(data->bs);
	free(data);
}

void	free_env_var(t_data *data)
{
	int	i;

	i = 0;
	while (data->env_var[i] != NULL)
	{
		free(data->env_var[i]);
		i++;
	}
	free(data->env_var);
}

void	free_env_value(t_data *data)
{
	int	i;

	i = 0;
	while (data->env_value[i] != NULL)
	{
		free(data->env_value[i]);
		i++;
	}
	free(data->env_value);
}

void	free_data(t_data *data)
{
	if (data->env_var != NULL)
		free_env_var(data);
	if (data->env_value != NULL)
		free_env_value(data);
	free_the_rest(data);
}
