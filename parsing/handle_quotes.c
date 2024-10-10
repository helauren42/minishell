/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: ttaneski <ttaneski@student.42.fr>          +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2023/10/31 14:46:13 by ttaneski          #+#    #+#             */
/*   Updated: 2023/10/31 14:46:13 by ttaneski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	what_quote(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\"')
			return (2);
		else if (s[i] == '\'')
			return (1);
		i++;
	}
	return (0);
}

int	valid_no_quotes(char *s, t_preparse *cur)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '>' || s[i] == '<' || s[i] == '|')
		{
			if (cur->next == NULL)
				return (1);
		}
		if (s[i] == '&' || s[i] == '!' || s[i] == '(' || s[i] == ')'
			|| s[i] == '#' || s[i] == '`' || s[i] == '@')
		{
			if (i == 0 || (i > 0 && s[i - 1] != '\\'))
			{
				g_exit_status = 2;
				error_unexpected_token(s[i]);
				return (1);
			}
		}
		i++;
	}
	return (0);
}

char	*update_special_characters(char *s, t_data *data)
{
	int	i;

	i = 0;
	if (s != NULL && ft_strlen(s) == 1)
	{
		if (s[i] == '~' && (s[i + 1] == ' ' || s[i + 1] == 0))
		{
			free(s);
			s = get_env_value(data, "HOME");
			return (s);
		}
	}
	while (s[i])
		i++;
	return (s);
}

int	handle_quotes(t_preparse *head, t_data *data)
{
	int			wot;
	t_preparse	*cur;

	cur = head;
	if (cur == NULL)
		return (1);
	while (1)
	{
		wot = what_quote(cur->s);
		if (wot == 0)
		{
			if (valid_no_quotes(cur->s, cur) == 1)
				return (1);
			cur->s = update_special_characters(cur->s, data);
		}
		if (wot == 2 || wot == 0)
			cur->s = handle_double_quotes(cur->s, cur, data);
		if (wot == 1)
			cur->s = handle_single_quotes(cur->s, cur, data);
		cur = cur->next;
		if (cur == NULL)
			break ;
	}
	return (0);
}
