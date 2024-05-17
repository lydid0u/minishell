/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboudjel <lboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 20:37:56 by lboudjel          #+#    #+#             */
/*   Updated: 2024/05/17 21:54:38 by lboudjel         ###   ########.fr       */
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
		output[*j] = input[*i];
		(*i)++;
		(*j)++;
	}
}

void	handle_double_quote(char *input, int *i, int *count, char *value)
{
	if (input[*i] && input[*i] == '\"')
	{
		i_and_count_plus_plus(i, count, 1, 1);
		while (input[*i] && input[*i] != '\"')
		{
			if (input[*i] == '$' && input[*i + 1] == '"')
				break ;
			if (input[*i] == '$')
			{
				if (input[*i + 1] == '?')
				{
					i_and_count_plus_plus(i, count, 2, ft_strlen(value));
					continue ;
				}
			}
			else
				i_and_count_plus_plus(i, count, 1, 1);
		}
		if (input[*i])
			i_and_count_plus_plus(i, count, 1, 1);
	}
}

static void	write_n_increment(char *input, char *output, int *i, int *j)
{
	output[(*j)] = input[(*i)];
	(*i)++;
	(*j)++;
}

void	write_double_quote(char *tab[2], int *i_j[2], t_copyenv *lst_envp,
	t_pipex *pipex)
{
	int (res) = 0;
	if (tab[0][(*i_j[0])] && tab[0][(*i_j[0])] == '\"')
	{
		write_n_increment(tab[0], tab[1], &(*i_j[0]), &(*i_j[1]));
		while (tab[0][(*i_j[0])] && tab[0][(*i_j[0])] != '"')
		{
			if (tab[0][(*i_j[0])] == '$' && tab[0][(*i_j[0]) + 1] == '"')
				break ;
			if (tab[0][(*i_j[0])] == '$')
			{
				res = write_dollars((char *[]){tab[0], tab[1]},
						(int *[]){&(*i_j[0]), &(*i_j[1])}, lst_envp, pipex);
				if (res == 1)
					break ;
				if (res == 2)
					continue ;
				if (res == 3)
					return ;
			}
			else
				write_n_increment(tab[0], tab[1], &(*i_j[0]), &(*i_j[1]));
		}
		if (tab[0][(*i_j[0])])
			write_n_increment(tab[0], tab[1], &(*i_j[0]), &(*i_j[1]));
	}
}
