/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboudjel <lboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 18:19:08 by lboudjel          #+#    #+#             */
/*   Updated: 2024/05/12 20:49:30 by lboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_len_word(char *str)
{
	int	i;
	int	r;

	i = 0;
	r = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	while (str[i] && !ft_isspace(str[i] && !ft_strchr("><|&", str[i])))
	{
		i++;
		r++;
	}
	return (r);
}

char	*get_word(char *str)
{
	int		i;
	int		r;
	char	*word;

	word = malloc(get_len_word(str) + 1);
	i = 0;
	r = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	while (str[i] && !ft_isspace(str[i]) && !ft_strchr("><|&", str[i]))
	{
		word[r] = str[i];
		r++;
		i++;
	}
	word[r] = '\0';
	return (word);
}

int	count_here_doc(char *str)
{
	int	nb;
	int	i;

	nb = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '<')
		{
			i++;
			if (str[i] == '<')
			{
				nb++;
				i++;
			}
		}
		i++;
	}
	return (nb);
}

void	free_heredoc(t_pipex *pipex)
{
	int	i;

	i = 0;
	if (!pipex->nbr_heredoc)
		return ;
	while (i < pipex->nbr_heredoc)
	{
		free(pipex->heredoc[i].stop_word);
		close(pipex->heredoc[i].hd_pipe[0]);
		close(pipex->heredoc[i].hd_pipe[1]);
		i++;
	}
	free(pipex->heredoc);
	pipex->nbr_heredoc = 0;
}

void	close_heredoc(t_pipex *pipex)
{	
	int	i;

	i = 0;
	while (i < pipex->nbr_heredoc)
	{
		close(pipex->heredoc[i].hd_pipe[0]);
		i++;
	}
}
