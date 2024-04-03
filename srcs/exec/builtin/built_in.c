/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboudjel <lboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 05:39:43 by lboudjel          #+#    #+#             */
/*   Updated: 2024/03/30 08:07:46 by lboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_built_in_pipex(t_pipex *pipex, int i)		
{
	char	**tab;
	int 	j;

	j = 0;
	tab = ft_split(pipex->arg_cmd[i], ' ');
	while (tab[j])
	{
		if (ft_strcmp(tab[j], "export") == 0)
		{
			built_in_export(&tab[j + 1], pipex->envp);
			return (free_tab(tab), 0);
		}
		if (ft_strcmp(tab[j], "unset") == 0)
		{
			built_in_unset(&tab[j + 1], pipex->envp);
			return (free_tab(tab), 0);
		}
		if (ft_strcmp(tab[j], "echo") == 0)
		{
			built_in_echo(&tab[j + 1]);
			return (free_tab(tab), 0);
		}
		if (ft_strcmp(tab[j], "pwd") == 0)
		{
			built_in_pwd();
			return (free_tab(tab), 0);
		}
		if (ft_strcmp(tab[j], "cd") == 0)
		{
			built_in_cd(&tab[j + 1], pipex->envp);
			return (free_tab(tab), 0);
		}
		if (ft_strcmp(tab[j], "env") == 0)
		{
			built_in_env(pipex->envp);
			return (free_tab(tab), 0);
		}
		if (ft_strcmp(tab[j], "exit") == 0)
		{
			//checker le comportement avec un autre arg ?
			free(pipex->prompt);
			free_tab(pipex->cmd);
			free_tab(tab);
			free_lst(pipex->envp);	
			return (exit(EXIT_SUCCESS), 0);
		}
		j++;
	}
	return (free_tab(tab), 1);
}

//eske faut gerer les built in meme dans les pipes ? si oui mon parsing fonctionne pas ici 
void	handle_built_in_no_exec(t_pipex *pipex, t_copyenv *lst_envp)		
{
	char			**tab;

	tab = ft_split(pipex->cmd[0], ' ');
	if (strcmp(tab[0], "export") == 0)
		built_in_export(&tab[1], lst_envp);
	if (strcmp(tab[0], "unset") == 0)
		built_in_unset(&tab[1], lst_envp);
	if (strcmp(tab[0], "echo") == 0)
		built_in_echo(&tab[1]);
	if (strcmp(tab[0], "pwd") == 0)
		built_in_pwd();
	if (strcmp(tab[0], "cd") == 0)
		built_in_cd(&tab[1], lst_envp);
	if (strcmp(tab[0], "env") == 0)
		built_in_env(lst_envp);
	if (strcmp(tab[0], "exit") == 0)
	{
		// checker le comportement avec un autre arg ?
		free(pipex->prompt);
		free_tab(pipex->cmd);
		free_tab(tab);
		free_lst(lst_envp);	
		exit(EXIT_SUCCESS);
	}
	free_tab(tab);
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

int		is_builtin(char *cmd)
{
	int	i;
	char **tab;

	i = 0;
	tab = ft_split(cmd, ' ');
	while (tab[i])
	{
		if (ft_strcmp(tab[i], "export") == 0)
			return(free(tab), 1);
		if (ft_strcmp(tab[i], "unset") == 0)
			return(free(tab), 1);
		if (ft_strcmp(tab[i], "echo") == 0)
			return(free(tab), 1);
		if (ft_strcmp(tab[i], "pwd") == 0)
			return(free(tab), 1);
		if (ft_strcmp(tab[i], "cd") == 0)
			return(free(tab), 1);
		if (ft_strcmp(tab[i], "env") == 0)
			return(free(tab), 1);
		if (ft_strcmp(tab[i], "exit") == 0)
			return(free(tab), 1);
		i++;
	}
	return (free(tab), 0);
}