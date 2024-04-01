/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboudjel <lboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 22:11:53 by lboudjel          #+#    #+#             */
/*   Updated: 2024/03/25 04:14:16 by lboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*		
		— env (with no options or arguments) :
			copie de l'env dans une liste chaine avec KEY et VALUE par node
			-->a utiliser pour pipex
		 
		— export (with no options) :
			ajoute une key + value a l'env
		 
		— unset (with no options)
			supprime une key + value de l'env  

		export :

	- step 1 : parser la string et recup les infos (unset + les args) OK

	- step 2 : checker est-ce que la KEY existe ? OK

	- step 3 : supprimer le noeud
*/
int	parsing_unset(char *str, t_copyenv *head)
{
	t_copyenv	*lst;
	t_copyenv	*prev;

	lst = head;
	while (lst)
	{
		if (ft_strcmp(str, lst->key) == 0)
		{
			if (prev)
				prev->next = lst->next;
			else
				head = lst->next;
			free(lst);
			lst = NULL;
		}
		prev = lst;
		if (lst)
			lst = lst->next;
	}
	return (0);
}

void	built_in_unset(char **args, t_copyenv *lst)
{
	int	i;

	i = 0;
	while (args[i])
	{
		parsing_unset(args[i], lst);
		i++;
	}
}
