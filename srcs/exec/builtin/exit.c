/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboudjel <lboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 00:50:32 by lboudjel          #+#    #+#             */
/*   Updated: 2024/05/12 20:57:21 by lboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

unsigned long long	ft_atoi_exit(const char *str)
{
	unsigned long long	i;
	unsigned long long	sign;
	unsigned long long	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i++] == '-')
			sign = -1;
	}
	if (!ft_isdigit(str[i]))
		return (9223372036854775808ULL);
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i++] - '0');
		if (result > 9223372036854775808ULL)
			return (9223372036854775808ULL);
	}
	if (str[i] && !ft_isdigit(str[i]))
		return (9223372036854775808ULL);
	return ((unsigned char)(result * sign));
}

int	ft_exit_args_is_valid(char *args)
{
	if (ft_atoi_exit(args))
		return (ft_atoi_exit(args));
	else
		return (0);
}

void	free_exit(t_pipex *pipex, t_token *token, t_copyenv *lst_envp, int fork)
{
	if (fork == 0)
	{
		dup2(pipex->out, 1);
		dup2(pipex->in, 0);
		close(pipex->in);
		close(pipex->out);
		free(pipex->prompt);
		free_tab(pipex->cmd);
	}
	free_tab(pipex->tab_env);
	free_lst(lst_envp);
	free_token(token);
}

// arg[0] = exit
int	ft_exit(t_pipex *pipex, t_token *token, t_copyenv *lst_envp, int fork)
{
	int	status;

	if (!token->args[1])
	{
		printf("exit\n");
		free_exit(pipex, token, lst_envp, fork);
		exit(0);
	}
	if (!token->args[2])
	{
		status = exit_one_arg(pipex, token, lst_envp, fork);
		exit(status);
	}
	else
	{
		if (!ft_exit_args_is_valid(token->args[1]))
		{
			ft_printf("minishell: exit: %s: numeric argument required\n",
				token->args[1]);
			exit(4);
		}
		return (ft_printf("exit: too many arguments\n"), 1);
	}
}

int	exit_one_arg(t_pipex *pipex, t_token *token, t_copyenv *lst_envp, int fork)
{
	int	status;

	if (ft_exit_args_is_valid(token->args[1]))
	{
		printf("exit\n");
		status = ft_exit_args_is_valid(token->args[1]);
		free_exit(pipex, token, lst_envp, fork);
		return (status);
	}
	else
	{
		ft_printf("exit: %s: numeric argument required\n",
			token->args[1]);
		free_exit(pipex, token, lst_envp, fork);
		return (2);
	}
}

/*
	exit
		affiche exit
		quitte avec(status)
					
	exit avec string OU valeur >= 2^63 OU string avec d'autres arguments 
		affiche exit
		quitte avec(2)
		affiche numeric argument required

	exit avec nombre < 2^63 
		affiche exit
		quitte avec(21 % 256)

	exit avec plusieurs arguments et arg[0] <= 2^63 
		affiche exit
		quitte pas
		met le status a 1 affiche too many arguments
*/