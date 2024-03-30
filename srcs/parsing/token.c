/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboudjel <lboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 04:02:22 by lboudjel          #+#    #+#             */
/*   Updated: 2024/03/30 07:06:06 by lboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_a_redirection(char *str)
{
	if (ft_strcmp(str, ">") == 0)
		return (1);
	if (ft_strcmp(str, ">>") == 0)
		return (2);
	if (ft_strcmp(str, "<") == 0)
		return (3);
	if (ft_strcmp(str, "<<") == 0)
		return (4);
}

void	tokenisation(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		if (is_a_redirection(tab[i]) != 0)
			type[r] = is_a_redirection(tab[i]);
		i++;
	}
}
// 	redir[r++] = tab[i + 1]
// 	args[a++] = tab[i]