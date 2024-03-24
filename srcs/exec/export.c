/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboudjel <lboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 05:07:28 by lboudjel          #+#    #+#             */
/*   Updated: 2024/03/24 04:20:41 by lboudjel         ###   ########.fr       */
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

// edge case : 
// rechecker pour le chiffre que en 1e 
// si USER= juste ecraser et reecrire USER=

// void	get_key()

int		export_key_already_exist(char *str, t_copyenv *head)
{
	int i;
	t_copyenv	*lst;

	lst = head;
	i = 0;
	while (head)
	{
		if (ft_strncmp(str, head->key, ft__strlen(head->key)) == 0)
		{
			i += ft__strlen(head->key);
			if ((str[i] != '='))
			{
				printf("\n \n CHAR {%c}\n\n", str[i]);
				break ;
			}
			i++;
			head->value = ft_strdup(&str[i]);
			printf("str : %s\n", head->value);
			while (lst)
				lst = lst->next;
			return (1);
			// return (1);
		}
		head = head->next;
	}
	return (0);
}

void	add_node_export_back(t_copyenv *lst, t_copyenv *new_node)
{	
	while (lst->next)
	{
		lst = lst->next;
	}
	lst->next = new_node;	
}

void	create_export_node(char *str, t_copyenv *head)
{
	int i;
	int j;
	int tmp;
	t_copyenv	*node_export;

	i = 0;
	j = 0;
	node_export = create_node();
	if (ft_strchr(str, '='))
		return ;
	while (str[i])
	{
		while (str[i] && str[i] != '=')
			i++;
		node_export->key = malloc((sizeof(char) * i) + 1);
		i = 0;
		while (str[i] && str[i] != '=')
			node_export->key[j++] = str[i++];
		node_export->key[j] = '\0';
		i++;
		tmp = i;
		int size = i;
		while (str[i])
			i++;
		size = i - size;
		node_export->value = malloc((sizeof(char) * size) + 1);
		j = 0;
		i = tmp;
		while (str[i])
			node_export->value[j++] = str[i++];
		node_export->value[j] = '\0';
		break;
	}
	add_node_export_back(head, node_export);
}
// *str			*ret
// [a][v][i][o][n][=][m][o][h][a]
// [=][m][o][h][a]
int wrong(char *str)
{
	int i = 0;

	char *ret = ft_strchr(str, '=');
	if (!ret)
		return (1);
	*ret = '\0';
	while ((str[i] && (ft_isalnum(str[i]) || str[i] == '_')))
		i++;
	printf("JE RETURN %i\n", str[i]);
	return (str[i] != 0);
}

void	built_in_export(char **args, t_copyenv *head)
{
	int i;
	// int status;

	i = 0;
	// status = 0;
	// if (args[i] == NULL)
	// 	export_only(head);
	while (args[i])
	{
		if (wrong(args[i]))
		{
			printf("WRONG ARG [%s]\n", args[i]);
			i++;
			continue;
		}
		if (export_key_already_exist(args[i], head))
		{
			i++;
			continue;
		}
		else
		{
			create_export_node(args[i], head);
			i++;
		}
		// if (parse(args[i]))
			// continue ;
	}
	// t_copyenv 	*lst = head;
	// while (lst != NULL)
	// {
	//     printf("%s=%s\n", lst->key, lst->value);
	//     lst = lst->next;
	// }
	// return (status);
}

// void	built_export(char *input)
// {
// 	int i;

// 	i = 0;
// 	while (input[i])
// 	{
// 		if (ft_strcmp(&input[i], "export") == 0)
// 		{
// 			i += 6;
// 			input[i] = '\0';
// 			printf("BUILT IN : {%s}\n", &input[i]);
// 		}
// 		i++;
// 	}
// }