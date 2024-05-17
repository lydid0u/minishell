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
	int	i;

	i = 0;
	while (tab[i])
	{
		printf("%s", tab[i]);
		if (tab[i + 1])
			printf(" ");
		i++;
	}
}

int	built_in_echo(char **tab)
{
	int	i;
	int	space;

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
	return (0);
}

int	echo_option_n(char *str)
{
	int	i;

	i = 1;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
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

int	built_in_cd(char **tab, t_copyenv *lst_envp)
{
	int		cd;
	char	*path;

	if (tab[0] && tab[1])
	{
		ft_printf("cd: too many arguments\n");
		return (1);
	}
	if (tab[0] == NULL)
		path = find_home(lst_envp);
	else
		path = tab[0];
	cd = chdir(path);
	if (cd == -1)
	{
		perror(tab[0]);
		return (1);
	}
	update_pwd(lst_envp);
	return (0);
}
