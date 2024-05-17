/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboudjel <lboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 22:35:45 by lboudjel          #+#    #+#             */
/*   Updated: 2024/05/17 04:35:16 by lboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	get_stop_word(t_heredoc *heredoc, t_token *token, char *str)
{
	int	nb;
	int	i;

	i = 0;
	nb = 0;
	(void)token;
	while (str[i])
	{
		if (str[i] == '<')
		{
			i++;
			if (str[i] == '<')
			{
				i++;
				heredoc[nb].stop_word = get_word(&str[i]);
				pipe(heredoc[nb++].hd_pipe);
			}
		}
		i++;
	}
}

static char	*open_here_doc(int i, t_pipex *pipex)
{
	char	*line;

	while (1)
	{
		line = readline(">");
		if (!line || !ft_strcmp(line, pipex->heredoc[i].stop_word))
		{
			printf("bash: warning: here-document at line 0 delimited by end-of-file (wanted `%s')", pipex->heredoc[i].stop_word);
			break ;
		}
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
	if (sig == SIGINT)
	{
		ft_putchar_fd('\n', 2);
		i = -1;
		while (++i < pipex->nbr_heredoc)
		{
			close(pipex->heredoc[i].hd_pipe[1]);
			close(pipex->heredoc[i].hd_pipe[0]);
			if (pipex->heredoc[i].stop_word != NULL)
				free(pipex->heredoc[i].stop_word);
		}
		free(pipex->heredoc);
		free(pipex->path);
		free(pipex->prompt);
		free_lst(pipex->envp);
		exit(130);
	}
}

static void	child_hd(t_pipex *pipex, t_copyenv *lst_envp)
{
	int	i;

	signal(SIGINT, &exit_hd);
	free_tab(pipex->cmd);
	i = -1;
	while (++i < pipex->nbr_heredoc)
		open_here_doc(i, pipex);
	free_heredoc(pipex);
	free(pipex->path);
	free(pipex->prompt);
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
		child_hd(pipex, lst_envp);
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
