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

char	*access_cmd(t_pipex *pipex, t_token *token, int *flag)
{
	int		i;
	char	*check_access;

	i = 0;
	if (ft_strchr(token->cmd, '/'))
	{
		if (access(token->cmd, F_OK | X_OK) != -1)
			return (ft_strdup(token->cmd));
		return (NULL);
	}
	pipex->path = get_path(pipex->envp);
	if (!pipex->path)
		return (NULL);
	while (pipex->path[i])
	{
		check_access = ft_strjoin_slash(pipex->path[i], token->cmd);
		if (access(check_access, F_OK | X_OK) == 0)
			return (free_tab(pipex->path), check_access);
		free(check_access);
		i++;
	}
	fprintf(stderr, "%s: command not found\n", token->cmd);
	(*flag) = 1;
	return (free_tab(pipex->path), NULL);
}

char	**get_path(t_copyenv *lst_envp)
{
	while (lst_envp)
	{
		if (ft_strcmp(lst_envp->key, "PATH") == 0)
			return (ft_split(lst_envp->value, ':'));
		lst_envp = lst_envp->next;
	}
	return (NULL);
}

void	redirection(t_pipex *pipex, int i)
{
	if (i != 0)
	{
		dup2(pipex->prev, 0);
		close(pipex->prev);
	}
	if (i != pipex->nbr_cmd - 1)
		dup2(pipex->fd[1], 1);
	close(pipex->fd[0]);
	close(pipex->fd[1]);
}

int	ft_status(t_token *token)
{
	struct stat	file;

	stat(token->cmd, &file);
	if ((!(ft_strncmp(token->cmd, "./", 2))
			|| !(ft_strncmp(token->cmd, "/", 1))) && S_ISDIR(file.st_mode))
	{
		return (fprintf(stderr, "%s: Is a directory\n", token->cmd), 126);
	}
	else if (S_ISDIR(file.st_mode))
		return (fprintf(stderr, "%s: Is a directory\n", token->cmd), 126);
	else if (!(ft_strncmp(token->cmd, "./", 2)))
	{
		if (access(token->cmd, F_OK) == 0 && access(token->cmd, X_OK) == -1)
			return (perror(token->cmd), 126);
		if (access(token->cmd, F_OK) == -1)
			perror(token->cmd);
		return (127);
	}
	else if (!(ft_strncmp(token->cmd, "/", 1)))
	{
		if (access(token->cmd, F_OK) == -1)
			fprintf(stderr, "%s: No such file or directory\n", token->cmd);
		return (127);
	}
	return (127);
}
