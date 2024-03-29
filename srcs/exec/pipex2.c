/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboudjel <lboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 18:20:10 by lboudjel          #+#    #+#             */
/*   Updated: 2024/03/03 19:41:25 by lboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*access_cmd(t_pipex *pipex, int i)
{
	int		j;
	char	*check_access;

	j = 0;
	pipex->args_path = get_path(pipex->envp);
	if (ft_strchr(pipex->tab_cmd[i], '/'))
	{
		if (access(pipex->tab_cmd[i], F_OK | X_OK) != -1)
			return (ft_strdup(pipex->tab_cmd[i]));
		return (NULL);
	}
	if (!pipex->args_path)
		return (free_tab(pipex->args_path), NULL);
	while (pipex->args_path[j])
	{
		check_access = ft_strjoin_slash(pipex->args_path[j], pipex->tab_cmd[i]);
		if (access(check_access, F_OK | X_OK) == 0)
			return (check_access);
		free(check_access);
		j++;
	}
	ft_printf("command not found : %s \n", pipex->tab_cmd[i]);
	return (free_tab(pipex->args_path), NULL);
}

int	open_fd(t_pipex *pipex, int i)
{
	int	fd;

	fd = -1;
	if (i == pipex->nbr_cmd - 1)
	{
		fd = open(pipex->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
		{
			close(pipex->fd[0]);
			return (close(pipex->prev), close(pipex->fd[1]),
				perror("open outfile"), exit(1), fd);
		}
	}
	return (fd);
}

char	**get_path(t_copyenv *lst_envp)
{
	int	i;

	i = 0;
	while (lst_envp)
	{
		if (ft_strcmp(lst_envp->key, "PATH") == 0)
			return (ft_split(lst_envp->value, ':'));
		lst_envp = lst_envp->next;
	}
	return (NULL);
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	here_doc(char *infile, char *stop_word)
{
	int		fd;
	char	*line;

	fd = open(infile, O_RDWR | O_CREAT, 0644);
	if (fd < 0)
		return (perror("Error"), exit(1));
	stop_word = ft_strjoin(stop_word, "\n");
	while (1)
	{
		write(1, "heredoc> ", 10);
		line = get_next_line(0, 0);
		if (!line)
			break ;
		if (ft_strcmp(line, stop_word) == 0)
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, fd);
		free(line);
	}
	get_next_line(0, 1);
	free(stop_word);
	close(fd);
}
