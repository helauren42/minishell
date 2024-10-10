/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helauren <helauren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 16:01:54 by helauren          #+#    #+#             */
/*   Updated: 2023/11/01 16:34:10 by helauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_user(char *user)
{
	int		i;
	char	*ret;

	i = 0;
	while (user[i] != '=')
		i++;
	i++;
	ret = &user[i];
	return (ret);
}

char	*find_user(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (env[i][0] == 'U' && env[i][1] == 'S' && env[i][2] == 'E'
			&& env[i][3] == 'R' && env[i][4] == '=')
			break ;
		i++;
	}
	if (env[i] == 0)
		write_error("environment error\n");
	return (env[i]);
}

void	output_pwd_up(char *pwd)
{
	int	i;

	i = 0;
	while (pwd[i] != '=')
		i++;
	i++;
	while (pwd[i])
	{
		printf("%c", pwd[i]);
		i++;
	}
}

int	find_user_pwd(char *pwd, char *user)
{
	int	i;

	i = 0;
	while (pwd[i])
	{
		if (pwd[i] == user[0])
		{
			if (ft_strncmp(&pwd[i], user, ft_strlen(user)) == 0)
				return (i);
		}
		i++;
	}
	return (-1);
}

char	*get_pwd(char *pwd, char *user)
{
	int		i;
	char	*ret;
	int		user_pwd;

	ret = NULL;
	user_pwd = find_user_pwd(pwd, user);
	ret = ft_strjoin(ret, ":~");
	i = 0;
	if (user_pwd > 0)
		i = user_pwd;
	while (pwd[i] != '/' && pwd[i] != 0)
		i++;
	if (pwd[i] == 0 && user_pwd > 0)
	{
		return (ret);
	}
	i++;
	if (user_pwd > 0)
		ret = ft_strjoin(ret, "/");
	ret = ft_strjoin(ret, &pwd[i]);
	return (ret);
}
