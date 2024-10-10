/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_it.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helauren <helauren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 16:25:08 by helauren          #+#    #+#             */
/*   Updated: 2023/11/07 20:49:39 by helauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	same_path(char *og_path, char ***dict)
{
	int		i;
	char	*test_path;

	i = 0;
	while (dict && dict[i] && ft_strcmp(dict[i][0], "PATH") != 0)
		i++;
	if (dict == NULL || dict[i] == NULL)
		return (1);
	test_path = dict[i][0];
	test_path = ft_strjoin_nofree(test_path, "=");
	test_path = ft_strjoin(test_path, dict[i][1]);
	if (ft_strcmp(test_path, og_path) == 0)
	{
		free(test_path);
		return (0);
	}
	free(test_path);
	return (1);
}

char	*is_cmd(char *s, t_data *data)
{
	int		i;
	char	*path;

	i = 0;
	if (ft_strncmp(s, "/bin/", 5) == 0)
		s = &s[5];
	if (ft_strcmp(s, "export") == 0 || ft_strcmp(s, "unset") == 0
		|| ft_strcmp(s, "exit") == 0 || ft_strcmp(s, "cd") == 0)
		return (ft_strdup("yes"));
	free_double_str(data->paths);
	data->paths = get_paths(data);
	while (data->paths && data->paths[i])
	{
		path = ft_strjoin_nofree(data->paths[i], "/");
		path = ft_strjoin(path, s);
		if (access(path, F_OK) == 0)
			return (path);
		if (path != NULL)
			free(path);
		path = NULL;
		i++;
	}
	return (NULL);
}

t_cmd	*cmd_it(char *s, t_data *data, char *path)
{
	t_cmd	*cmd;

	(void)s;
	(void)data;
	cmd = malloc(sizeof(t_cmd));
	cmd->type = ft_strdup("cmd");
	cmd->cmd_path = path;
	if (ft_strncmp(s, "/bin/", 5) == 0)
		s = &s[5];
	cmd->cmd_options = malloc(sizeof(char *) * 2);
	cmd->cmd_options[0] = ft_strdup(s);
	cmd->cmd_options[1] = NULL;
	cmd->left = NULL;
	cmd->right = NULL;
	cmd->sign = 0;
	return (cmd);
}

t_temp	*decoy_it(void)
{
	t_temp	*decoy;

	decoy = malloc(sizeof(t_temp *));
	decoy->type = ft_strdup("decoy");
	return (decoy);
}
