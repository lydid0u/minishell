/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboudjel <lboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 20:42:22 by lboudjel          #+#    #+#             */
/*   Updated: 2024/03/26 03:41:05 by lboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./ft_printf/ft_printf.h"
# include "./libft/libft.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define SYNTAXERROR "bash: syntax error near unexpected token `%s"

typedef struct pipex
{
	char				**envp;
	char				*infile;
	char				*outfile;
	int					nbr_cmd;
	char				**arg_cmd;
	int					infile_fd;
	int					outfile_fd;
	int					fd[2];
	int					pid[1024];
	char				**tab_cmd;
	char				**args_path;
	int					prev;
	int					here_doc;
	char				*stop_word;
	char				**cmd;
	char				*prompt;
}						t_pipex;

typedef struct s_copyenv
{
	char				*key;
	char				*value;
	struct s_copyenv	*next;
}						t_copyenv;

//				pipex1				//
void					child(t_pipex *pipex, int i);
void					piping_and_forking(t_pipex *pipex);
void					init_struct(t_pipex *pipex, int argc, char **argv,
							char **envp);
void					redirection(t_pipex *pipex, int i);
int						exec(int argc, t_copyenv *lst_envp, t_pipex *pipex);

//				pipex2				//
char					*access_cmd(t_pipex *pipex, int i);
int						open_fd(t_pipex *pipex, int i);
char					**get_path(char **envp);
void					free_tab(char **tab);
void					here_doc(char *infile, char *stop_word);

//				addspaces			//
char					*add_spaces(char *input);
int						count_token(char *input);

//				quote				//
int						check_quotes(char *input);
void					quote_negatif(char *input);
void					quote_positif(char *input);

//				parsing				//
int						parsing(char *input);
int						check_separator(char *input);

//				syntax_error		//
int						pipe_in_first(char *input);
int						pipe_in_last(char *input, int i);
int						redir_in_last(char *input, int i);
int						double_pipe(char *input);
int						redir_n_pipe(char *input);

//				expand				//
char					*get_value_from_key(char *key, t_copyenv *lst_envp);
int						get_len_of_key(char *str);
int						get_len_of_value_from_str(char *str, t_copyenv *lst_envp);
int						total_expand(char *input, t_copyenv *lst_envp);
char					*final_string(char *input, t_copyenv *lst_envp);

//				expand_2				//
void					handle_single_quote(char *input, int *i, int *count);
void					write_single_quote(char *input, char *output, int *i,
							int *j);
int						is_key_valid(char *key, t_copyenv *lst_envp);
char					*get_key_expand(char *str);

//				copy_envp			//
void					key_env(t_copyenv *node, char *key);
void					value_env(t_copyenv *node, char *value);
int						nbr_of_element_in_envp(char **envp);
t_copyenv				*create_lst(char **envp);
void					copy_envp(char **envp, t_copyenv *lst);

//				export      	//
int						export_key_already_existing(char *key, char *str,
							t_copyenv *head);
int						create_export_node(char *str, t_copyenv *head);
int						wrong(char *str);
void					built_in_export(char **args, t_copyenv *lst);

//				unset			//
int						parsing_unset(char *str, t_copyenv *head);
void					built_in_unset(char **args, t_copyenv *lst);

//				utils_export	//
char					*get_key(char *str);
void					add_node_export_back(t_copyenv *lst,
							t_copyenv *new_node);
void					free_lst(t_copyenv *lst);
t_copyenv				*create_node(void);

// garbage collector ??

#endif