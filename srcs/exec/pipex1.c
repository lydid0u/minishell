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

// INPUT : cat a | < b cat | cat > c | cat c
/*

	1) je prend ma string et je split au pipe
	2) je check dans la string si ya redirection > si oui,
	jouvre le fd/le cree tout ca
	>  si non, salam
	3) je dup2 le dernier
*/

// void	print_tokenexec(t_token *token)
// {
// 	fprintf(stderr, "PRINT TOKEN IN EXEC\n");
// 	fprintf(stderr, "Command: %s\n", token->cmd);
// 	for (int i = 1; i < token->arg_count; i++)
// 	{
// 		fprintf(stderr, "argument : %s\n", token->tabargs[i]);
// 	}
// 	fprintf(stderr, "\n");
// 	for (int i = 0; i < token->file_count; i++)
// 	{
// 		fprintf(stderr, "Redirection: %d\n", token->tabredir[i]);
// 		fprintf(stderr, "File: %s\n", token->tabfiles[i]);
// 	}
// }

void	child(t_pipex *pipex, t_copyenv *lst_envp, int i)
{
	char	*path;

	t_token (*mycmd) = tokenisation(pipex->arg_cmd[i]);
	free(pipex->prompt);
	redirection(pipex, i);
	free_tab(pipex->arg_cmd);
	if (handle_redirection(mycmd))
		return (free_all(lst_envp, mycmd), exit(1));
	if (!mycmd->cmd)
	{
		ft_printf("cmd not found\n");
		free_all(lst_envp, mycmd);
		return (exit(127));
	}
	if (handle_built_in_pipex(mycmd, pipex) == 0)
		return (free_all(lst_envp, mycmd), exit(0));
	else
	{
		path = access_cmd(pipex, mycmd);
		if (path)
			execve(path, mycmd->tabargs, NULL);
		free(path);
	}
	free_all(lst_envp, mycmd);
	return (exit(127));
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

void	piping_and_forking(t_pipex *pipex, t_copyenv *lst_envp)
{
	int (i) = 0;
	while (i < pipex->nbr_cmd)
	{
		if (pipe(pipex->fd) == -1)
			return (ft_printf("Error: pipe function\n"), exit(EXIT_FAILURE));
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
		}
		i++;
	}
	ft_waitpid(pipex);
}

void	init_struct(t_pipex *pipex, int argc, char **argv, t_copyenv *lst_envp)
{
	pipex->envp = lst_envp;
	pipex->arg_cmd = argv;
	pipex->nbr_cmd = argc;
}

int	exec(int argc, t_copyenv *lst_envp, t_pipex *pipex)
{
	init_struct(pipex, argc, pipex->arg_cmd, lst_envp);
	piping_and_forking(pipex, lst_envp);
	close(pipex->fd[0]);
	return (1);
}
