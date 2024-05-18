/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboudjel <lboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 05:20:48 by lboudjel          #+#    #+#             */
/*   Updated: 2024/03/29 01:46:35 by lboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	question_mark(t_pipex *pipex, char *output, int *j)
{
	char	*value;
	int		i;

	i = 0;
	value = ft_itoa(pipex->status_code);
	while (value[i])
	{
		output[*j] = value[i];
		(*j)++;
		i++;
	}
	free(value);
}

void	i_and_count_plus_plus(int *i, int *count, int i_plus, int count_plus)
{
	(*i) += i_plus;
	(*count) += count_plus;
}

int	total_expand(char *input, t_copyenv *lst_envp, t_pipex *pipex, int i)
{
	int (count) = 0;
	char *(value) = ft_itoa(pipex->status_code);
	int (res) = 0;
	while (input[i])
	{
		handle_single_quote(input, &i, &count);
		handle_double_quote((char *[]){input, value}, &i, &count, lst_envp);
		res = count_while_dollar((char *[]){input, value}, &i,
				&count, lst_envp);
		if (res == 3)
			return (0);
		if (input[i] == '\'')
			continue ;
		if (input[i])
			i_and_count_plus_plus(&i, &count, 1, 1);
	}
	return (free(value), count);
}

// int	total_expand(char *input, t_copyenv *lst_envp, t_pipex *pipex, int i)
// {
// 	int (count) = 0;
// 	char *(value) = ft_itoa(pipex->status_code);
// 	int (res) = 0;
// 	while (input[i])
// 	{
// 		handle_single_quote(input, &i, &count);
// 		handle_double_quote((char *[]){input, value}, &i, &count, lst_envp);
// 		while (input[i] == '$')
// 		{
// 			if (input[i + 1] == '\0' || input[i + 1] == '"')
// 				break ;
// 			if (input[i + 1] == '"')
// 			{
// 				i++;
// 				break ;
// 			}
// 			res = handle_dollar((char *[]){input, value}, &i, &count, lst_envp);
// 			if (res == 1)
// 				break ;
// 			if (res == 2)
// 				continue ;
// 			if (res == 3)
// 				return (0);
// 		}
// 		if (input[i] == '\'')
// 			continue ;
// 		if (input[i])
// 			i_and_count_plus_plus(&i, &count, 1, 1);
// 	}
// 	return (free(value), count);
// }
