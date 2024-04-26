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

int	handle_redirection(t_token *cmd)
{
	int (i) = 0;
	int (fd) = 0;
	while (i < cmd->file_count)
	{
		if (cmd->tabredir[i] == 1)
			fd = open(cmd->tabfiles[i], O_CREAT | O_RDWR | O_APPEND, 0666);
		if (cmd->tabredir[i] == 2)
			fd = open(cmd->tabfiles[i], O_CREAT | O_RDWR | O_TRUNC, 0666);
		if (cmd->tabredir[i] == 3)
			fd = open(cmd->tabfiles[i], O_RDONLY);
		if (fd == -1)
			return (perror(cmd->tabfiles[i]), 1);
		if (cmd->tabredir[i] == 1 || cmd->tabredir[i] == 2)
		{
			dup2(fd, 1);
			close(fd);
		}
		if (cmd->tabredir[i] == 3)
		{
			dup2(fd, 0);
			close(fd);
		}
		i++;
	}
	return (0);
}

// if (ft_strcmp(redir[i], "<<") == 0)
	//heredoc

void	chevron_no_exec(t_pipex *pipex, t_token *token, t_copyenv *lst_envp)
{
	int	entree;
	int	sortie;
// #if DEBUG 
// 	printf("executing builtion no fork!!!!\n");
// #endif
	entree = dup(0);
	sortie = dup(1);
	if (handle_redirection(token))
	{
		dup2(sortie, 1);
		dup2(entree, 0);
		close(entree);
		close(sortie);
		pipex->status_code = 1;
		return ;
	}
	pipex->status_code = handle_built_in_no_exec(pipex, token, lst_envp);
	dup2(sortie, 1);
	dup2(entree, 0);
	close(entree);
	close(sortie);
}
