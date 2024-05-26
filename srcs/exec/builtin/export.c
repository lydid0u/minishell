/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboudjel <lboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 05:07:28 by lboudjel          #+#    #+#             */
/*   Updated: 2024/03/30 04:31:13 by lboudjel         ###   ########.fr       */
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
- step 1: parser la string et recup les infos (export + les args)
- step 1,5: si aucun args -> gerer le cas a part
- step 2: check si la KEY existe deja? si oui remplacer sa value dans le noeud 
- step 3: si elle existe pas: creer noeud et stocker la KEY et la VALUE dedans
- step 4: ajouter le noeud a la fin
*/

int	export_key_already_existing(char *key, char *str, t_copyenv *head)
{
	int	i;

	i = 0;
	while (head)
	{
		if (ft_strcmp(key, head->key) == 0)
		{
			i += ft_strlen(head->key);
			if (str[i] != '=')
				break ;
			i++;
			free(head->value);
			head->value = ft_strdup(&str[i]);
			return (1);
		}
		head = head->next;
	}
	return (0);
}

int	create_export_node(char *str, t_copyenv **head)
{
	int (i) = 0;
	int (j) = 0;
	t_copyenv *(node_export) = create_node();
	char *(key) = get_key(str);
	if (!key)
		return (1);
	while (str[i])
	{
		node_export->key = key;
		i += (ft_strlen(key) + 1);
		if (str[i - 1] != '=')
		{
			free(node_export);
			free(key);
			return (0);
		}
		node_export->value = malloc((sizeof(char) * ft_strlen(&str[i])) + 1);
		if (!node_export)
			return (1);
		while (str[i])
			node_export->value[j++] = str[i++];
		node_export->value[j] = '\0';
	}
	add_node_export_back(head, node_export);
	return (0);
}

// *str			*ret
// [a][v][i][o][n][=][m][o][h][a]
// [=][m][o][h][a]
int	wrong_args(char *str)
{
	int		i;

	i = 0;
	if (isdigit(str[0]))
		return (1);
	while (str[i])
	{
		if (str[i] == '=')
			break ;
		if (!ft_isalnum(str[i]) && str[i] != '_' && str[i] != '?')
			return (1);
		i++;
	}
	return (0);
}

/*
export return status

{export hello} = 0
{export A-} = 1
{export HELLO=123 A} = 0
{export hello world} = 0
{export HELLO-=123} = 1
{export =} = 1
export 123 = 1

-->
key invalid = 1
pas de value = 0
2 value = 0

good()
{
	return c is AlphaNumeric || c is _
}


si !good(str) avant le =
	status error
si pas de =
	status ok

*/

int	bt_export_loop_to_create_node(char *arg, t_copyenv **head)
{
	char	*key;

	key = get_key(arg);
	if (!key)
		return (ft_printf("%s: not a valid identifier\n", arg), 1);
	if (export_key_already_existing(key, arg, *head))
	{
		free(key);
		return (0);
	}
	create_export_node(arg, head);
	free(key);
	return (0);
}

int	built_in_export(char **args, t_copyenv **head)
{
	int	i;

	i = 0;
	int (status) = 0;
	int (error) = 0;
	while (args[i])
	{
		status = bt_export_loop_to_create_node(args[i], head);
		if (status)
			error = 1;
		i++;
	}
	return (error);
}
