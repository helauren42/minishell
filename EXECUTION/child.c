/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: ttaneski <ttaneski@student.42.fr>          +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2023/10/31 14:34:04 by ttaneski          #+#    #+#             */
/*   Updated: 2023/10/31 14:34:04 by ttaneski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	child_exec(t_temp *curr, t_data *data)
{
	int		error;
	t_cmd	*cmd_type;
	t_exec	*exec_type;

	if (ft_strcmp(curr->type, "cmd") == 0)
	{
		cmd_type = (t_cmd *)curr;
		error = execve(cmd_type->cmd_path, cmd_type->cmd_options,
				data->env_for_execve);
	}
	if (ft_strcmp(curr->type, "exec") == 0)
	{
		exec_type = (t_exec *)curr;
		error = execve(exec_type->path, exec_type->options,
				data->env_for_execve);
	}
	if (error == -1)
		perror("failed to execute");
}

void	post_forkination(t_temp *curr, t_data *data, t_redir *redir, int status)
{
	if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
	else if (g_exit_status == 130)
		g_exit_status = 130;
	else
		g_exit_status = 0;
	if (curr->right != NULL && (curr->right->sign == 4
			|| curr->right->sign == 3))
	{
		dup2(data->og_stdout, STDOUT_FILENO);
		dup2(data->og_stdin, STDIN_FILENO);
		redir = (t_redir *)redir->right;
	}
	if (curr->right != NULL && curr->right->sign == 1)
		close(redir->file_fd);
}

void	fork_out_dat_child(t_temp *curr, t_data *data)
{
	pid_t	pid;
	t_redir	*redir;
	int		status;

	status = 0;
	redir = (t_redir *)curr->right;
	if (curr->right == NULL)
		dup2(data->og_stdout, STDOUT_FILENO);
	if (curr->left != NULL && curr->left->sign == 5)
	{
		redir = (t_redir *)curr->left;
		dup2(redir->pipe_fd[0], STDIN_FILENO);
		close(redir->pipe_fd[1]);
	}
	pid = fork();
	if (pid == -1)
		perror("fork");
	if (pid == 0)
		child_exec(curr, data);
	if (data->free_hd == 1)
		close(data->hd_pipe_fd[0]);
	if (waitpid(pid, &status, 0) == -1)
		perror("wtf waitpid");
	post_forkination(curr, data, redir, status);
}
