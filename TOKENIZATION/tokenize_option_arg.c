/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_option_arg.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helauren <helauren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 15:59:08 by helauren          #+#    #+#             */
/*   Updated: 2023/11/07 14:45:55 by helauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ft_strdup2d(char **s, char *new_s)
{
	int		i;
	char	**ret;

	i = 0;
	while (s && s[i])
		i++;
	if (new_s == NULL)
		return (s);
	ret = malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (s && s[i])
	{
		ret[i] = ft_strdup(s[i]);
		free(s[i]);
		i++;
	}
	free(s);
	ret[i] = ft_strdup(new_s);
	ret[i + 1] = NULL;
	return (ret);
}

void	redir_option(t_redir *redir, t_preparse *preparse)
{
	if (redir->sign == 1)
		redir->file_fd = open(preparse->s, O_RDONLY, 0644);
	if (redir->sign == 2)
		redir->delim = ft_strdup(preparse->s);
	if (redir->sign == 3)
		redir->file_fd = open(preparse->s, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (redir->sign == 4)
		redir->file_fd = open(preparse->s, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (redir->sign == 5)
		pipe(redir->pipe_fd);
}

void	tokenize_as_option_arg(t_temp *left, t_preparse *preparse)
{
	t_cmd	*cmd_type;
	t_exec	*exec_type;
	t_redir	*redir_type;

	redir_type = (t_redir *)left;
	cmd_type = (t_cmd *)left;
	exec_type = (t_exec *)left;
	if (left == NULL)
		return ;
	if (ft_strcmp(left->type, "redir") == 0)
		redir_option(redir_type, preparse);
	if (ft_strcmp(left->type, "cmd") == 0)
		cmd_type->cmd_options = ft_strdup2d(cmd_type->cmd_options, preparse->s);
	if (ft_strcmp(left->type, "exec") == 0)
		exec_type->options = ft_strdup2d(exec_type->options, preparse->s);
}
