/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helauren <helauren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 20:38:56 by helauren          #+#    #+#             */
/*   Updated: 2023/11/08 12:45:21 by helauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status;

void	read_input1(char *read, char **env, t_data *data)
{
	data->init_av = NULL;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sigint_handler);
	if (read != NULL)
		free(read);
	set_text_color_to_orange();
	if (data->prompt != NULL)
		free(data->prompt);
	data->prompt = give_prompt(env);
	data->prompt = ft_strjoin_free2("\xF0\x9F\x92\x80 ", data->prompt);
	data->prompt = ft_strjoin(data->prompt, "\xF0\x9F\x92\x80 ");
}

void	read_input(char *read, char **env, t_data *data, t_preparse *head)
{
	t_temp		*first;

	first = NULL;
	while (1)
	{
		read_input1(read, env, data);
		read = readline(data->prompt);
		if (!read)
			cmd_exit(read, data);
		add_history(read);
		init_to_strings(data, read);
		head = strings_to_linked_list(data);
		if (handle_quotes (head, data))
		{
			free_double_str(data->init_av);
			free_preparse_list(head);
			continue ;
		}
		first = tokenization(head, data);
		free_preparse_list(head);
		if (read == NULL || read[0] == 0 || first == NULL)
			continue ;
		execution(first, data);
		free_tokenz(first);
	}
}

void	initialize_data(t_data *data, char **env)
{
	data->prompt = NULL;
	data->old_pwd = NULL;
	data->previous_path = NULL;
	data->bs = malloc(sizeof(t_bs));
	data->f_p = malloc(sizeof(t_f_exec_path));
	data->exit = malloc(sizeof(t_exit));
	data->t = malloc(sizeof(t_tokenization));
	data->pwd = NULL;
	data->env_for_execve = NULL;
	data->og_stdin = dup(STDIN_FILENO);
	data->og_stdout = dup(STDOUT_FILENO);
	data->env = env;
	data->exp_var = NULL;
	data->buffer = NULL;
	data->free_hd = 0;
	parse_into_exp_var(data, env);
	data->paths = get_paths(data);
}

int	main(int ac, char **av, char **env)
{
	char		*read;
	t_data		*data;
	t_preparse	*head;

	(void)ac;
	(void)av;
	head = NULL;
	data = malloc(sizeof(t_data));
	initialize_data(data, env);
	read = NULL;
	read_input(read, env, data, head);
	return (0);
}
