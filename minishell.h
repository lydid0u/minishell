/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboudjel <lboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 20:42:22 by lboudjel          #+#    #+#             */
/*   Updated: 2024/03/18 06:18:55 by lboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./ft_printf/ft_printf.h"
# include "./libft/libft.h"
# include "srcs/gnl/gnl.h"
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
	char	**envp;
	char	*infile;
	char	*outfile;
	int		nbr_cmd;
	char	**arg_cmd;
	int		infile_fd;
	int		outfile_fd;
	int		fd[2];
	int		pid[1024];
	char	**tab_cmd;
	char	**args_path;
	int		prev;
	int		here_doc;
	char	*stop_word;
	char	**cmd;
	char	*prompt;
}			t_pipex;

typedef struct s_copyenv
{
	char	*key;
	char 	*value;
	struct s_copyenv *next;
}				t_copyenv;

//				pipex1				//
void		child(t_pipex *pipex, int i);
void		piping_and_forking(t_pipex *pipex);
void		init_struct(t_pipex *pipex, int argc, char **argv, char **envp);
void		redirection(t_pipex *pipex, int i);
int			exec(int argc, char **envp, t_pipex *pipex);

//				pipex2				//
char		*access_cmd(t_pipex *pipex, int i);
int			open_fd(t_pipex *pipex, int i);
char		**get_path(char **envp);
void		free_tab(char **tab);
void		here_doc(char *infile, char *stop_word);

//				addspaces			//
char		*add_spaces(char *input);
int			count_token(char *input);

//				quote				//
int			check_quotes(char *input);
void		quote_negatif(char *input);
void		quote_positif(char *input);

//				parsing				//
int			parsing(char *input);
int			check_separator(char *input);

//				syntax_error		//
int			pipe_in_first(char *input);
int			pipe_in_last(char *input, int i);
int			redir_in_last(char *input, int i);
int			double_pipe(char *input);
int			redir_n_pipe(char *input);

//				expand				//
char		*get_value_from_key(char *key, char **envp);
int			get_len_of_key(char *str);
int			get_len_of_value_from_str(char *str, char **envp);
int			total_expand(char *input, char **envp);
char		*final_string(char *input, char **envp);

//				expand_2	   		//
void		handle_single_quote(char *input, int *i, int *count);
void		write_single_quote(char *input, char *output, int *i, int *j);
int			is_key_valid(char *key, char **envp);


//				export_unset      	//
void	copy_envp(char **envp, t_copyenv *lst);
int	lstsize(t_copyenv *lst);
void	free_lst(t_copyenv *lst);


//				copy_envp			//
t_copyenv *create_node(void);
void key_env(t_copyenv *node, char *key);
void value_env(t_copyenv *node, char *value);
int	nbr_of_element_in_envp(char **envp);
void looping_to_copy_env(t_copyenv *lst);
void create_lst(char **envp);

// garbage collector ??

#endif
