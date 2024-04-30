/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboudjel <lboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 21:12:19 by lboudjel          #+#    #+#             */
/*   Updated: 2024/04/26 21:12:19 by lboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// strace -o /dev/pts/11 -f

#include "minishell.h"

// void	print_tokenexec(t_token *token)
// {
// 	fprintf(stderr, "PRINT TOKEN IN EXEC\n");
// 	fprintf(stderr, "Command: %s\n", token->cmd);
// 	for (int i = 1; i < token->arg_count; i++)
// 	{
// 		fprintf(stderr, "argument : %s\n", token->args[i]);
// 	}
// 	fprintf(stderr, "\n");
// 	for (int i = 0; i < token->file_count; i++)
// 	{
// 		fprintf(stderr, "Redirection: %d\n", token->redir_chevron[i]);
// 		fprintf(stderr, "File: %s\n", token->files[i]);
// 	}
// }


void	child(t_pipex *pipex, t_copyenv *lst_envp, int i)
{
	char	*path;

	signal(SIGINT, &ctrl_c);
	signal(SIGQUIT, &backslash);
	t_token (*mycmd) = tokenisation(pipex->cmd[i]);
	free(pipex->prompt);
	redirection(pipex, i);
	free_tab(pipex->cmd);
	if (handle_redirection(mycmd))
		return (free_all(pipex, lst_envp, mycmd), exit(1));
	if (!mycmd->cmd)
		return (free_all(pipex, lst_envp, mycmd), exit(127));
	if (handle_built_in_pipex(mycmd, pipex) == 0)
		return (free_all(pipex, lst_envp, mycmd), exit(0));
	else
	{
		path = access_cmd(pipex, mycmd);
		if (path)
			execve(path, mycmd->args, pipex->tab_env);
		free(path);
	}
	free_all(pipex, lst_envp, mycmd);
	return (exit(127));
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
	signal(SIGINT, &ctrl_c);
}

void	ft_waitpid(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->nbr_cmd)
	{
		waitpid(pipex->pid[i++], &pipex->status_code, 0);
		if (WIFEXITED(pipex->status_code))
			pipex->status_code = WEXITSTATUS(pipex->status_code);
	}
}

void	init_struct(t_pipex *pipex, int argc, char **argv, t_copyenv *lst_envp)
{
	pipex->envp = lst_envp;
	pipex->cmd = argv;
	pipex->nbr_cmd = argc;
}

int	exec(int argc, t_copyenv *lst_envp, t_pipex *pipex)
{
	init_struct(pipex, argc, pipex->cmd, lst_envp);
	piping_and_forking(pipex, lst_envp);
	close(pipex->fd[0]);
	return (1);
}
