/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helauren <helauren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 17:59:14 by ttaneski          #+#    #+#             */
/*   Updated: 2024/02/16 01:22:12 by helauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	process_cd(char *path, t_data *data)
{
	char	*old_pwd;
	char	*pwd;

	old_pwd = get_env_value(data, "OLDPWD");
	pwd = get_env_value(data, "PWD");
	if (old_pwd == NULL && pwd == NULL)
	{
		perror("get_env_value");
		free(old_pwd);
		free(pwd);
		return (1);
	}
	if (change_directory(path, data) != 0)
	{
		free(old_pwd);
		free(pwd);
		return (1);
	}
	update_env_variables(data, pwd);
	free(old_pwd);
	free(pwd);
	return (0);
}

int	process_cd_option_with_previous_path(t_data *data)
{
	int	pwd_i;
	int	old_pwd_i;

	pwd_i = find_index(data, "PWD");
	old_pwd_i = find_index(data, "OLDPWD");
	free(data->exp_var[old_pwd_i][1]);
	data->exp_var[old_pwd_i][1] = data->exp_var[pwd_i][1];
	if (chdir(data->previous_path) != 0)
	{
		free(data->previous_path);
		perror("chdir");
		return (1);
	}
	free(data->previous_path);
	data->previous_path = NULL;
	data->previous_path = data->pwd;
	data->exp_var[pwd_i][1] = find_pwd();
	return (0);
}
