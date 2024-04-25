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

// //while (tab[(*i)])  && tab[(*i)] == words ??
// void	print_echo(char **tab, int *i)
// {
// 	// (*i)++;
// 	// if ()
// 	while (tab[(*i)])
// 	{
// 		if (is_a_redirection(tab[(*i)]))
// 			break;
// 		printf("{%s}", tab[(*i)]);
// 		if (tab[(*i) + 1])
// 			printf(" ");
// 		(*i)++;
// 	}
// }

void	print_echo(char **tab, int *i, t_pipex *pipex)
{
	int j;

	j = 0;
	(void)tab;
	(void)i;
	while (j < pipex->token->arg_count)
	{
		printf("%s", pipex->token->args[j]);
		if (pipex->token->args[j + 1])
			printf(" ");
		j++;
	}
}

// int	countword_v2(const char *s)
// {
// 	int	i;
// 	int	len;
//     // char quote;

// 	i = 0;
// 	len = 0;
// 	while (s[i])
// 	{
// 		while (s[i] != '\0' && (s[i] == ' ' || s[i] == '\t'))
// 			i++;
// 		if (s[i] != '\0')
// 			len++;
// 		while (s[i] != '\0' && s[i] != ' ' && s[i] != '\t')
//         {
//             printf("countword {%s}\n", &s[i]);
//             // if (s[i] == '"' || s[i] == '\'')
//             // {
//             //     quote = s[i];
//             //     while (s[i] != quote)
//             //         i++;
//             // }
// 			i++;
//         }
// 	}
//     printf("LA LEN %d\n", len);
// 	return (len);
// }

void	built_in_echo(char **tab, t_pipex *pipex)
{
	int	i;
	int	space;

	(void)pipex;
	i = 0;
	space = 0;
	while (tab[i])
	{
		printf("%s", tab[i]);
		if (tab[i + 1])
			printf(" ");
		// if (ft_strncmp(tab[i], "-n", 2) == 0)
		// {
		// 	if (echo_option_n(tab[i]) == 1)
		// 	{
		// 		space = 1;
		i++;
		// 	}
		// 	else
		// 		break ;
		// }
		// else
		// 	break ;
	}
	// print_echo(tab, &i, pipex);
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
