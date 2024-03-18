/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboudjel <lboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 05:20:48 by lboudjel          #+#    #+#             */
/*   Updated: 2024/03/18 05:21:39 by lboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_single_quote(char *input, int *i, int *count)
{
	if (input[*i] && input[*i] == '\'')
	{
		(*i)++;
		(*count)++;
		while (input[*i] && input[*i] != '\'')
		{
			(*i)++;
			(*count)++;
		}
	}
}

void	write_single_quote(char *input, char *output, int *i, int *j)
{
	if (input[*i] && input[*i] == '\'')
	{
		output[*j] = input[*i];
		(*i)++;
		(*j)++;
		while (input[*i] && input[*i] != '\'')
		{
			output[*j] = input[*i];
			(*i)++;
			(*j)++;
		}
	}
}

int	is_key_valid(char *key, char **envp)
{
	int	i;
	int	len;

	i = 0;
	len = get_len_of_key(&key[i]);
	while (envp[i])
	{
		if (ft_strncmp(key, envp[i], len) == 0)
			return (0);
		i++;
	}
	return (1);
}
