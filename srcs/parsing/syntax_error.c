/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: lboudjel <lboudjel@student.42.fr>          +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2024/03/07 02:54:53 by lboudjel          #+#    #+#             */
/*   Updated: 2024/03/23 00:27:50 by lboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	syntax error :
		if tab[0] == PIPE
		if tab[i] == PIPE && tab[i + 1] == PIPE
		if tab[dernier] == PIPE ou CHEVRON
		if tab[i] == CHEVRON && tab[i + 1] == CHEVRON ou PIPE
*/

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

int	pipe_in_first(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '|')
			return (1);
		else if (input[i] == ' ' || input[i] == '\t')
			i++;
		else
			break ;
	}
	return (0);
}

int	pipe_in_last(char *input, int i)
{
	while (i >= 0)
	{
		if (input[i] == '|')
			return (1);
		else if (input[i] == ' ' || input[i] == '\t')
			i--;
		else
			break ;
	}
	return (0);
}

int	redir_in_last(char *input, int i)
{
	while (i >= 0)
	{
		if (input[i] == '<' || input[i] == '>')
			return (1);
		else if (input[i] == ' ' || input[i] == '\t')
			i--;
		else
			break ;
	}
	return (0);
}

int	double_pipe(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '|')
		{
			i++;
			while (input[i])
			{
				if (input[i] == '|')
					return (1);
				else if (input[i] == ' ' || input[i] == '\t')
					i++;
				else
					break ;
			}
		}
		i++;
	}
	return (0);
}
