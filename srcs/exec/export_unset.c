/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboudjel <lboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 05:07:28 by lboudjel          #+#    #+#             */
/*   Updated: 2024/03/21 04:07:38 by lboudjel         ###   ########.fr       */
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

void		parsing_export(char *str, t_copyenv *lst)
{
	int i;
	t_copyenv	*node_export;
	
	i = 0;
	node_export = create_node();
	while (lst)
	{
		printf("str : {%s} key : {%s}\n", str, lst->key);
		if (ft_strncmp(str, lst->key, ft__strlen(lst->key)) == 0)
		{
			printf("ls\n");
			node_export->key = malloc(ft__strlen(lst->key) + 1);
			strncpy(node_export->key, lst->key, ft__strlen(lst->key) + 1);
			printf("key export {%s} key {%s} \n", node_export->key, lst->key);
			i += ft__strlen(lst->key) + 1;
			node_export->value = malloc(ft__strlen(lst->value) + 1); //la len est fausse -> a fix
			strncpy(node_export->value, &str[i], ft__strlen(lst->key) + 1);
			printf("value export {%s}\n", node_export->value);
		}
		lst = lst->next;
	}
}

void	built_in_export(char **args, t_copyenv *lst) //t_pipex *pipex
{
	int i;
	// int status;

	i = 0;
	// status = 0;
	// if (args[i] == NULL)
	// 	export_only(lst);
	while (args[i])
	{
		printf("argument : {%s}\n", args[i]);
		parsing_export(args[i], lst);
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