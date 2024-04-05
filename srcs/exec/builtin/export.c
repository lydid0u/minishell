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

// edge case :
// rechecker pour le chiffre que en 1e
// FIXE LE CAS DE =B
// petit leaks a fix encore

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
			head->value = ft_strdup(&str[i]);
			return (1);
		}
		head = head->next;
	}
	return (0);
}

int	create_export_node(char *str, t_copyenv *head)
{
	int			i;
	int			j;
	t_copyenv	*node_export;
	char		*key;

	i = 0;
	j = 0;
	node_export = create_node();
	key = get_key(str);
	if (!key)
		return (1);
	while (str[i])
	{
		node_export->key = key;
		i += (ft_strlen(key) + 1);
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

int	wrong(char *str)
{
	int		i;
	char	*ret;

	i = 0;
	ret = ft_strchr(str, '=');
	if (!ret)
		return (1);
	*ret = '\0';
	while ((str[i] && (ft_isalnum(str[i]) || str[i] == '_')))
		i++;
	*ret = '=';
	return (str[i] != '=');
}

void	bt_export_loop_to_create_node(char *arg, t_copyenv *head)
{
	char	*key;

	key = get_key(arg);
	if (!key)
		return ;
	if (wrong(arg))
	{
		printf("WRONG ARG [%s]\n", arg);
		return ;
	}
	if (export_key_already_existing(key, arg, head))
		return ;
	create_export_node(arg, head);
	free(key);
}

void	built_in_export(char **args, t_copyenv *head)
{
	int	i;

	i = 0;
	while (args[i])
	{
		bt_export_loop_to_create_node(args[i], head);
		i++;
	}
}
