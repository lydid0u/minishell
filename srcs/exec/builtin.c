/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboudjel <lboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 05:39:43 by lboudjel          #+#    #+#             */
/*   Updated: 2024/03/30 08:07:46 by lboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	built_in_echo(char **str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			if (str[i][j] == '\'' || str[i][j] == '"')
				j++;
			printf("%c", str[i][j]);
			j++;
		}
		if (str[i + 1])
			printf(" ");
		i++;
	}
	printf("\n");
}

void	built_in_pwd(t_copyenv *lst_envp)
{
	t_copyenv	*current;

	current = lst_envp;
	while (current)
	{
		if (ft_strcmp(current->key, "PWD") == 0)
		{
			printf("%s\n", current->value);
			break ;
		}
		current = current->next;
	}
}

char	*get_home(t_copyenv *lst_envp)
{
	t_copyenv	*current;

	current = lst_envp;
	while (current)
	{
		if (ft_strcmp(current->key, "HOME") == 0)
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

void	built_in_cd(char **tab, t_copyenv *lst_envp)
{
	int		cd;
	char	*path;

	if (tab[0] == NULL)
		path = get_home(lst_envp);
	else
		path = tab[0];
	cd = chdir(path);
	if (cd == -1)
		printf("cd: %s: No such file or directory\n", tab[0]);
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
