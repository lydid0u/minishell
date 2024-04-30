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

void	print_token(t_pipex *pipex)
{
    printf("\nCommand: %s\n", pipex->token->cmd);
    for (int i = 0; i < pipex->token->arg_count; i++) 
    {
    	printf( "argument : %s\n", pipex->token->args[i]);
	}
    printf("\n");
    for (int i = 0; i < pipex->token->file_count; i++) 
    {
        printf("Redirection: %d\n", pipex->token->redir_chevron[i]);
        printf("File: %s\n", pipex->token->files[i]);
    }
}

char	**copy_env_to_tab(char **envp)
{
	int (i) = 0;
	char	**tab;
	while (envp[i])
		i++;
	tab = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while(envp[i])
	{
		tab[i] = ft_strdup(envp[i]);
		i++;
	}
	tab[i] = '\0';
	return (tab);
}

int	main(int argc, char **argv, char **envp)
{
	static t_pipex	pipex = {0};
	t_token			*token;
	t_copyenv		*lst_envp;
	char			*prompt;
	int				nbcmd;
	(void)argc;
	(void)argv;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &ctrl_c);
	lst_envp = create_lst(envp);
	pipex.tab_env = copy_env_to_tab(envp);
	if (!lst_envp)
		return (1);
	while (1)
	{
		prompt = readline("minishell> ");
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
		pipex.prompt = add_spaces(pipex.prompt);
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
		token = tokenisation(pipex.cmd[0]);//COMMENTAIRE
		if (nbcmd == 1 && is_builtin(token->cmd))
		{
			pipex.status_code = 0;
			chevron_no_fork(&pipex, token, lst_envp);//COMMENTAIRE
			free_token(token);
		}
		else
		{
			free_token(token);
			exec(nbcmd, lst_envp, &pipex);
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