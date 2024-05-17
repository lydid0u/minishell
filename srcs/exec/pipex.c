/* ************************************************************************** */
/*		                                                                    */
/*                                                        :::      ::::::::   */
/*   pipex.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboudjel <lboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 21:12:19 by lboudjel          #+#    #+#             */
/*   Updated: 2024/04/26 21:12:19 by lboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// strace -o /dev/pts/11 -f

#include "minishell.h"

/* child : 
si ya un pb avec le fd de redir, si pas de cmd ou si la cmd est un builtin
	-> on free et on exit avec le bon exit status
sinon, on recup le path de la cmd et on execute
*/

void	free_n_redir_child(t_pipex *pipex, int i)
{
	free(pipex->prompt);
	free_tab(pipex->cmd);
	redirection(pipex, i);
}

void	child(t_pipex *pipex, t_copyenv *lst_envp, int i)
{
	char *(path);
	int (status_exit);
	int (flag) = 0;
	t_token (*token) = tokenisation(pipex->cmd[i]);
	free_n_redir_child(pipex, i);
	if (handle_redirection(token, pipex->heredoc, pipex))
		return (free_all(pipex, lst_envp, token), exit(1));
	if (!token->cmd)
		return (free_all(pipex, lst_envp, token), exit(127));
	if (handle_built_in_pipex(token, pipex, lst_envp) == 0)
		return (free_all(pipex, lst_envp, token), exit(0));
	else
	{
		pipex->tab_env = copy_env_to_tab(lst_envp);
		path = access_cmd(pipex, token, &flag);
		if (path)
			execve(path, token->args, pipex->tab_env);
		free(path);
	}
	status_exit = 127;
	if (flag != 1)
		status_exit = ft_status(token);
	return (free_all(pipex, lst_envp, token), exit(status_exit));
}

void	piping_and_forking(t_pipex *pipex, t_copyenv *lst_envp)
{
	int (i) = 0;
	while (i < pipex->nbr_cmd)
	{
		if (pipe(pipex->fd) == -1)
			return (ft_printf("Error: pipe function\n"), exit(EXIT_FAILURE));
		signal(SIGINT, SIG_IGN);
		pipex->pid[i] = fork();
		if (pipex->pid[i] == -1)
			return (ft_printf("Error: fork function\n"), exit(EXIT_FAILURE));
		if (pipex->pid[i] == 0)
			child(pipex, lst_envp, i);
		else
		{
			close(pipex->fd[1]);
			if (i != 0)
				close(pipex->prev);
			pipex->prev = pipex->fd[0];
			signal(SIGQUIT, SIG_IGN);
		}
		i++;
	}
	ft_waitpid(pipex);
	close_heredoc(pipex);
	signal(SIGINT, &ctrl_c);
}

/* ft_waitpid : 

on attend le retour du pid de chacun des child 
+ on recupere a la sortie les status code grace au syscall exit() 
*/

void	ft_waitpid(t_pipex *pipex)
{
	int (i) = 0;
	int (flag) = 0;
	while (i < pipex->nbr_cmd)
	{
		waitpid(pipex->pid[i++], &pipex->status_code, 0);
		if (WIFEXITED(pipex->status_code))
			pipex->status_code = WEXITSTATUS(pipex->status_code);
		if (WTERMSIG(pipex->status_code) == 2)
			ft_printf("\n");
		else if (WIFSIGNALED(pipex->status_code)
			&& WTERMSIG(pipex->status_code) == SIGQUIT)
		{
			if (!flag)
			{
				flag = 1;
				ft_printf("Quit (core dumped)\n");
			}
		}
	}
}

int	exec(t_copyenv *lst_envp, t_pipex *pipex)
{
	pipex->envp = lst_envp;
	piping_and_forking(pipex, lst_envp);
	close(pipex->fd[0]);
	return (1);
}
