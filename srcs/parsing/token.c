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
	else
		return (0);
}

void tokenisation(char *input, t_pipex *pipex) 
{
    char **tab;
    int flag;
    int redir;
    int i;

    if (!pipex->token) 
    {
        pipex->token = malloc(sizeof(t_token));
        if (!pipex->token)
            return;
    }
	i = 0;
	flag = 0;
    tab = ft_split_v2(input);
    if (!tab)
        return ;
    pipex->token->arg_count = 0;
    pipex->token->file_count = 0;
	redir = 0;
    while (tab[i]) 
    {
        redir = is_a_redirection(tab[i]);
        if (redir != 0) 
        {
            pipex->token->redir[pipex->token->file_count] = redir;
            pipex->token->files[pipex->token->file_count] = ft_strdup(tab[i + 1]);
            pipex->token->file_count++;
            i+=2;
            continue;
        } 
        else // savoir si ya une quote dans ma string et passer
        {
            if (flag == 0)
            {
                pipex->token->cmd = ft_strdup(tab[i]);
                pipex->token->cmd = suppresing_quote(pipex->token->cmd);
                quote_positif(pipex->token->cmd);
                flag = 1;
            }
            else
            {
                pipex->token->args[pipex->token->arg_count] = ft_strdup(tab[i]);
                pipex->token->args[pipex->token->arg_count] = suppresing_quote(pipex->token->args[pipex->token->arg_count]);
                quote_positif(pipex->token->args[pipex->token->arg_count]);
                pipex->token->arg_count++;
            }
        }
        i++;
    }
	printf("files %d args %d\n", pipex->token->file_count, pipex->token->arg_count);

	free_tab(tab);
}

// >> ?
//------------------------------------------------------------------//
// 	// t_mycmd  *parse(pipex->redir[i])
	// mycmd->cmd
	// mycmd->args
	// mycmd->filename
	// mycmd->types
//

// 	redir[r++] = tab[i + 1]
// 	args[a++] = tab[i]
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

// e"cho|hola"
// echo hola