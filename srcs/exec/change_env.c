/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboudjel <lboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 05:07:28 by lboudjel          #+#    #+#             */
/*   Updated: 2024/03/18 06:19:41 by lboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	copie de l'env dans une liste chaine avec KEY et VALUE par node
		-->a utiliser pour pipex :
	    — env (with no options or arguments)
	ajoute une key + value a l'env :
	    — export (with no options)
	supprime une key + value de l'env : 
	    — unset (with no options)
*/

// void	copy_envp(char **envp)
// {
// 	int i;
// 	int j;
// 	int k;
// 	int v;
// 	char *key;
// 	char *value;

// 	i = 0;
// 	j = 0;
// 	while (envp[i])
// 	{
// 		j = 0;
// 		while (envp[i][j])
// 		{
// 			key[k] = envp[i][j];
// 			k++;
// 			j++;
// 			if (envp[i][j] == '=')
// 			{
// 				j++;
// 				while (envp[i][j])
// 				{
// 					value[v] = envp[i][j];
// 					j++;
// 					v++;
// 				}
// 				printf("value {%s}\n", value);
// 			}
// 		}
		
// 		i++;
// 	}
	
// }