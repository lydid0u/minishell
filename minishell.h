/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboudjel <lboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 17:27:52 by lboudjel          #+#    #+#             */
/*   Updated: 2024/04/29 17:27:52 by lboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./ft_printf/ft_printf.h"
# include "./libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <unistd.h>
# include <fcntl.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <errno.h>

# define SYNTAXERROR "bash: syntax error near unexpected token `%s"
# define DEBUG 0

typedef struct s_copyenv
{
	char				*key;
	char				*value;
	struct s_copyenv	*next;
}	t_copyenv;

typedef struct token
{
	char	*cmd;
	int		arg_count;
	int		file_count;
	char	**args;
	int		*redir_chevron;
	char	**files;
}	t_token;

typedef struct pipex
{
	t_copyenv	*envp;
	char		**tab_env;
	char		**path;
	int			nbr_cmd;
	char		**cmd;
	int			fd[2];
	int			pid[1024];
	int			prev;
	int			here_doc;
	char		*stop_word;
	char		*prompt;
	int			in;
	int			out;
	int			status_code;
	t_token		*token;
}	t_pipex;

// ====================================================================
// 						[P][A][R][S][I][N][G]
// ====================================================================

//				addspaces			//
char		*add_spaces(char *input);
int			count_token(char *input);

//				expand_2				//
void		handle_single_quote(char *input, int *i, int *count);
void		write_single_quote(char *input, char *output, int *i, int *j);
int			is_key_valid(char *key, t_copyenv *lst_envp);
char		*get_key_expand(char *str);

//				expand				//
char		*get_value_from_key(char *key, t_copyenv *lst_envp);
int			get_len_of_value_from_str(char *str,
				t_copyenv *lst_envp);
int			get_len_of_key(char *str);
int			total_expand(char *input, t_copyenv *lst_envp);
void		question_mark(t_pipex *pipex, char *output, int *j);

//				parsing				//
int			parsing(char *input);
int			check_separator(char *input);
int			double_separator(char *input, int *i);
int			redir_n_pipe(char *input);
char		*final_string(char *input, t_copyenv *lst_envp, t_pipex *pipex);

//				quote				//
int			check_quotes(char *input);
void		quote_negatif(char *input);
void		quote_positif(char *input);
char		*suppresing_quote(char *input);

//				syntax_error		//
int			pipe_in_first(char *input);
int			pipe_in_last(char *input, int i);
int			redir_in_last(char *input, int i);
int			double_pipe(char *input);

//				token			//
int			is_a_redirection(char *str);
t_token		*alloc_token_struct(char **tab);
t_token		*tokenisation(char *input);

// ====================================================================
// 							[E][X][E][C]
// ====================================================================

//				copy_envp			//
void		key_env(t_copyenv *node, char *key);
void		value_env(t_copyenv *node, char *value);
int			nbr_of_element_in_envp(char **envp);
t_copyenv	*create_lst(char **envp);
void		copy_envp(char **envp, t_copyenv *lst);

//				pipex1				//
void		child(t_pipex *pipex, t_copyenv *lst_envp, int i);
void		piping_and_forking(t_pipex *pipex, t_copyenv *lst_envp);
void		ft_waitpid(t_pipex *pipex);
void		init_struct(t_pipex *pipex, int argc, t_copyenv *lst_envp);
int			exec(int argc, t_copyenv *lst_envp, t_pipex *pipex);

//				pipex2				//
char		*access_cmd(t_pipex *pipex, t_token *token);
char		**get_path(t_copyenv *lst_envp);
void		redirection(t_pipex *pipex, int i);

//				redir_chevron		//
int			handle_redirection(t_token *cmd);
void		chevron_no_fork(t_pipex *pipex, t_token *token,
				t_copyenv *lst_envp);

// ====================================================================
// 						[B][U][I][L][T] [I][N]
// ====================================================================

//				built-in_utils		//
int			is_builtin(char *cmd);
void		free_handle_bt(t_pipex *pipex);
void		free_handle_bt_no_fork(t_pipex *pipex, t_copyenv *lst_envp);

//				built-in		//
int			handle_built_in_pipex(t_token *token, t_pipex *pipex, t_copyenv *lst_envp);
int			handle_built_in_no_fork(t_pipex *pipex, t_token *token,
				t_copyenv *lst_envp);
int			built_in_pwd(void);
int			built_in_env(t_copyenv *lst_envp);

//				echo_and_cd		//
void		print_echo(char **tab);
int			built_in_echo(char **str);
int			echo_option_n(char *str);
char		*find_home(t_copyenv *lst_envp);
int			built_in_cd(char **tab, t_copyenv *lst_envp);

//				exit		//
int			ft_isnumber(char *str);
int			ft_exit_args_is_valid(char *args);
int			ft_exit(t_pipex *pipex, t_token *token, t_copyenv *lst_envp, int fork);

//				export_utils	//
char		*get_key(char *str);
void		add_node_export_back(t_copyenv *lst,
				t_copyenv *new_node);
t_copyenv	*create_node(void);

//				export      	//
int			export_key_already_existing(char *key, char *str, t_copyenv *head);
int			create_export_node(char *str, t_copyenv *head);
int			wrong_args(char *str);
int			bt_export_loop_to_create_node(char *arg, t_copyenv *head);
int			built_in_export(char **args, t_copyenv *lst);

//				unset			//
int			parsing_unset(char *str, t_copyenv *head);
int			built_in_unset(char **args, t_copyenv *lst);

// ====================================================================
// 
// ====================================================================

//				free			//
void		free_tab(char **tab);
void		free_lst(t_copyenv *lst);
void		free_all(t_pipex *pipex, t_copyenv *lst_envp, t_token *tok);
void		free_token(t_token *token);

//				signals			//
void		backslash(int signal);
void		ctrl_c(int signal);

char		**copy_env_to_tab(char **env);


void	free_exit(t_pipex *pipex, t_token *token, t_copyenv *lst_envp, int fork);
#endif