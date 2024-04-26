/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_and_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboudjel <lboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 07:17:10 by lboudjel          #+#    #+#             */
/*   Updated: 2024/03/31 07:17:10 by lboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_echo(char **tab)
{
	int j;

	j = 0;
	while (tab[j])
	{
		printf("%s", tab[j]);
		if (tab[j + 1])
			printf(" ");
		j++;
	}
}

void	built_in_echo(char **tab, t_pipex *pipex)
{
	int	i;
	int	space;
	(void)pipex;
	i = 0;
	space = 0;
	while (tab[i])
	{
		if (ft_strncmp(tab[i], "-n", 2) == 0)
		{
			if (echo_option_n(tab[i]) == 1)
			{
				space = 1;
				i++;
			}
			else
				break ;
		}
		else
			break ;
	}
	print_echo(&tab[i]);
	if (space != 1)
		printf("\n");
}

int	echo_option_n(char *str)
{
	int	j;

	j = 0;
	if (!str || str[0] != '-' || !str[1])
		return (0);
	j = 1;
	while (str[j])
	{
		if (str[j] != 'n')
			return (0);
		j++;
	}
	return (1);
}

char	*find_home(t_copyenv *lst_envp)
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
		path = find_home(lst_envp);
	else
		path = tab[0];
	cd = chdir(path);
	if (cd == -1)
		printf("cd: %s: No such file or directory\n", tab[0]);
}
