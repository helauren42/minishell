/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_single_quotes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttaneski <ttaneski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 13:34:23 by ttaneski          #+#    #+#             */
/*   Updated: 2023/10/31 13:34:23 by ttaneski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strlen_no_single_quotes(char *s)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (s[i])
	{
		if (s[i] != '\'')
			len++;
		i++;
	}
	return (len);
}

char	*ft_strcpy_no_single_quotes(char *dest, char *src)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (src[i])
	{
		if (src[i] != '\'')
		{
			dest[j] = src[i];
			j++;
		}
		i++;
	}
	dest[j] = 0;
	return (dest);
}

char	*handle_single_quotes(char *buffer, t_preparse *cur, t_data *data)
{
	char	*dest;

	(void)cur;
	(void)data;
	dest = malloc(sizeof(char) * (ft_strlen_no_single_quotes(buffer) + 1));
	cur->s = ft_strcpy_no_single_quotes(dest, buffer);
	free(buffer);
	return (dest);
}

// void	clean_up_double_quotes(t_data *data)
// {
// 	int		i;
// 	int		len;
// 	char	**ss;

// 	ss = init_ss(data->init_av);
// 	i = 0;
// 	while(data->init_av[i])
// 	{
// 		len = ft_strlen_no_double_quotes(data->init_av[i]);
// 		printf("test i = %d, len = %d\n", i, len);
// 		ss[i] = malloc(sizeof(char) * (len + 1));
// 		ft_strcpy_no_double_quotes(ss[i], data->init_av[i]);
// 		// free(data->init_av[i]);
// 		i++;
// 	}
// 	// free(data->init_av);
// 	data->init_av = ss;
// }
