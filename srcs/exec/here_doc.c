/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboudjel <lboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 22:35:45 by lboudjel          #+#    #+#             */
/*   Updated: 2024/05/09 18:27:21 by lboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	get_stop_word(t_heredoc *heredoc, t_token *token, char *str)
{
	int	nb;
	int	i;
	(void)str;
	i = 0;
	nb = 0;
	while (i < token->file_count)
	{
		if (token->redir_chevron[i] == 4)
		{
			heredoc[nb].stop_word = ft_strdup(token->files[i]);
			pipe(heredoc[nb++].hd_pipe);
		}
		i++;
	}
}

// static char	*open_here_doc(int i, t_pipex *pipex)
// {
// 	char	*str;
// 	char	prompt[100];

// 	if (ft_strlen(pipex->heredoc[i].stop_word) > 98)
// 		ft_strlcpy(prompt, pipex->heredoc[i].stop_word, 98);
// 	else
// 		ft_strcpy(prompt, pipex->heredoc[i].stop_word);
// 	ft_strcat(prompt, ">");
// 	while (1)
// 	{
// 		str = readline(prompt);
// 		if (!str || !ft_strcmp(str, pipex->heredoc[i].stop_word))
// 			break ;
// 		ft_putendl_fd(str, pipex->heredoc[i].hd_pipe[1]);
// 		free(str);
// 	}
// 	close(pipex->heredoc[i].hd_pipe[1]);
// 	close(pipex->heredoc[i].hd_pipe[0]);
// 	return (NULL);
// }

static char *open_here_doc(int i, t_pipex *pipex)
{
	char *line;

	while (1)
	{
		line = readline(">");
		if (!line || !ft_strcmp(line, pipex->heredoc[i].stop_word))
			break ;
		ft_putendl_fd(line, pipex->heredoc[i].hd_pipe[1]);
		free(line);
	}
	close(pipex->heredoc[i].hd_pipe[1]);
	close(pipex->heredoc[i].hd_pipe[0]);
	return (NULL);
}

static void	exit_hd(int sig)
{
	int		i;
	t_pipex	*pipex;

	pipex = starton();
	fprintf(stderr, "pipex->heredoc : %p\n", pipex->heredoc);
	if (sig == SIGINT)
	{
		ft_putchar_fd('\n', 2);
		i = -1;
		while (++i < pipex->nbr_heredoc)
		{
			fprintf(stderr, "is ok : %s\n", pipex->heredoc[i].stop_word);
			close(pipex->heredoc[i].hd_pipe[1]);
			close(pipex->heredoc[i].hd_pipe[0]);
			if (pipex->heredoc[i].stop_word != NULL)
				free(&pipex->heredoc[i].stop_word);
		}
		free(pipex->heredoc);
		free(pipex->path);
		free_token(pipex->token);
		free_lst(pipex->envp);
		exit(130);
	}
}

static void	child_hd(t_pipex *pipex, t_token *token, t_copyenv *lst_envp)
{
	int	i;

	signal(SIGINT, &exit_hd);
	i = -1;
	while (++i < pipex->nbr_heredoc)
		open_here_doc(i, pipex);
	free_heredoc(pipex);
	free(pipex->heredoc);
	free(pipex->path);
	free(pipex->prompt);
	free_token(token);
	free_lst(lst_envp);
	exit(1);
}

void	here_doc(t_pipex *pipex, t_token *token, t_copyenv *lst_envp, char *str)
{
	int		i;
	int		pid;

	i = 0;
	pipex->nbr_heredoc = count_here_doc(str);
	if (!pipex->nbr_heredoc)
		return ;
	pipex->heredoc = ft_calloc(sizeof(t_heredoc), pipex->nbr_heredoc);
	if (!pipex->heredoc)
		return ;
	get_stop_word(pipex->heredoc, token, str);
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == 0)
		child_hd(pipex, token, lst_envp);
	else if (pid > 0)
	{
		while (i < pipex->nbr_heredoc)
		{
			close(pipex->heredoc[i].hd_pipe[1]);
			i++;
		}
	}
	signal(SIGINT, &ctrl_c);
	waitpid(pid, NULL, 0);
}

