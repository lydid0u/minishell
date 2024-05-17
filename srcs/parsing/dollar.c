/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboudjel <lboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 21:54:41 by lboudjel          #+#    #+#             */
/*   Updated: 2024/05/17 21:55:08 by lboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_dollar(char *input, int *i, int *count, char *value,
	t_copyenv *lst_envp)
{
	if (input[(*i) + 1] == '?')
	{
		i_and_count_plus_plus(i, count, 2, ft_strlen(value));
		return (2);
	}
	else if (!ft_isalnum(input[(*i) + 1]) && input[(*i)] != '_')
		return (1);
	i_and_count_plus_plus(i, count, 1, 1);
	if (is_key_valid(&input[(*i)], lst_envp))
	{
		(*i) += get_len_of_key(&input[(*i)]);
		return (2);
	}
	count += get_len_of_value_from_str(&input[(*i)], lst_envp);
	i += get_len_of_key(&input[(*i)]);
	return (0);
}

// (tab)[0] = INPUT
// (tab)[1] = OUTPUT
int	write_dollars(char *tab[2], int *i_j[2], t_copyenv *lst_envp,
	t_pipex *pipex)
{
	char *(value);
	char *(key);
	int (k) = 0;
	if (tab[0][(*i_j[0]) + 1] == '?')
	{
		(*i_j[0])++;
		question_mark(pipex, tab[1], i_j[1]);
		return ((*i_j[0])++, 2);
	}
	else if (!ft_isalnum(tab[0][(*i_j[0]) + 1]) && tab[0][(*i_j[0]) + 1] != '_')
		return (1);
	(*i_j[0])++;
	key = get_key_expand(&tab[0][(*i_j[0])]);
	if (!key)
		return (3);
	if (is_key_valid(key, lst_envp) != 0)
		return ((*i_j[0]) += get_len_of_key(key), free(key), 2);
	value = get_value_from_key(key, lst_envp);
	while (value[k])
		tab[1][(*i_j[1])++] = value[k++];
	return ((*i_j[0]) += get_len_of_key(&tab[0][(*i_j[0])]), free(key), 0);
}

int	while_dollar(char *tab[2], int *i_j[2], t_copyenv *lst_envp,
	t_pipex *pipex)
{
	int	res;

	res = 0;
	while (tab[0][(*i_j[0])] == '$')
	{
		if (tab[0][(*i_j[0]) + 1] == '\0' || tab[0][(*i_j[0]) + 1] == '"')
		{
			(*i_j[0])++;
			break ;
		}
		res = write_dollars((char *[]){tab[0], tab[1]},
				(int *[]){&(*i_j[0]), &(*i_j[1])}, lst_envp, pipex);
		if (res == 1)
			break ;
		if (res == 2)
			continue ;
		if (res == 3)
			break ;
	}
	return (res);
}
