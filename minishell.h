/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboudjel <lboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 20:42:22 by lboudjel          #+#    #+#             */
/*   Updated: 2024/03/07 04:32:59 by lboudjel         ###   ########.fr       */
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
}			t_pipex;

//				pipex1				//
void		child(t_pipex *pipex, int i);
void		piping_and_forking(t_pipex *pipex);
void		init_struct(t_pipex *pipex, int argc, char **argv, char **envp);
void		redirection(t_pipex *pipex, int i);
int			pipex(int argc, char **argv, char **envp);

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
int			parsing(char *input);

//				syntax_error		//
int			pipe_in_first(char *input);
int			pipe_in_last(char *input, int i);
int			double_pipe(char *input);
int			redir_n_pipe(char *input);
int			check_token(char *input);

#endif
