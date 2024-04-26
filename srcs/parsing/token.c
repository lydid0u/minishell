/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: lboudjel <lboudjel@student.42.fr>          +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
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

t_token	*allocstruct(char **tab)
{
	t_token *tok = malloc(sizeof(t_token));
	int(i) = 0;
	int(r) = 0;
	int(a) = 0;

	while (tab[i])
	{
		if (is_a_redirection(tab[i]))
		{
			r++;
			i++;
		}
		else
			a++;
		i++;
	}
	tok->tabargs = ft_calloc(sizeof(char *), a + 1);
	tok->tabfiles = ft_calloc(sizeof(char *), r + 1);
	tok->tabredir = ft_calloc(sizeof(int), r + 1);
	return (tok);
}

t_token	*tokenisation(char *input)
{
	t_token *token;

	int r = 0;
	int a = 0;
	char **tab = ft_split_v2(input);
	token = allocstruct(tab);

	int i = 0;
	while (tab[i])
	{
		if (is_a_redirection(tab[i]))
		{
			token->tabredir[r] = is_a_redirection(tab[i++]);
			token->tabfiles[r] = suppresing_quote(ft_strdup(tab[i]));
			quote_positif(token->tabfiles[r++]);
		}
		else
		{
			token->tabargs[a] = suppresing_quote(ft_strdup(tab[i]));
			quote_positif(token->tabargs[a++]);
		}
		i++;
	}
	free_tab(tab);
	token->cmd = token->tabargs[0];
	token->arg_count = a;
	token->file_count = r;

#if DEBUG
	print_tokenexec(token);
#endif


	return (token);
}

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