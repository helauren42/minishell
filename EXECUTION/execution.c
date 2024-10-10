/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helauren <helauren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 13:27:19 by helauren          #+#    #+#             */
/*   Updated: 2023/11/08 12:45:27 by helauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_redir	*find_heredoc(t_temp *first)
{
	t_temp	*curr;

	curr = first;
	while (curr != NULL)
	{
		if (curr->sign == 2)
			return ((t_redir *)curr);
		if (curr->sign == 5)
			break ;
		curr = curr->right;
	}
	return (NULL);
}

void	execution_heredoc(t_redir *find_hd, t_temp *curr, t_data *data)
{
	find_hd = find_heredoc(curr);
	if (find_hd != NULL)
	{
		handle_heredoc_input(find_hd, data);
		prepare_hd_pipe(data);
		dup2(data->hd_pipe_fd[0], STDIN_FILENO);
	}
}

int	is_g(t_data *data)
{
	if (data->curr->right->sign == 1 || data->curr->right->sign == 2
		|| data->curr->right->sign == 3 || data->curr->right->sign == 4)
		return (0);
	return (1);
}

void	execution1(t_data *data)
{
	execution_heredoc(NULL, data->curr, data);
	read_file_input((t_redir *)data->curr, data);
	if (ft_strcmp(data->curr->type, "redir") == 0 && data->curr->right)
		data->curr = data->curr->right;
	read_pipe_input((t_redir *)data->curr);
	redirect_output((t_redir *)data->curr);
}

void	execution(t_temp *first, t_data *data)
{
	signal(SIGINT, sigint_child);
	data->env_for_execve = env_execve(data->exp_var);
	data->curr = first;
	while (data->curr != NULL)
	{
		execution1(data);
		if (seven_cmd((t_cmd *)data->curr, data, first) != 1)
		{
			if (data->curr && data->curr->type && ft_strcmp(data->curr->type,
					"redir") != 0)
				fork_out_dat_child(data->curr, data);
		}
		while (data->curr && data->curr->right && (is_g(data)) == 0)
			data->curr = data->curr->right;
		free_hd(data);
		if (data->curr != NULL)
			data->curr = data->curr->right;
	}
	free_double_str(data->env_for_execve);
	data->env_for_execve = NULL;
	dup2(data->og_stdin, STDIN_FILENO);
	dup2(data->og_stdout, STDOUT_FILENO);
}
