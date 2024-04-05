/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboudjel <lboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 04:02:22 by lboudjel          #+#    #+#             */
/*   Updated: 2024/03/30 07:06:06 by lboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_a_redirection(char *str)
{
	if (ft_strcmp(str, ">") == 0)
		return (1);
	if (ft_strcmp(str, ">>") == 0)
		return (2);
	if (ft_strcmp(str, "<") == 0)
		return (3);
	if (ft_strcmp(str, "<<") == 0)
		return (4);
}

// void	tokenisation(char **tab, t_pipex *pipex)
// {
// 	int	i;

// 	i = 0;
// 	while (tab[i])
// 	{
// 		if (is_a_redirection(tab[i]) != 0)
// 			pipex->token->redir[pipex->token->r++] = tab[i];
// 		i++;
// 	}
// }

// 	// t_mycmd  *parse(pipex->redir[i])
	// mycmd->cmd
	// mycmd->args
	// mycmd->filename
	// mycmd->types
//

// 	redir[r++] = tab[i + 1]
// 	args[a++] = tab[i]

// void	looping(char *cmd)
// {
// 	int	i;
// 	int	nb_cmd;
// 	char	**args;

// 	i = 0;
// 	while (cmd[i])
// 	{

// 	}
// }

/*
boucler sur les cmd et en faire un tab d'args et des que je vois une redirection
je dis que ca va avec en faisant :

input : echo "oui" > a | cat Makefile 

devient : 

pipex.cmd[0] = echo "oui" > non
pipex.cmd[1] = cat Makefile 

et pipex.cmd[0] deviendra :

mot[0] = echo
mot[1] = oui
mot[2] = >
mot[3] = non

et j'affilie a '>' le fichier non en faisant mot[i + 1]
*/