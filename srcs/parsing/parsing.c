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

int	check_separator(char *input)
{
	int	len;

	len = ft_strlen(input) - 1;
	if (pipe_in_first(input))
		return (ft_printf(SYNTAXERROR, "|'\n"), 1);
	if (pipe_in_last(input, len))
		return (ft_printf(SYNTAXERROR, "|'\n"), 1);
	if (redir_in_last(input, len))
		return (ft_printf(SYNTAXERROR, "redirection'\n"), 1);
	if (double_pipe(input))
		return (ft_printf(SYNTAXERROR, "||'\n"), 1);
	if (redir_n_pipe(input))
		return (ft_printf(SYNTAXERROR, "double separator'\n"), 1);
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
