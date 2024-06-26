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

int	handle_built_in_pipex(t_token *token, t_pipex *pipex, t_copyenv *lst_envp)
{
	int	status;

	if (ft_strcmp(token->cmd, "export") == 0)
		return (built_in_export(&token->args[1], &pipex->envp), 0);
	if (ft_strcmp(token->cmd, "unset") == 0)
		return (built_in_unset(&token->args[1], pipex->envp), 0);
	if (ft_strcmp(token->cmd, "echo") == 0)
		return (built_in_echo(&token->args[1]), 0);
	if (ft_strcmp(token->cmd, "pwd") == 0)
		return (built_in_pwd(), 0);
	if (ft_strcmp(token->cmd, "cd") == 0)
		return (built_in_cd(&token->args[1], pipex->envp), 0);
	if (ft_strcmp(token->cmd, "env") == 0)
		return (built_in_env(pipex->envp), 0);
	if (ft_strcmp(token->cmd, "exit") == 0)
	{
		status = ft_exit(pipex, token, lst_envp, 1);
		return (status);
	}
	return (1);
}

int	handle_built_in_no_fork(t_pipex *pipex, t_token *token,
	t_copyenv **lst_envp)
{
	int	status;

	if (ft_strcmp(token->cmd, "export") == 0)
		return (built_in_export(&token->args[1], lst_envp));
	if (ft_strcmp(token->cmd, "unset") == 0)
		return (built_in_unset(&token->args[1], *lst_envp));
	if (ft_strcmp(token->cmd, "echo") == 0)
		return (built_in_echo(&token->args[1]));
	if (ft_strcmp(token->cmd, "pwd") == 0)
		return (built_in_pwd());
	if (ft_strcmp(token->cmd, "cd") == 0)
		return (built_in_cd(&token->args[1], *lst_envp));
	if (ft_strcmp(token->cmd, "env") == 0)
		return (built_in_env(*lst_envp));
	if (ft_strcmp(token->cmd, "exit") == 0)
	{
		status = ft_exit(pipex, token, *lst_envp, 0);
		return (status);
	}
	return (0);
}

int	built_in_pwd(void)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf("%s\n", cwd);
	else
		perror("getcwd");
	return (0);
}

int	built_in_env(t_copyenv *lst_envp)
{
	t_copyenv	*print;

	print = lst_envp;
	while (print)
	{
		printf("%s=%s\n", print->key, print->value);
		print = print->next;
	}
	return (0);
}

void	update_pwd(t_copyenv *lst_envp)
{
	t_copyenv	*current;
	char		cwd[1024];

	current = lst_envp;
	while (current)
	{
		if (ft_strcmp(current->key, "PWD") == 0)
		{
			free(current->value);
			current->value = ft_strdup(getcwd(cwd, sizeof(cwd)));
			return ;
		}
		current = current->next;
	}
	return ;
}
