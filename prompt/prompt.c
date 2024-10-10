/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helauren <helauren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 15:33:10 by helauren          #+#    #+#             */
/*   Updated: 2023/11/07 15:58:06 by helauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*find_pwd(void)
{
	char	buff[1024];

	if (getcwd(buff, sizeof(buff)) == NULL)
		return (NULL);
	buff[sizeof(buff) - 1] = '\0';
	return (ft_strdup(buff));
}

char	*give_prompt(char **env)
{
	char	*user;
	char	*userbis;
	char	*pwd;
	char	*tofree;

	user = find_user(env);
	user = get_user(user);
	pwd = find_pwd();
	tofree = pwd;
	userbis = ft_strdup(user);
	pwd = get_pwd(pwd, user);
	userbis = ft_strjoin(userbis, pwd);
	userbis = ft_strjoin(userbis, "$ ");
	free(tofree);
	free(pwd);
	return (userbis);
}

int	out_pwd(void)
{
	char	*pwd;

	pwd = find_pwd();
	printf("%s\n", pwd);
	free(pwd);
	return (1);
}
