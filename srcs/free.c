/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboudjel <lboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 21:39:55 by lboudjel          #+#    #+#             */
/*   Updated: 2024/04/29 18:16:13 by lboudjel         ###   ########.fr       */
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

void	free_lst(t_copyenv *lst)
{
	t_copyenv	*current;
	t_copyenv	*nxt;

	current = lst;
	while (current)
	{
		nxt = current->next;
		free(current->key);
		free(current->value);
		free(current);
		current = nxt;
	}
}

void	free_all(t_pipex *pipex, t_copyenv *lst_envp, t_token *tok)
{
	free_lst(lst_envp);
	free_tab(pipex->tab_env);
	free_token(tok);
}

void	free_token(t_token *token)
{
	int	i;

	i = 0;
	while (i < token->arg_count)
	{
		free(token->args[i]);
		i++;
	}
	i = 0;
	while (i < token->file_count)
	{
		free(token->files[i]);
		i++;
	}
	free(token->args);
	free(token->files);
	free(token->redir_chevron);
	free(token);
}
