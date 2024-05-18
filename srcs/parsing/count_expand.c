/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboudjel <lboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 14:31:47 by lboudjel          #+#    #+#             */
/*   Updated: 2024/05/18 14:46:24 by lboudjel         ###   ########.fr       */
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
		(*i)++;
		(*count)++;
	}
}

//tab[0] = input
//tab[1] = value
int	count_double_quote(char *tab[2], int *i, int *count, t_copyenv *lst_envp)
{
	if (tab[0][*i + 1] == '?')
	{
		i_and_count_plus_plus(i, count, 2, ft_strlen(tab[1]));
		return (2);
	}
	else if (!ft_isalnum(tab[0][(*i) + 1]) && tab[0][(*i)] != '_')
		return (1);
	i_and_count_plus_plus(i, count, 1, 1);
	if (is_key_valid(&tab[0][(*i)], lst_envp))
	{
		(*i) += get_len_of_key(&tab[0][(*i)]);
		return (2);
	}
	(*count) += get_len_of_value_from_str(&tab[0][(*i)], lst_envp);
	(*i) += get_len_of_key(&tab[0][(*i)]);
	return (0);
}

//tab[0] = input
//tab[1] = value
void	handle_double_quote(char *tab[2], int *i, int *count,
	t_copyenv *lst_envp)
{
	int	res;

	if (tab[0][*i] && tab[0][*i] == '\"')
	{
		i_and_count_plus_plus(i, count, 1, 1);
		while (tab[0][*i] && tab[0][*i] != '\"')
		{
			if (tab[0][*i] == '$' && tab[0][*i + 1] == '"')
				break ;
			if (tab[0][*i] == '$')
			{
				res = count_double_quote((char *[]){tab[0], tab[1]}, i,
						count, lst_envp);
				if (res == 1)
					break ;
				if (res == 2)
					continue ;
			}
			else
				i_and_count_plus_plus(i, count, 1, 1);
		}
		if (tab[0][*i])
			i_and_count_plus_plus(i, count, 1, 1);
	}
}
