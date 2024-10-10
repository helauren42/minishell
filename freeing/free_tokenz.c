/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tokenz.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: ttaneski <ttaneski@student.42.fr>          +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2023/10/31 14:45:48 by ttaneski          #+#    #+#             */
/*   Updated: 2023/10/31 14:45:48 by ttaneski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_redir(t_redir *redir, int heredoc)
{
	if (redir->sign == 2)
		free(redir->delim);
	free(redir->type);
	if (heredoc == 0)
	{
		free(redir);
		redir = NULL;
	}
	free(redir);
}

void	free_exec(t_exec *exec)
{
	if (exec->path != NULL)
		free(exec->path);
	free_double_str(exec->options);
	free(exec->type);
	free(exec);
}

void	free_cmd(t_cmd *cmd)
{
	int	i;

	free(cmd->cmd_path);
	i = 0;
	while (cmd->cmd_options[i])
	{
		free(cmd->cmd_options[i]);
		i++;
	}
	free(cmd->cmd_options);
	free(cmd->type);
	free(cmd);
}

void	free_tokenz(t_temp *first)
{
	t_temp	*next;

	if (first == NULL)
		return (error_none("in free first == NULL\n"));
	while (first != NULL)
	{
		next = first->right;
		if (ft_strcmp(first->type, "cmd") == 0)
			free_cmd((t_cmd *)first);
		else if (ft_strcmp(first->type, "exec") == 0)
			free_exec((t_exec *)first);
		else if (ft_strcmp(first->type, "redir") == 0)
			free_redir((t_redir *)first, 1);
		first = next;
	}
	first = NULL;
}
