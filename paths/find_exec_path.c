/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_exec_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helauren <helauren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 14:20:59 by helauren          #+#    #+#             */
/*   Updated: 2023/11/05 20:04:43 by helauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_backtracks(char *s)
{
	int	i;
	int	count;

	if (ft_strlen(s) <= 3)
		return (0);
	i = 2;
	if (s[0] == '.' && s[1] == '/')
		return (0);
	count = 0;
	while (s[i])
	{
		if (s[i - 1] == '/' && s[i] != '.')
			return (count);
		if (s[i] == '/' && s[i - 1] == '.' && s[i - 2] == '.')
			count++;
		i++;
	}
	return (count);
}

char	*backt_pwd(int backt, char *pwd)
{
	int	i;
	int	len;

	len = ft_strlen(pwd) - 1;
	i = 0;
	while (i < backt)
	{
		while (pwd[len] != '/')
			len--;
		len--;
		i++;
	}
	pwd[len + 1] = 0;
	return (pwd);
}

char	*clean_exec(char *s)
{
	int	i;

	i = 0;
	while (s[i] == '.' || s[i] == '/')
		i++;
	return (&s[i]);
}

char	*find_exec_path(char *s, t_data *data)
{
	data->f_p->old_s = s;
	data->f_p->backt = count_backtracks(s);
	data->f_p->pwd = find_pwd();
	if (data->f_p->backt > 0)
		data->f_p->pwd = backt_pwd(data->f_p->backt, data->f_p->pwd);
	s = clean_exec(s);
	data->f_p->path = ft_strjoin(data->f_p->pwd, "/");
	data->f_p->path = ft_strjoin(data->f_p->path, s);
	if (access(data->f_p->path, F_OK) == 0)
	{
		if (access(data->f_p->path, X_OK) == 0)
			return (data->f_p->path);
		else
		{
			printf("bash: %s: Permission denied\n", data->f_p->old_s);
			free(data->f_p->path);
			g_exit_status = 126;
			return (NULL);
		}
	}
	printf("no such file or directory: %s\n", data->f_p->old_s);
	g_exit_status = 126;
	free(data->f_p->path);
	return (NULL);
}
