/* ************************************************************************** */
/*																			  */
/*														:::	  ::::::::   	  */
/*   redir_chevron.c									:+:	  :+:	:+:   	  */
/*													+:+ +:+		 +:+		  */
/*   By: lboudjel <lboudjel@student.42.fr>		  +#+  +:+	   +#+			  */
/*												+#+#+#+#+#+   +#+		   	  */
/*   Created: 2024/04/05 01:09:23 by lboudjel		  #+#	#+#			 	  */
/*   Updated: 2024/04/05 03:22:29 by lboudjel		 ###   ########.fr	      */
/*																			  */
/* ************************************************************************** */

#include "minishell.h"

/* Handle_redirection : gerer la redirection des fichiers si ya des chevrons :

je boucle sur le nombre de file qu'il ya et si je rencontre un chevron 
j'open et affilie dans fd, et je donne les droits/cree le file/les options etc
du file en question et je dup2 le stdin ou le stdout 

-> a la fin, la derniere redirection sera celle du dernier chevron et en bouclant
sur chacun des chevrons, on passe par chacun des files et on les cree bien tous

input : echo "salut" > a > b > c > d

ca va bien creer les files a, b, c et d mais lorsqu'on fera "cat" dessus
ils seront tous vides sauf d qui affichera "salut"
*/

int	handle_redirection(t_token *cmd)
{
	int (i) = 0;
	int (fd) = 0;
	while (i < cmd->file_count)
	{
		if (cmd->redir_chevron[i] == 1)
			fd = open(cmd->files[i], O_CREAT | O_RDWR | O_TRUNC, 0666);
		if (cmd->redir_chevron[i] == 2)
			fd = open(cmd->files[i], O_CREAT | O_RDWR | O_APPEND, 0666);
		if (cmd->redir_chevron[i] == 3)
			fd = open(cmd->files[i], O_RDONLY);
		// if (cmd->redir_chevron[i] == 4)
		// 	// heredoc
		if (fd == -1)
			return (perror(cmd->files[i]), 1);
		if (cmd->redir_chevron[i] == 1 || cmd->redir_chevron[i] == 2)
		{
			dup2(fd, 1);
			close(fd);
		}
		if (cmd->redir_chevron[i] == 3)
		{
			dup2(fd, 0);
			close(fd);
		}
		i++;
	}
	return (0);
}

/* Chevron_no_fork : gerer un built-in quand y a 1 seul cmd et pas de fork  :

je copie avec dup le fd stdin et stdout dans in & out pour les utiliser avec dup2
et pas "perdre" les vrais sorties vu que ya pas de fork et que tout se passe dans
le main process, puis je remet stdin et stdout a leur place avec dup2
*/

void	chevron_no_fork(t_pipex *pipex, t_token *token, t_copyenv *lst_envp)
{
	pipex->in = dup(0);
	pipex->out = dup(1);
	if (handle_redirection(token))
	{
		dup2(pipex->out, 1);
		dup2(pipex->in, 0);
		close(pipex->in);
		close(pipex->out);
		pipex->status_code = 1;
		return ;
	}
	pipex->status_code = handle_built_in_no_fork(pipex, token, lst_envp);
	dup2(pipex->out, 1);
	dup2(pipex->in, 0);
	close(pipex->in);
	close(pipex->out);
}
