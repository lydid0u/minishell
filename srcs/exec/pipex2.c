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

char	*access_cmd(t_pipex *pipex, t_token *mycmd)
{
	int		i;
	char	*check_access;

	i = 0;
	if (ft_strchr(mycmd->cmd, '/'))
	{
		if (access(mycmd->cmd, F_OK | X_OK) != -1)
			return (ft_strdup(mycmd->cmd));
		return (NULL);
	}
	pipex->args_path = get_path(pipex->envp);
	if (!pipex->args_path)
		return (NULL);
	while (pipex->args_path[i])
	{
		check_access = ft_strjoin_slash(pipex->args_path[i], mycmd->cmd);
		if (access(check_access, F_OK | X_OK) == 0)
			return (free_tab(pipex->args_path), check_access);
		free(check_access);
		i++;
	}
	fprintf(stderr, "command not found : %s \n", mycmd->cmd);
	return (free_tab(pipex->args_path), NULL);
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
