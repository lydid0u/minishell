/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboudjel <lboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 20:29:05 by lboudjel          #+#    #+#             */
/*   Updated: 2024/04/30 20:29:05 by lboudjel         ###   ########.fr       */
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

/* alloc_token_struct : allouer la memoire pour ma structure de token

Je boucle et j'incremente mes int de chaque type pour la taille de l'alloc
*/

t_token	*alloc_token_struct(char **tab)
{
	t_token *(token) = malloc(sizeof(t_token));
	int (i) = 0;
	int (redir) = 0;
	int (args) = 0;
	while (tab[i])
	{
		if (is_a_redirection(tab[i]))
			redir++;
		else
			args++;
		i++;
	}
	token->i = 0;
	token->a = 0;
	token->r = 0;
	token->args = ft_calloc(sizeof(char *), args + 1);
	token->files = ft_calloc(sizeof(char *), redir + 1);
	token->redir_chevron = ft_calloc(sizeof(int), redir + 1);
	return (token);
}

/* tokenisation : boucler sur ma cmd et donner un "type" a chacun des mots

Dans mon input, chaque mot est soit : la commande, l'argument de la cdm, un file

Le 1e mot est forcement la cmd et le mot apres une redir est forcement un file
--> les autres mots sont donc les arguments de la commande

Je split mon input et je stock chaque mot dans le tab qui lui correspond
et j'affilie a ma redir le fichier qui lui correspond avec tab[i + 1]

input : echo a > d b > e c

token->cmd = "echo";
token->args[0] = "a";
token->redir_chevron[0] = 1; (le int 1 = '>')
token->files[0] = "d";
token->args[1] = "b";
token->redir_chevron[1] = 1;
token->files[1] = "e";
token->args[2] = "c";

le fichier d sera vide et le fichier e affichera "a b c"
*/

t_token	*tokenisation(char *input)
{
	char **(tab) = ft_split_v2(input);
	t_token *(tok) = alloc_token_struct(tab);
	while (tab[tok->i])
	{
		if (is_a_redirection(tab[tok->i]))
		{
			tok->redir_chevron[tok->r] = is_a_redirection(tab[tok->i]);
			tok->i++;
			if (tab[tok->i])
			{
				tok->files[tok->r] = suppresing_quote(ft_strdup(tab[tok->i]));
				quote_positif(tok->files[tok->r++]);
			}
		}
		else
		{
			tok->args[tok->a] = suppresing_quote(ft_strdup(tab[tok->i]));
			quote_positif(tok->args[tok->a++]);
		}
		if (tab[tok->i])
			tok->i++;
	}
	tok->cmd = tok->args[0];
	tok->arg_count = tok->a;
	return (tok->file_count = tok->r, free_tab(tab), tok);
}

/*
void	print_tokenexec(t_token *token)
{
	printf("PRINT TOKEN IN EXEC\n");
	printf("Command: %s\n", token->cmd);
	for (int i = 0; i < token->arg_count; i++)
	{
		printf("argument : %s\n", token->args[i]);
	}
	printf("\n");
	for (int i = 0; i < token->file_count; i++)
	{
		printf("Redirection: %d\n", token->redir_chevron[i]);
		printf("File: %s\n", token->files[i]);
	}
}
*/
