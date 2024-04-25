/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboudjel <lboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 00:53:44 by lboudjel          #+#    #+#             */
/*   Updated: 2024/04/05 00:53:44 by lboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_built_in_pipex(t_token *cmd, t_pipex *pipex)
{
	fprintf(stderr, "MY CMD IS [%s]\n", cmd->cmd);
	if (ft_strcmp(cmd->cmd, "export") == 0)
		return (built_in_export(&cmd->tabargs[1], pipex->envp), 0);
	if (ft_strcmp(cmd->cmd, "unset") == 0)
		return (built_in_unset(&cmd->tabargs[1], pipex->envp), 0);
	if (ft_strcmp(cmd->cmd, "echo") == 0)
		return (built_in_echo(&cmd->tabargs[1], pipex), 0);
	if (ft_strcmp(cmd->cmd, "pwd") == 0)
		return (built_in_pwd(), 0);
	if (ft_strcmp(cmd->cmd, "cd") == 0)
		return (built_in_cd(&cmd->tabargs[1], pipex->envp), 0);
	if (ft_strcmp(cmd->cmd, "env") == 0)
		return (built_in_env(pipex->envp), 0);
	if (ft_strcmp(cmd->cmd, "exit") == 0)
		return (free_handle_bt(pipex), 0);
	return (1);
}

void	handle_built_in_no_exec(t_pipex *pipex, t_token *token, t_copyenv *lst_envp)
{
	// int		i;
	// char	**tab;

	// i = 0;
	// tab = ft_split(pipex->cmd[0], ' ');
	// while (tab[i])
	// {
	// 	// printf("%s\n", tab[i + 1]);
	if (ft_strcmp(token->cmd, "export") == 0)
		built_in_export(&token->tabargs[1], lst_envp);
	if (ft_strcmp(token->cmd, "unset") == 0)
		built_in_unset(&token->tabargs[1], lst_envp);
	if (ft_strcmp(token->cmd, "echo") == 0)
		built_in_echo(&token->tabargs[1], pipex);
	if (ft_strcmp(token->cmd, "pwd") == 0)
		built_in_pwd();
	if (ft_strcmp(token->cmd, "cd") == 0)
		built_in_cd(&token->tabargs[1], lst_envp);
	if (ft_strcmp(token->cmd, "env") == 0)
		built_in_env(lst_envp);
	if (ft_strcmp(token->cmd, "exit") == 0)
		free_handle_bt_no_exec(pipex, lst_envp);
		// i++;
	// }
	// free_tab(tab);
}

void	built_in_pwd(void)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf("%s\n", cwd);
	else
		perror("getcwd");
}

void	built_in_env(t_copyenv *lst_envp)
{
	t_copyenv	*print;

	print = lst_envp;
	while (print)
	{
		printf("%s=%s\n", print->key, print->value);
		print = print->next;
	}
}
