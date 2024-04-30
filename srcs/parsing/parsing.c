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

char	*final_string(char *input, t_copyenv *lst_envp, t_pipex *pipex)
{
	int		k;
	char	*value;
	char	*key;

	int (i) = 0;
	int (j) = 0;
	char *(output) = malloc(sizeof(char) * (total_expand(input, lst_envp)) + 1);
	if (!output)
		return (NULL);
	while (input[i])
	{
		write_single_quote(input, output, &i, &j);
		while (input[i] == '$')
		{
			if (input[i + 1] == ' ' || input[i + 1] == '\t'
				|| input[i + 1] == '\0' || input[i + 1] == '"')
			{
				output[j++] = input[i++];
				break ;
			}
			i++;
			if (input[i] == '?')
			{
				question_mark(pipex, output, &j);
				i++;
				continue ;
			}
			key = get_key_expand(&input[i]);
			if (!key)
				return (NULL);
			if (is_key_valid(key, lst_envp) != 0)
			{
				i += get_len_of_key(key);
				free(key);
				continue ;
			}
			value = get_value_from_key(key, lst_envp);
			k = 0;
			while (value[k])
				output[j++] = value[k++];
			i += get_len_of_key(&input[i]);
			free(key);
		}
		if (input[i])
			output[j++] = input[i++];
	}
	output[j] = '\0';
	return (free(input), output);
}
