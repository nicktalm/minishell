/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntalmon <ntalmon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 11:56:03 by lbohm             #+#    #+#             */
/*   Updated: 2024/03/25 18:32:32 by ntalmon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exe_cd(char *path)
{
	if (chdir(path))
		error(ERROR_12);
}

void	exe_pwd(void)
{
	char	*cwd;
	int		size;

	size = 1;
	cwd = malloc(size * sizeof(char));
	if (!cwd)
		error(ERROR_1);
	while (getcwd(cwd, size) == NULL)
	{
		if (errno == ERANGE)
		{
			size++;
			free(cwd);
			cwd = malloc(size * sizeof(char));
			if (!cwd)
				error(ERROR_1);
		}
		else
			error(ERROR_11);
	}
	printf("%s\n", cwd);
	free(cwd);
}

void	exe_exit(t_data data)
{
	freeup(data.cmd_path);
	if (data.exe)
		free_exe((t_exe *)data.exe);
	free(data.in);
	free_ast(data.s_n);
	free_lst(&data.vars);
	free(data.path_exe);
	exit(0);
}

// void	ctrl_c(int signal)
// {
// 	signal = 0;
// 	printf("\n");
// 	rl_on_new_line();
// 	rl_replace_line("", 0);
// 	rl_redisplay();
// }

void	exe_env(t_var *vars)
{
	t_var	*ptr;

	ptr = vars;
	if (vars == NULL || vars->name == NULL)
	{
		printf("Keine Umgebungsvariablen vorhanden.\n");
		return ;
	}
	while (ptr != NULL)
	{
		printf("%s=%s\n", ptr->name, ptr->value);
		ptr = ptr->nxt;
	}
}

void	exe_export(t_data *data, t_exe *cmd)
{
	t_var	*ptr;
	char	*name_to_search;
	int		len_name;

	ptr = data->export;
	if (cmd->argv[1] == NULL)
	{
		printf("test\n");
		print_export(data->export);
		exit (0);
	}
	if (ft_strchr(cmd->argv[1], '='))
	{
		len_name = (ft_strlen(cmd->argv[1])
				- ft_strlen(ft_strchr(cmd->argv[1], '=')));
		name_to_search = ft_substr(cmd->argv[1], 0, len_name);
		while (ptr != NULL)
		{
			if (!(ft_strncmp(ptr->name, name_to_search,
						ft_strlen(name_to_search)))
				&& !(ft_strncmp(ptr->name, name_to_search,
						ft_strlen(ptr->name))))
			{
				free(ptr->value);
				ptr->value = ft_substr(cmd->argv[1], len_name + 1,
						ft_strlen(ft_strchr(cmd->argv[1], '=')));
				break ;
			}
			ptr = ptr->nxt;
		}
		if (ptr == NULL)
		{
			ft_lstadd_back_new(&data->vars,
				ft_lstnew_new(ft_substr(cmd->argv[1], 0, len_name),
					ft_substr(cmd->argv[1], len_name + 1,
						ft_strlen(ft_strchr(cmd->argv[1], '=')) + 1)));
		}
	}
}

void	exe_unset(t_data *data, t_exe *cmd)
{
	t_var	*ptr;
	char	*name_to_search;

	ptr = data->vars;
	name_to_search = cmd->argv[1];
	while (ptr != NULL)
	{
		if (!ft_strncmp(ptr->name, name_to_search, ft_strlen(ptr->name)))
		{
			ft_lstdelone_new(&(data->vars), ptr, del);
			break ;
		}
		ptr = ptr->nxt;
	}
}

void	exe_echo(t_exe *cmd)
{
	int	nline;
	int	i;

	nline = 0;
	i = 1;
	if (cmd->argv[1] == NULL)
		exit (0);
	if (ft_strcmp(cmd->argv[1], "-n") == 0)
	{
		nline = 1;
		i = 2;
	}
	while (cmd->argv[i] != NULL)
	{
		printf("%s", cmd->argv[i]);
		if (cmd->argv[i + 1] != NULL)
			printf(" ");
		i++;
	}
	if (nline == 0)
		printf("\n");
}

void	print_export(t_var *export)
{
	t_var	*ptr;

	ptr = export;
	if (export == NULL || export->name == NULL)
	{
		printf("Keine Umgebungsvariablen vorhanden.\n");
		return ;
	}
	while (ptr != NULL)
	{
		printf("declare -x %s=%s\n", ptr->name, ptr->value);
		ptr = ptr->nxt;
	}
}
