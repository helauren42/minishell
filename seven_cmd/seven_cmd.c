/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   seven_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helauren <helauren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 20:53:34 by helauren          #+#    #+#             */
/*   Updated: 2023/11/07 20:53:34 by helauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*read_again_lmao(t_cmd *curr)
{
	char	*read;
	int		i;

	read = ft_strdup(curr->cmd_options[0]);
	i = 1;
	while (curr->cmd_options[i])
	{
		read = ft_strjoin(read, " ");
		read = ft_strjoin(read, curr->cmd_options[i]);
		i++;
	}
	return (read);
}

int	last_is_not_cat(t_temp *curr)
{
	t_cmd	*last;

	while (curr != NULL)
	{
		last = (t_cmd *)curr;
		curr = curr->right;
	}
	if ((ft_strcmp(last->type, "cmd") == 0 && ft_strcmp(last->cmd_options[0],
				"cat")) || (ft_strcmp(last->type, "cmd")))
	{
		if (ft_strcmp(last->type, "cmd") == 0 && ft_strcmp(last->cmd_options[0],
				"wc") == 0)
			return (1);
		return (0);
	}
	return (1);
}

int	seven_eleven(t_temp *first, t_data *data, char *read, t_cmd *curr)
{
	int	ret;

	ret = 0;
	if (ft_strcmp("echo", curr->cmd_options[0]) == 0)
		ret = exec_echo(read);
	if (ft_strcmp("export", curr->cmd_options[0]) == 0)
		ret = exec_export(read, curr, data);
	if (ft_strcmp("unset", curr->cmd_options[0]) == 0)
		ret = exec_unset(read, data);
	if (ft_strcmp("cd", curr->cmd_options[0]) == 0)
		ret = exec_cd(read, data);
	if (ft_strcmp("env", curr->cmd_options[0]) == 0)
		ret = out_env(data);
	if (ft_strcmp("pwd", curr->cmd_options[0]) == 0)
		ret = out_pwd();
	if ((ft_strcmp("exit", curr->cmd_options[0]) == 0))
	{
		if (first != NULL)
			free_tokenz(first);
		cmd_exit(read, data);
	}
	return (ret);
}

int	empty_read(char *read)
{
	int	i;

	i = 0;
	if (read == NULL || read[i] == 0)
		return (1);
	while (read[i])
	{
		if (read[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

int	seven_cmd(t_cmd *curr, t_data *data, t_temp *first)
{
	int		ret;
	char	*read;

	g_exit_status = 0;
	if (ft_strcmp(curr->type, "cmd"))
		return (0);
	ret = 0;
	read = read_again_lmao((t_cmd *)curr);
	if (empty_read(read) == 1)
		return (1);
	ret = seven_eleven(first, data, read, curr);
	if ((ft_strcmp("cat", curr->cmd_options[0]) == 0) && curr->right != NULL
		&& curr->right->sign == 5 && last_is_not_cat((t_temp *)curr) == 0)
		ret = prepare_cat(curr->cmd_options, (t_temp *)curr);
	free(read);
	return (ret);
}
