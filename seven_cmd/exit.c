/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helauren <helauren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 17:43:01 by ttaneski          #+#    #+#             */
/*   Updated: 2023/11/07 21:00:56 by helauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exit_std(char *read, t_data *data)
{
	free(read);
	free_triple_str(data->exp_var);
	free(data->prompt);
	free_split(data->paths);
	reset_text_color();
	if (data->pwd != NULL)
	{
		free(data->pwd);
		data->previous_path = NULL;
	}
	data->pwd = NULL;
	if (data->env_for_execve != NULL)
	{
		free_double_str(data->env_for_execve);
		data->env_for_execve = NULL;
	}
	if (data->previous_path != NULL)
		free(data->previous_path);
	free(data->f_p);
	free(data->exit);
	free(data->t);
	free(data->bs);
	free(data);
}

void	exit_null(char *read, t_data *data)
{
	exit_std(read, data);
	exit(1);
}

void	exit_above_2(char **argv, t_data *data, char *read)
{
	printf("./minishell: exit: too many arguments\n");
	free_split(argv);
	exit_std(read, data);
	exit(1);
}

void	exit_end(t_data *data, char *read, char **argv)
{
	data->set_read = NULL;
	free_split(argv);
	exit_std(read, data);
	exit(0);
}

void	cmd_exit(char *read, t_data *data)
{
	int	i;

	i = 0;
	data->exit->argc = 0;
	data->exit->argv = ft_split(read, ' ');
	if (data->exit->argv == NULL)
		exit_null(read, data);
	while (data->exit->argv[i++])
		data->exit->argc++;
	if (data->exit->argc > 2)
		exit_above_2(data->exit->argv, data, read);
	if (data->exit->argc == 2)
	{
		if (is_all_num(data->exit->argv[1]) == 1)
		{
			printf("%s: numeric argument required\n", data->exit->argv[1]);
			free_split(data->exit->argv);
			exit(2);
		}
		i = ft_atoi(data->exit->argv[1]);
		free_split(data->exit->argv);
		exit_std(read, data);
		exit(i);
	}
	exit_end(data, read, data->exit->argv);
}
