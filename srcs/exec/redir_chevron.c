/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   redir_chevron.c									:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: lboudjel <lboudjel@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/04/05 01:09:23 by lboudjel		  #+#	#+#			 */
/*   Updated: 2024/04/05 03:22:29 by lboudjel		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "minishell.h"

//si c'est redire jouvre le fd
// boucler et fd = open sur chaque redirection et dup2 sur le dernier
//apres avoir fais les pipes

void	handle_redirection(char **redir)
{
	int	i;
	int	fd;

	i = 0;
	fd = 0;
	while (redir[i])
	{
		if (ft_strcmp(redir[i], ">>") == 0)
			fd = open(redir[i + 1], O_CREAT | O_RDWR | O_APPEND, 0666);
		if (ft_strcmp(redir[i], ">") == 0)
			fd = open(redir[i + 1], O_CREAT | O_RDWR | O_TRUNC, 0666);
		if (ft_strcmp(redir[i], "<") == 0)
			fd = open(redir[i + 1], O_RDONLY);
		if (ft_strcmp(redir[i], ">>") == 0 || ft_strcmp(redir[i], ">") == 0)
		{
			dup2(fd, 1);
			close(fd);
		}
		if (ft_strcmp(redir[i], "<") == 0)
		{
			dup2(fd, 0);
			close(fd);
		}
		i++;
	}
}

void	chevron(t_pipex *pipex, int i)
{
	pipex->redir = ft_split(pipex->arg_cmd[i], ' ');
	if (!pipex->redir)
		return ;
	handle_redirection(pipex->redir);
	free_tab(pipex->redir);
}


// if (ft_strcmp(redir[i], "<<") == 0)
	//heredoc

void	handle_redirection_no_exec(char **redir, int entree, int sortie)
{
	(void)entree;
	(void)sortie;
	int	fd;
	int	i;

	i = 0;
	fd = 0;
	while (redir[i])
	{
		if (ft_strcmp(redir[i], ">>") == 0)
			fd = open(redir[i + 1], O_CREAT | O_RDWR | O_APPEND, 0666);
		if (ft_strcmp(redir[i], ">") == 0)
			fd = open(redir[i + 1], O_CREAT | O_RDWR | O_TRUNC, 0666);
		if (ft_strcmp(redir[i], "<") == 0)
			fd = open(redir[i + 1], O_RDONLY);
		if (ft_strcmp(redir[i], ">>") == 0 || ft_strcmp(redir[i], ">") == 0)
		{
			dup2(fd, 1);
			close(fd);
		}
		if (ft_strcmp(redir[i], "<") == 0)
		{
			dup2(fd, 0);
			close(fd);
		}
		i++;
	}
}

void	chevron_no_exec(t_pipex *pipex, t_copyenv *lst_envp)
{
	int	entree;
	int	sortie;

	entree = dup(0);
	sortie = dup(1);
	pipex->redir = ft_split(pipex->cmd[0], ' ');
	if (!pipex->redir)
		return ;
	handle_redirection_no_exec(pipex->redir, entree, sortie);
	handle_built_in_no_exec(pipex, lst_envp);
	dup2(sortie,1);
	dup2(entree,0);
	close(entree);
	close(sortie);
	free_tab(pipex->redir);
}

// 	fprintf(stderr, " ca pue sa mere \n");
//5410938E