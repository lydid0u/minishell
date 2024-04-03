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


// INPUT : cat a | < b cat | cat > c | cat c
/*

	1) je prend ma string et je split au pipe
	2) je check dans la string si ya redirection > si oui, jouvre le fd/le cree tout ca
												>  si non, salam
	3) je dup2 le dernier


*/


void	redirection(t_pipex *pipex, int i)
{
	int	j;
	int	fd;

	j = 0;
	fd = 0;
	if (i != 0)
	{
		dup2(pipex->prev, 0);
		close(pipex->prev);
	}
	if (i != pipex->nbr_cmd - 1)
		dup2(pipex->fd[1], 1);
	pipex->redir = ft_split(pipex->arg_cmd[i], ' ');
	if (!pipex->redir)
		return;
	// t_mycmd  *parse(pipex->redir[i])
	// mycmd->cmd
	// mycmd->args
	// mycmd->filename
	// mycmd->types

	while (pipex->redir[j])
	{
		if (ft_strcmp(pipex->redir[j], ">>") == 0)
			fd = open(pipex->redir[j + 1], O_CREAT | O_RDWR | O_APPEND, 0666);
		else if (ft_strcmp(pipex->redir[j], ">") == 0)
			fd = open(pipex->redir[j + 1], O_CREAT | O_RDWR | O_TRUNC, 0666);
		// if (ft_strcmp(pipex->redir[j], "<") == 0)
		// {
		// 	// 
		// }
		// if (ft_strcmp(pipex->redir[j], "<<") == 0)
		// {
		// 	// here doc
		// }
		if (ft_strcmp(pipex->redir[j], ">>") == 0 || ft_strcmp(pipex->redir[j], ">") == 0)
		{
			dup2(fd, 1);
			close(fd);
		}
		j++;
	}
	free_tab(pipex->redir);
	// ici redirection de fichier avec dup2
}

//si c'est redire jouvre le fd
// boucler et fd = open sur chaque redirection et dup2 sur le dernier
//apres avoir fais les pipes 

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

// int	nbr_redir(char *input)
// {
// 	int i;
// 	int	count;
// 	char **tab;

// 	count =
// 	tab = ft_split(input, ' ');
// 	while (tab[i])
// 	{
// 		if (ft_strcmp(tab[i], ">") == 0)
// 			count++;
// 		if (ft_strcmp(tab[i], ">>") == 0)
// 			count = count + 2;
// 		if (ft_strcmp(tab[i], "<") == 0)
// 			return (3);
// 		if (ft_strcmp(tab[i], "<<") == 0)
// 			return (4);
// 	}
// 	free(tab);
// }


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
