/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd1.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helauren <helauren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 17:57:37 by ttaneski          #+#    #+#             */
/*   Updated: 2023/11/07 20:52:17 by helauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*handle_tilde_expansion(char *path, char *home)
{
	char	*result;

	if (home)
	{
		if (path[1] == '/')
		{
			result = malloc(ft_strlen(home) + ft_strlen(path + 1) + 1);
			ft_strcpy(result, home);
			ft_strcat(result, path + 1);
			return (result);
		}
		else if (path[1] == '\0')
			return (home);
	}
	return (path);
}

char	*expand_tilde(char *path, t_data *data, int *tilde, int *nil)
{
	char	*home;
	char	*result;

	home = get_home_directory(data);
	if (path == NULL)
	{
		*nil = 0;
		return (home);
	}
	if (space(path) == 1)
		return (home);
	if (ft_strcmp(path, ".") == 0)
	{
		free(home);
		return (path);
	}
	if (path != NULL && path[0] == '~')
	{
		*tilde = 0;
		result = handle_tilde_expansion(path, home);
		free(home);
		return (result);
	}
	free(home);
	return (path);
}

char	*get_env_value(t_data *data, char *var)
{
	int		i;
	char	*str;
	char	*res;

	i = 0;
	str = NULL;
	res = NULL;
	while (data->env[i])
	{
		if (ft_strncmp(data->env[i], var, ft_strlen(var)) == 0)
		{
			str = ft_strdup(data->env[i]);
			res = ft_strchr(str, '=');
			if (res)
			{
				res = ft_strdup(res + 1);
				free(str);
				return (res);
			}
		}
		free(str);
		str = NULL;
		i++;
	}
	return (NULL);
}

int	change_directory(char *path, t_data *data)
{
	if (chdir(path) != 0)
	{
		if (data->old_pwd != NULL)
		{
			free(data->old_pwd);
			data->old_pwd = NULL;
			data->previous_path = ft_strdup("shite");
			free(data->previous_path);
			data->previous_path = NULL;
		}
		if (data->pwd != NULL)
		{
			free(data->pwd);
			data->pwd = NULL;
		}
		perror("chdir");
		g_exit_status = 1;
		return (1);
	}
	return (0);
}

void	update_env_variables(t_data *data, char *pwd)
{
	int	pwd_index;
	int	old_pwd_index;

	pwd_index = find_index(data, "PWD");
	old_pwd_index = find_index(data, "OLDPWD");
	free(data->exp_var[pwd_index][1]);
	data->exp_var[pwd_index][1] = find_pwd();
	free(data->exp_var[old_pwd_index][1]);
	data->exp_var[old_pwd_index][1] = ft_strdup(pwd);
}
