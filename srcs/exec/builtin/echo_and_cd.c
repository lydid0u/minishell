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

void	built_in_echo(char **str)
{
	int	i;
	int space;

	i = 0;
	space = 0;
	while (str[i])
	{
		if (ft_strncmp(str[i], "-n", 2) == 0)
		{
			if (echo_option_n(str[i]) == 1)
			{
				space = 1;
				i++;
			}
			else			
				break;
		}
		else
			break;
	}
	while (str[i])
	{
		printf("%s", str[i]);
		if (str[i + 1])
			printf(" ");
		i++;
	}
	if (space != 1)
		printf("\n");
	// if (space)
	// 	printf("{$}");
}

/*
echoHola : leaks mais bon message
echo-nHola : leaks mais bon message
// jai pas le $ pour le \n
rcho : leaks 
EechoE : leaks 
--> les leaks viennent surement de exec

----------------------------------------

e"cho hola" : doit renvoyer "echo hola: command not found"
--> je renvoie hola
*/

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