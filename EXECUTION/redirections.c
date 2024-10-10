/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helauren <helauren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 14:06:55 by helauren          #+#    #+#             */
/*   Updated: 2023/11/05 16:09:08 by helauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	read_file_input(t_redir *redir, t_data *data)
{
	t_redir	*prev;

	if ((redir->sign != 1 && redir->sign != 2 && redir->sign != 3
			&& redir->sign != 4 && redir->sign != 5) && redir->right != NULL)
		redir = (t_redir *)redir->right;
	if (redir == NULL)
		return ;
	if (ft_strcmp(redir->type, "redir") || redir->sign == 0 || redir->sign >= 3)
		return ;
	while (redir != NULL && (redir->sign == 1 || redir->sign == 2))
	{
		prev = redir;
		redir = (t_redir *)redir->right;
	}
	if (redir == NULL || (redir->sign != 1 || redir->sign != 2))
		redir = prev;
	if (redir->sign == 1)
		dup2(redir->file_fd, STDIN_FILENO);
	else if (redir->sign == 2)
	{
		dup2(data->hd_pipe_fd[0], STDIN_FILENO);
		close(data->hd_pipe_fd[1]);
	}
}

void	read_pipe_input(t_redir *redir)
{
	if (redir->left == NULL)
		return ;
	if (ft_strcmp(redir->left->type, "redir"))
		return ;
	if (redir->left->sign != 5)
		return ;
	dup2(redir->pipe_fd[0], STDIN_FILENO);
}

int	should_redir(t_redir *redir)
{
	if (redir == NULL)
		return (1);
	if (redir->right == NULL)
		return (1);
	if ((redir->right->sign != 1) && (redir->right->sign != 2)
		&& (redir->right->sign != 5) && (redir->right->sign != 3)
		&& (redir->right->sign != 4))
	{
		return (1);
	}
	return (0);
}

void	redirect_output(t_redir *redir)
{
	int	sh;

	sh = should_redir(redir);
	if (sh == 1)
		return ;
	redir = (t_redir *)redir->right;
	while (redir->right != NULL && (redir->right->sign == 1
			|| redir->right->sign == 2))
		redir = (t_redir *)redir->right;
	while (redir->right != NULL && (redir->right->sign == 3
			|| redir->right->sign == 4 || redir->right->sign == 5))
		redir = (t_redir *)redir->right;
	if (redir->sign == 3 || redir->sign == 4)
	{
		while (redir->right != NULL && (redir->right->sign == 3
				|| redir->right->sign == 4))
			redir = (t_redir *)redir->right;
		dup2(redir->file_fd, STDOUT_FILENO);
	}
	if (redir->sign == 5)
		dup2(redir->pipe_fd[1], STDOUT_FILENO);
}
