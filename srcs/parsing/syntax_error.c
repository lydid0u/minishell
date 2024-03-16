/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboudjel <lboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 02:54:53 by lboudjel          #+#    #+#             */
/*   Updated: 2024/03/16 01:42:03 by lboudjel         ###   ########.fr       */
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
	while (input[i])
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
	while (input[i])
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
			((input[i] == '>' || input[i] == '<') && i++);
			while (input[i])
			{
				if (input[i] == '|' || input[i] == '>' || input[i] == '<')
					return (1);
				else if (input[i] == ' ' || input[i] == '\t')
					i++;
				else
					break ;
			}
		}
		(input[i] && i++);
	}
	return (0);
}
