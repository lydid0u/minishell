/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboudjel <lboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 05:07:28 by lboudjel          #+#    #+#             */
/*   Updated: 2024/03/18 06:19:41 by lboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// /*
// 	    — env (with no options or arguments) :
// 	copie de l'env dans une liste chaine avec KEY et VALUE par node
// 	-->a utiliser pour pipex
// 	    — export (with no options) :
// 	ajoute une key + value a l'env
// 	    — unset (with no options)
// 	supprime une key + value de l'env  
// */

// /* 
// 	step 1 :
// - creer + initialiser ma liste chainee
// 	step 2 :
// */


// void	built_in_export(t_copyenv *copyenv)
// {
// 	t_copyenv *node_export;
//
// 	while (copyenv)
// 	{
// 		copyenv = copyenv->next;
// 	}
// 	copyenv->next = node_export;
// }