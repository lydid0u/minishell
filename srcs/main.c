/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboudjel <lboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 20:40:48 by lboudiel          #+#    #+#             */
/*   Updated: 2024/03/30 08:03:00 by lboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**copy_env_to_tab( t_copyenv *lst_envp)
{
	char	**tab;

	int (i) = 0;
	t_copyenv (*head) = lst_envp;
	while (head)
	{
		head = head->next;
		i++;
	}
	tab = malloc(sizeof(char *) * (i + 1));
	i = 0;
	head = lst_envp;
	while (head)
	{
		tab[i] = malloc(ft_strlen(head->key) + 1 + ft_strlen(head->value) + 1);
		ft_strcpy(tab[i], head->key);
		ft_strcat(tab[i], "=");
		ft_strcat(tab[i], head->value);
		i++;
		head = head->next;
	}
	tab[i] = '\0';
	return (tab);
}

int	main(int argc, char **argv, char **envp)
{
	static t_pipex	pipex = {0};
	t_token			*token;
	char			*prompt;
	int				nbcmd;

	(void)argc;
	(void)argv;
	//isatty();
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &ctrl_c);
	t_copyenv *(lst_envp) = create_lst(envp);
	// if (!lst_envp)
		// return (1);m
	pipex.tab_env = NULL;
	// int i = 0;
	while (1)
	{
		prompt = readline("minishell> ");
		// prompt = ft_strdup("unset SHELL");
		if (!prompt)
			break ;
		if (!*prompt)
			continue ;
		add_history(prompt);
		pipex.prompt = final_string(prompt, lst_envp, &pipex);
		if (parsing(pipex.prompt))
		{
			pipex.status_code = 2;
			free(pipex.prompt);
			continue ;
		}
		pipex.prompt = add_spaces(pipex.prompt); //COMMENTEE
		if (!pipex.prompt)
			break ;
		pipex.prompt = suppresing_quote(pipex.prompt);
		pipex.cmd = ft_split(pipex.prompt, '|');
		if (!pipex.cmd || !pipex.cmd[0])
		{
			free_tab(pipex.cmd);
			continue ;
		}
		nbcmd = countword(pipex.prompt, '|');
		quote_positif(pipex.prompt);
		token = tokenisation(pipex.cmd[0]); //COMMENTEE
		if (nbcmd == 1 && is_builtin(token->cmd))
		{
			pipex.status_code = 0;
			chevron_no_fork(&pipex, token, lst_envp); //COMMENTEE
			free_token(token);
		}
		else
		{
			free_token(token);
			exec(nbcmd, lst_envp, &pipex); //COMMENTEE
		}
		free(pipex.prompt);
		free_tab(pipex.cmd);
	}
	free_lst(lst_envp);
	free_tab(pipex.tab_env);
	printf("exit\n");
	rl_clear_history();
	return (pipex.status_code);
}

// pipex.cmd = on split au pipe -> je recupere chaque commande