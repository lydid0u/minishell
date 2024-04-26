/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboudjel <lboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 21:39:55 by lboudjel          #+#    #+#             */
/*   Updated: 2024/04/26 21:41:09 by lboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	free_all(t_copyenv *lst_envp, t_token *tok)
{
	free_lst(lst_envp);
	free_token(tok);
}

void free_token(t_token *token)
{
	int i;
	
	i = 0;
	while (i < token->arg_count)
	{
		free(token->tabargs[i]);
		i++;
	}
	i = 0;
	while (i < token->file_count)
	{
		free(token->tabfiles[i]);
		i++;
	}
	free(token->tabargs);
	free(token->tabfiles);
	free(token->tabredir);
	free(token); 
}
