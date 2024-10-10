/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_double_quotes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: helauren <helauren@student.42.fr>          +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2023/11/04 21:35:08 by helauren          #+#    #+#             */
/*   Updated: 2023/11/04 21:35:08 by helauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strcpy_no_double_quotes(char *dest, char *src)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (src[i])
	{
		if (src[i] != '\"')
		{
			if (src[i] == '\"' && even_bs_before(src, i) == 1)
			{
				i++;
				continue ;
			}
			dest = ft_strjoin_char(dest, src[i]);
			j++;
		}
		i++;
	}
	return (dest);
}

char	*vaaar(char *s, int i)
{
	char	*ret;

	ret = NULL;
	while (s[i] && s[i] != ' ' && s[i] != '$' && s[i] != '\'' && s[i] != '\"'
		&& s[i] != '\\' && s[i] != '.')
	{
		ret = ft_strjoin_char(ret, s[i]);
		i++;
	}
	return (ret);
}

void	ontheside(t_data *data, int *i, char *s)
{
	(*i)++;
	data->bs->var = vaaar(s, *i);
	data->bs->value = get_dict_value(data, data->bs->var);
	if (data->bs->value != NULL)
		data->bs->ret = ft_strjoin(data->bs->ret, data->bs->value);
	free(data->bs->value);
	free(data->bs->var);
	while (s[*i] && s[*i] != ' ' && s[*i] != '$' && s[*i] != '\''
		&& s[*i] != '\"' && s[*i] != '\\' && s[*i] != '.')
		(*i)++;
}

char	*bs_and_dollar(char *s, t_data *data, t_preparse *cur)
{
	int	i;

	i = 0;
	data->bs->ret = NULL;
	while (s && s[i])
	{
		if (s[i] == '$' && s[i + 1] && s[i + 1] != ' ')
		{
			ontheside(data, &i, s);
			continue ;
		}
		else if (s[i] == '\\' && (s[i + 1] == '$' || s[i + 1] == '\\'))
		{
			data->bs->ret = ft_strjoin_char(data->bs->ret, s[i + 1]);
			i++;
		}
		else if (cur->quote == 2 || s[i] != '\\')
			data->bs->ret = ft_strjoin_char(data->bs->ret, s[i]);
		i++;
	}
	free(s);
	return (data->bs->ret);
}

char	*handle_double_quotes(char *buffer, t_preparse *cur, t_data *data)
{
	char	*dest;

	(void)cur;
	dest = NULL;
	dest = ft_strcpy_no_double_quotes(dest, buffer);
	if (dest != NULL && ft_strcmp(dest, "$?") == 0)
	{
		free(buffer);
		free(dest);
		dest = ft_itoa(g_exit_status);
		return (dest);
	}
	dest = bs_and_dollar(dest, data, cur);
	if (dest == NULL)
	{
		free(dest);
		dest = malloc(sizeof(char) * 2);
		dest[0] = 0;
	}
	free(buffer);
	return (dest);
}
