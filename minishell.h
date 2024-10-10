/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helauren <helauren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 14:30:40 by ttaneski          #+#    #+#             */
/*   Updated: 2023/11/07 21:50:06 by helauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./gnl/get_next_line_bonus.h"
# include "libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

extern int				g_exit_status;

typedef struct s_temp
{
	char				*type;
	struct s_temp		*left;
	struct s_temp		*right;
	int					sign;
	char				*delim;
}						t_temp;

typedef struct s_redir
{
	char				*type;
	t_temp				*left;
	t_temp				*right;
	int					sign;
	int					pipe_fd[2];
	int					file_fd;
	int					total_length_buff;
	char				*delim;
	char				flag;
}						t_redir;

typedef struct s_cmd
{
	char				*type;
	t_temp				*left;
	t_temp				*right;
	char				*cmd_path;
	char				**cmd_options;
	int					sign;
}						t_cmd;

typedef struct s_exec
{
	char				*type;
	t_temp				*left;
	t_temp				*right;
	char				*path;
	char				**options;
	int					sign;
}						t_exec;

typedef struct s_three
{
	t_exec				*exec;
	t_cmd				*cmd;
	t_redir				*redir;
}						t_three;

typedef struct s_preparse
{
	char				*s;
	int					quote;
	struct s_preparse	*next;
}						t_preparse;

typedef struct s_exit
{
	int					argc;
	char				**argv;
	int					exit_code;
}						t_exit;

typedef struct s_tokenization
{
	t_temp				*first;
	t_temp				*left;
	t_temp				*right;
	t_temp				*before_decoy;
}						t_tokenization;

typedef struct s_f_exec_path
{
	int					backt;
	char				*pwd;
	char				*path;
	char				*old_s;
}						t_f_exec_path;

typedef struct s_bs
{
	char				*ret;
	char				*var;
	char				*value;
}						t_bs;

typedef struct s_data
{
	char				*old_pwd;
	char				*previous_path;
	t_bs				*bs;
	t_f_exec_path		*f_p;
	t_tokenization		*t;
	t_three				*tt;
	t_exit				*exit;
	char				*set_read;
	t_temp				*curr;
	int					free_hd;
	char				*hd_line;
	int					hd_pipe_fd[2];
	char				*og_path;
	char				**env_for_execve;
	char				*pwd;
	char				**env;
	char				***exp_var;
	char				**env_var;
	char				**env_value;
	char				**paths;
	char				*prompt;
	int					words;
	char				**split_paths_cmd;
	char				**init_av;
	int					flag;
	char				**buffer;
	size_t				total_length_buff;
	int					og_stdin;
	int					og_stdout;
	int					pipe_i;
}						t_data;

// General Utilities
int						prepare_cat(char **option, t_temp *first);
void					set_exit_status(int status);
int						ft_cat(char **option);
char					*path_line(char **env);
void					parse_into_exp_var(t_data *data, char **env);
void					write_error(char *s);
char					*give_prompt(char **env);
char					*find_pwd(void);
char					*get_pwd(char *pwd, char *user);
int						find_user_pwd(char *pwd, char *user);
void					output_pwd_up(char *pwd);
char					*find_user(char **env);
char					*get_user(char *user);
void					init_to_strings(t_data *data, char *read);
char					*handle_double_quotes(char *buffer, t_preparse *cur,
							t_data *data);
char					*handle_single_quotes(char *buffer, t_preparse *cur,
							t_data *data);
int						handle_quotes(t_preparse *head, t_data *data);
char					*find_path(char **env);
char					*get_cmd_path(char **split_paths, char *cmmd);
char					*find_exec_path(char *s, t_data *data);
char					*backt_pwd(int backt, char *pwd);

// Seven Commands
int						seven_cmd(t_cmd *curr, t_data *data, t_temp *first);
int						out_env(t_data *data);
int						out_pwd(void);
void					find_var_error(char *read);
int						find_exp_var(char *var, char ***dict);
int						exec_unset(char *read, t_data *data);
int						exec_export(char *read, t_cmd *curr, t_data *data);
char					***only_var(char *variable, char ***dict);
char					*expand_tilde(char *path, t_data *data, int *tilde,
							int *nil);
int						exec_echo(char *read);
int						is_all_num(char *str);
void					update_env_variables(t_data *data, char *pwd);
int						change_directory(char *path, t_data *data);
char					*get_env_value(t_data *data, char *var);
char					*expand_tilde(char *path, t_data *data, int *tilde,
							int *nil);
char					*handle_tilde_expansion(char *path, char *home);
int						process_cd_option_with_previous_path(t_data *data);
int						handle_cd_operation(t_data *data);
int						process_cd(char *path, t_data *data);

// Tokenization
t_preparse				*first_preparse(t_preparse *preparse, t_data *data);
t_preparse				*get_rid_of_backslash(t_preparse *first);
t_temp					*tokenize_this(t_preparse *preparse, t_data *data,
							int first, t_temp *left);
void					tokenize_as_option_arg(t_temp *left,
							t_preparse *preparse);
t_temp					*tokenization(t_preparse *preparse, t_data *data);
void					print_tokenz(t_temp *first);
void					tokenization_fail2(void);
int						is_redir(char *s);
t_redir					*redir_it(int sign, t_data *data);
int						is_exec(char *s);
t_exec					*exec_it(char *s, t_data *data);
char					*is_cmd(char *s, t_data *data);
t_cmd					*cmd_it(char *s, t_data *data, char *path);
t_temp					*decoy_it(void);
char					**ft_strdup2d(char **s, char *new_s);

// Error Handling
void					free_redir(t_redir *redir, int heredoc);
void					free_init_av(t_data *data);
void					tokenization_fail(char *s);
void					cmd_exit(char *read, t_data *data);
void					free_tokenz(t_temp *first);
void					free_cmd(t_cmd *cmd);
void					free_data(t_data *data);
void					free_hd(t_data *data);
void					error_unexpected_token(char c);
int						error_one(char *s);
char					*error_null(char *s);
t_redir					*error_null_redir(char *s);
void					error_none(char *s);
t_temp					*tokenz_null(t_temp *first);

// Directory and File Handling
char					**get_paths(t_data *data);
t_temp					*parser(char **init_av, t_data *data);
t_preparse				*strings_to_linked_list(t_data *data);
void					free_split(char **words);

// Signal Handling
void					sigint_handler(int signo);
void					sigint_child(int signum);

// Colors
void					reset_text_color(void);
void					change_text_color(int color_code);
void					set_text_color_to_orange(void);

// Change Directory (cd)
int						exec_cd(char *read, t_data *data);
char					*parse_cd(char *read);

// Linked List Operations
void					print_preparse_list(t_preparse *head);
void					free_preparse_list(t_preparse *head);

// Heredoc Handling
t_redir					*handle_heredoc_input(t_redir *heredoc, t_data *data);

// Execution
void					execution(t_temp *first, t_data *data);
char					**env_execve(char ***s);
void					read_pipe_input(t_redir *redir);
void					read_file_input(t_redir *redir, t_data *data);
void					redirect_output(t_redir *redir);
void					fork_out_dat_child(t_temp *curr, t_data *data);
t_preparse				*create_preparse_node(char *s, int quote);

// Miscellaneous Utilities
int						**words_addr(char *read, int *len);
int						what_quote(char *s);
int						var_len(char *s, int i);
void					get_var(char *s, int i, char *var);
int						words_minus1(int **addr);
void					output_addr(int **addr);
int						find_next_word(char *read, int i);
char					*parse_cd(char *read);
char					*get_home_directory(t_data *data);
int						find_index(t_data *data, char *str);
int						space(char *str);
char					***ft_join_var(char ***s, char *variable, char *value);
char					*find_value(char *read);
char					*find_var(char *read);
char					*init_this_ret(char *read, int *i);
char					*find_var6(char *read);
char					*find_value6(char *read);
int						valid_name_var(char *s);
char					***replace_var(t_data *data, char *value, int i);
void					eliminate_var(int found, char ***dict);
int						count_words(char *s);
char					*extract_word(char *all);
int						is_redir(char *s);
t_redir					*redir_it(int sign, t_data *data);
int						is_exec(char *s);
char					*get_env_value(t_data *data, char *var);
void					send_to_pipe(t_data *data);
void					prepare_hd_pipe(t_data *data);
char					*next_word(char *all);
int						has_new_line(char *s);
char					*read_whole_file(char *file);
char					*get_dict_value(t_data *data, char *var);
int						even_bs_before(char *s, int i);
void					mid(int *j, char *dest, char *value);
#endif
