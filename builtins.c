/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 11:56:03 by lbohm             #+#    #+#             */
/*   Updated: 2024/03/28 18:27:14 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_pwd(t_var *data)
{
	t_var	*ptr;

	ptr = data;
	while (ptr != NULL)
	{
		if (!(ft_strncmp(ptr->name, "PWD", 3)))
		{
			free(ptr->value);
			ptr->value = prompt_cwd();
		}
		ptr = ptr->nxt;
	}
}

void	update_oldpwd(t_var *data)
{
	t_var	*ptr;

	ptr = data;
	while (ptr != NULL)
	{
		if (!(ft_strncmp(ptr->name, "OLDPWD", 6)))
		{
			free(ptr->value);
			ptr->value = prompt_cwd();
			return ;
		}
		ptr = ptr->nxt;
	}
	ft_lstadd_back_new(&data, ft_lstnew_new("OLDPWD", prompt_cwd()));
}

void	exe_cd(t_data *data, t_exe *cmd)
{
	update_oldpwd(data->vars);
	update_oldpwd(data->export);
	chdir(cmd->argv[1]);
	update_pwd(data->vars);
	update_pwd(data->export);
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

void	exe_exit(t_data data, t_exe *cmd)
{
	if (cmd->argv[1] != 0)
		Signal = ft_atoi(cmd->argv[1]);
	freeup(data.cmd_path);
	if (data.exe)
		free_exe((t_exe *)data.exe);
	free(data.in);
	free_ast(data.s_n);
	free_lst(&data.vars);
	free(data.path_exe);
	exit(Signal);
}

void	ctrl_c(int signal)
{
	signal = 0;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

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

void	exe_export_env(t_data *data, t_exe *cmd)
{
	t_var	*ptr_env;
	char	*name_to_search;
	int		len_name;

	ptr_env = data->vars;
	if (cmd->argv[1] == NULL)
		print_export(data->export);
	else if (ft_strchr(cmd->argv[1], '='))
	{
		len_name = (ft_strlen(cmd->argv[1])
				- ft_strlen(ft_strchr(cmd->argv[1], '=')));
		name_to_search = ft_substr(cmd->argv[1], 0, len_name);
		while (ptr_env != NULL)
		{
			if (!(ft_strncmp(ptr_env->name, name_to_search,
						ft_strlen(name_to_search)))
				&& !(ft_strncmp(ptr_env->name, name_to_search,
						ft_strlen(ptr_env->name))))
			{
				free(ptr_env->value);
				ptr_env->value = ft_substr(cmd->argv[1], len_name + 1,
						ft_strlen(ft_strchr(cmd->argv[1], '=')));
				break ;
			}
			ptr_env = ptr_env->nxt;
		}
		if (ptr_env == NULL)
		{
			ft_lstadd_back_new(&data->vars,
				ft_lstnew_new(ft_substr(cmd->argv[1], 0, len_name),
					ft_substr(cmd->argv[1], len_name + 1,
						ft_strlen(ft_strchr(cmd->argv[1], '=')) + 1)));
		}
	}
}

void	exe_export_export(t_data *data, t_exe *cmd)
{
	t_var	*ptr_export;
	char	*name_to_search;
	int		len_name;

	ptr_export = data->export;
	if (cmd->argv[1] == NULL)
		return ;
	else if (ft_strchr(cmd->argv[1], '='))
	{
		len_name = (ft_strlen(cmd->argv[1])
				- ft_strlen(ft_strchr(cmd->argv[1], '=')));
		name_to_search = ft_substr(cmd->argv[1], 0, len_name);
		while (ptr_export != NULL)
		{
			if (!(ft_strncmp(ptr_export->name, name_to_search,
						ft_strlen(name_to_search)))
				&& !(ft_strncmp(ptr_export->name, name_to_search,
						ft_strlen(ptr_export->name))))
			{
				free(ptr_export->value);
				ptr_export->value = ft_substr(cmd->argv[1], len_name + 1,
						ft_strlen(ft_strchr(cmd->argv[1], '=')));
				break ;
			}
			ptr_export = ptr_export->nxt;
		}
		if (ptr_export == NULL)
		{
			if (((ft_strchr(cmd->argv[1], '=')) + 1) == NULL)
			{
				ft_lstadd_back_new(&data->export,
					ft_lstnew_new(ft_substr(cmd->argv[1], 0, len_name),
						ft_strdup("")));
			}
			else
				ft_lstadd_back_new(&data->export,
					ft_lstnew_new(ft_substr(cmd->argv[1], 0, len_name),
						ft_substr(cmd->argv[1], len_name + 1,
							ft_strlen(ft_strchr(cmd->argv[1], '=')) + 1)));
		}
	}
	else
	{
		len_name = (ft_strlen(cmd->argv[1]));
		name_to_search = ft_substr(cmd->argv[1], 0, len_name);
		while (ptr_export != NULL)
		{
			if (!(ft_strncmp(ptr_export->name, name_to_search,
						ft_strlen(name_to_search)))
				&& !(ft_strncmp(ptr_export->name, name_to_search,
						ft_strlen(ptr_export->name))))
				return ;
			ptr_export = ptr_export->nxt;
		}
		ft_lstadd_back_new(&data->export,
			ft_lstnew_new(ft_substr(cmd->argv[1], 0, ft_strlen(cmd->argv[1])),
				ft_strdup("")));
	}
}

void	 exe_unset(t_data *data, t_exe *cmd)
{
	t_var	*ptr_env;
	t_var	*ptr_export;
	char	*name_to_search;

	ptr_env = data->vars;
	ptr_export = data->export;
	name_to_search = cmd->argv[1];
	while (ptr_env != NULL)
	{
		if (!ft_strncmp(ptr_env->name, name_to_search,
				ft_strlen(ptr_env->name)))
		{
			ft_lstdelone_new(&(data->vars), ptr_env, del);
			break ;
		}
		ptr_env = ptr_env->nxt;
	}
	while (ptr_export != NULL)
	{
		if (!ft_strncmp(ptr_export->name, name_to_search,
				ft_strlen(ptr_export->name)))
		{
			ft_lstdelone_new(&(data->export), ptr_export, del);
			break ;
		}
		ptr_export = ptr_export->nxt;
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
		printf("declare -x %s=\"%s\"\n", ptr->name, ptr->value);
		ptr = ptr->nxt;
	}
}
