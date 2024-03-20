/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboudjel <lboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 05:07:28 by lboudjel          #+#    #+#             */
/*   Updated: 2024/03/20 03:57:14 by lboudjel         ###   ########.fr       */
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

	- step 1 : parser la string et recup les infos (export + les args)

	- step 1,5 : si aucun args -> gerer le cas a part

	- step 2 : checker est-ce que la KEY existe deja ? si oui remplacer sa value dans le noeud 

	- step 3 : si elle existe pas : creer un noeud et stocker la KEY et la VALUE dedans

	- step 4 : ajouter le noeud a la fin
*/

// int		parsing_export(char **args)
// {
	
// }

void	export_only(t_copyenv *head)
{
	int i;
	int j;
	int alpha;
	char lettre;
	t_copyenv *current;
	
	current = head;
	lettre = 'A';
	alpha = 0;
	while (alpha < 26)
	{
		while (current)
		{
			i = 0;
			j = 0;
			if (lettre == current->key[0] && current->written == 0)
			{
				current->written = 1;
				printf("export %s=\"%s\"\n", current->key, current->value);
			}
			current = current->next;
		}
		current = head;
		lettre++;
		alpha++;
	}
}

void	built_in_export(char **args, t_copyenv *lst) //t_pipex *pipex
{
	int i;
	// int status;

	i = 0;
	// status = 0;
	if (args[i] == NULL)
		export_only(lst);
	while (args[i])
	{
		printf("argument : {%s}\n", args[i]);
		// if (parse(args[i]))
			// continue ;
		// export_value(args[i])
		i++;
	}
	// return (status);
}

void	built_export(char *input)
{
	int i;

	i = 0;
	while (input[i])
	{
		if (ft_strcmp(&input[i], "export") == 0)
		{
			i += 6;
			input[i] = '\0';
			printf("BUILT IN : {%s}\n", &input[i]);
		}
		i++;
	}
}

// void	node_export(t_copyenv *lst, t_copyenv *new_node)
// {
// 	t_copyenv *node_export;
	
// 	while (lst)
// 	{
// 		lst = lst->next;
// 	}
// 	lst->next = node_export;	
// }