/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addspaces.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboudjel <lboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 00:01:35 by lboudjel          #+#    #+#             */
/*   Updated: 2024/03/30 04:31:13 by lboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
addspaces
prend la chaine input en argument
doit reproduire ce comportement:
		input = ls>a|>>a<b|c
		output= ls > a >>|  a < b | c
*/

int	count_token(char *input)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (input[i])
	{
		if (input[i] == '|' || input[i] == '>' || input[i] == '<')
		{
			if ((input[i] == '>' && input[i + 1] == '>') || (input[i] == '<'
					&& input[i + 1] == '<'))
			{
				count++;
				i++;
			}
			count++;
		}
		i++;
	}
	return (count * 2);
}

char	*add_spaces(char *s)
{
	int		i;
	int		j;
	char	*output;

	output = malloc(sizeof(char) * (ft_strlen(s) + count_token(s) + 1));
	if (!output)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] == '|' || s[i] == '>' || s[i] == '<')
		{
			output[j++] = ' ';
			if ((s[i] == '>' && s[i + 1] == '>') || (s[i] == '<' && s[i
						+ 1] == '<'))
				output[j++] = s[i++];
			output[j++] = s[i++];
			output[j++] = ' ';
		}
		else
			output[j++] = s[i++];
	}
	output[j] = '\0';
	return (free(s), output);
}
