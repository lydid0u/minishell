/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboudjel <lboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 02:16:46 by lboudjel          #+#    #+#             */
/*   Updated: 2024/03/26 03:26:40 by lboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parsing(char *input)
{
	if (check_quotes(input))
		return (ft_printf("bash: error with the quotes\n"), 1);
	quote_negatif(input);
	if (check_separator(input))
		return (1);
	return (0);
}

int	double_separator(char *input, int *i)
{
	while (input[(*i)])
	{
		if (input[(*i)] == '|' || input[(*i)] == '>' || input[(*i)] == '<')
			return (1);
		else if (input[(*i)] == ' ' || input[(*i)] == '\t')
			(*i)++;
		else
			break ;
	}
	return (0);
}

// sadasd ads asd dsasad > asd >> a  | asd
int	redir_n_pipe(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '>' || input[i] == '<')
		{
			if ((input[i] == '>' && input[i + 1] == '<') || (input[i] == '<'
					&& input[i + 1] == '>'))
				return (1);
			i++;
			if (input[i] == '>' || input[i] == '<')
				i++;
			if (double_separator(input, &i))
				return (1);
		}
		if (input[i])
			i++;
	}
	return (0);
}

// (tab)[0] = INPUT
// (tab)[1] = OUTPUT
int	handle_dollars(char *tab[2], int *i_j[2], t_copyenv *lst_envp,
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
	{
		tab[1][(*i_j[1])++] = tab[0][(*i_j[0])++];
		return (1);
	}
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

char	*final_string(char *in, t_copyenv *envp, t_pipex *pipex, int res)
{
	int (i) = 0;
	int (j) = 0;
	char *(out) = malloc(sizeof(char) * (total_expand(in, envp, pipex, 0)) + 1);
	if (!out)
		return (NULL);
	while (in[i])
	{
		write_single_quote(in, out, &i, &j);
		while (in[i] == '$')
		{
			res = handle_dollars((char *[]){in, out}, (int *[]){&i, &j},
					envp, pipex);
			if (res == 1)
				break ;
			if (res == 2)
				continue ;
			if (res == 3)
				return (NULL);
		}
		if (in[i] == '\'')
			continue ;
		if (in[i])
			out[j++] = in[i++];
	}
	return (out[j] = '\0', free(in), out);
}
