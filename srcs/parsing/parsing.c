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
	quote_positif(input);
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
// (*i_j)[0] = i
// (*i_j)[1] = j
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
		write_double_quote((char *[]){in, out}, (int *[]){&i, &j},
			envp, pipex);
		res = while_dollar((char *[]){in, out}, (int *[]){&i, &j},
				envp, pipex);
		if (res == 3)
			return (NULL);
		if (in[i] == '\'')
			continue ;
		if (in[i])
			out[j++] = in[i++];
	}
	out[j] = '\0';
	return (free(in), out);
}
