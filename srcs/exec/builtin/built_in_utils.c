/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboudjel <lboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 02:41:15 by lboudjel          #+#    #+#             */
/*   Updated: 2024/04/05 02:42:56 by lboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *cmd)
{
	int		i;
	char	**tab;

	i = 0;
	tab = ft_split(cmd, ' ');
	while (tab[i])
	{
		if (ft_strcmp(tab[i], "export") == 0)
			return (free_tab(tab), 1);
		if (ft_strcmp(tab[i], "unset") == 0)
			return (free_tab(tab), 1);
		if (ft_strcmp(tab[i], "echo") == 0)
			return (free_tab(tab), 1);
		if (ft_strcmp(tab[i], "pwd") == 0)
			return (free_tab(tab), 1);
		if (ft_strcmp(tab[i], "cd") == 0)
			return (free_tab(tab), 1);
		if (ft_strcmp(tab[i], "env") == 0)
			return (free_tab(tab), 1);
		if (ft_strcmp(tab[i], "exit") == 0)
			return (free_tab(tab), 1);
		i++;
	}
	return (free_tab(tab), 0);
}

void	free_handle_bt(t_pipex *pipex, char **tab)
{
	free_tab(pipex->cmd);
	free_tab(tab);
	free_lst(pipex->envp);
	exit(EXIT_SUCCESS);
}

void	free_handle_bt_no_exec(t_pipex *pipex, t_copyenv *lst_envp, char **tab)
{
	free(pipex->prompt);
	free_tab(pipex->cmd);
	free_tab(tab);
	free_lst(pipex->envp);
	free_lst(lst_envp);
	exit(EXIT_SUCCESS);
}
