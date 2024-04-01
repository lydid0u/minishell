/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboudjel <lboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 18:20:13 by lboudjel          #+#    #+#             */
/*   Updated: 2024/03/30 07:05:47 by lboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// strace -o /dev/pts/11 -f

#include "minishell.h"

void	redirection(t_pipex *pipex, int i)
{
	if (i != 0)
	{
		dup2(pipex->prev, 0);
		close(pipex->prev);
	}
	if (i != pipex->nbr_cmd - 1)
		dup2(pipex->fd[1], 1);
}

// void	redirection_chevron(t_pipex *pipex, int i)
// {

// 	//while (nbr de infile)
// 	//open & check
// 	//dup2

// 	//while (nbr de outfile)
// 	//open & check
// 	//dup2

// }
	// redirection_chevron(pipex, i);

void	child(t_pipex *pipex, int i)
{
	char	*path;

	free(pipex->prompt);
	redirection(pipex, i);
	close(pipex->fd[0]);
	close(pipex->fd[1]);
	if (handle_built_in_pipex(pipex, i) == 0)
		return (free_tab(pipex->cmd), exit(1));
	else 
	{
		pipex->tab_cmd = ft_split(pipex->arg_cmd[i], ' ');
		if (!pipex->tab_cmd)
			return (free_tab(pipex->tab_cmd));
		path = access_cmd(pipex, 0);
		if (path)
			execve(path, pipex->tab_cmd, NULL);
	}
	free_tab(pipex->cmd);
	return (free(path), free_tab(pipex->tab_cmd), exit(1));
}
	// if(!pipex->tab_cmd[0])
	// return (free_tab(pipex->tab_cmd));

void	piping_and_forking(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->nbr_cmd)
	{
		if (pipe(pipex->fd) == -1)
			return (ft_printf("Error: pipe function\n"), exit(EXIT_FAILURE));
		pipex->pid[i] = fork();
		if (pipex->pid[i] == -1)
			return (ft_printf("Error: fork function\n"), exit(EXIT_FAILURE));
		if (pipex->pid[i] == 0)
			child(pipex, i);
		else
		{
			close(pipex->fd[1]);
			if (i != 0)
				close(pipex->prev);
			pipex->prev = pipex->fd[0];
		}
		i++;
	}
	i = 0;
	while (i < pipex->nbr_cmd)
		waitpid(pipex->pid[i++], NULL, 0);
}

	//recup les infiles
	//recup les outfiles
void	init_struct(t_pipex *pipex, int argc, char **argv, t_copyenv *lst_envp)
{
	pipex->envp = lst_envp;
	pipex->arg_cmd = argv;
	pipex->nbr_cmd = argc;
}

int	exec(int argc, t_copyenv *lst_envp, t_pipex *pipex)
{
	init_struct(pipex, argc, pipex->cmd, lst_envp);
	piping_and_forking(pipex);
	close(pipex->fd[0]);
	return (1);
}
// free_tab(pipex.tab_cmd);
