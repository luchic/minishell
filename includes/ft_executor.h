
#ifndef FT_EXECUTOR_H
# define FT_EXECUTOR_H

# include "ft_common.h"
# include "ft_defines.h"
# include "ft_printf.h"
# include "libft.h"
# include "minishell.h"

// ======================== executor ========================
int		execute_script(t_minishell *mnsh, t_ast_node *script);
int		execute_node(t_minishell *mnsh, t_ast_node *node);

int		execute_command(t_minishell *mnsh, t_command *cmd);
int		execute_command_pipeline(t_minishell *mnsh, t_command *cmd);
int		execute_logical(t_minishell *mnsh, t_logical_expression *logic);
int		execute_pipeline(t_minishell *mnsh, t_pipeline *pipeline);
int		execute_subshell(t_minishell *mnsh, t_subshell *subsh);

// void	setup_child_io(t_command *cmd);

// ======================== pipes utils========================
pid_t	fork_and_exe(t_pipeline *pipeline, int i, int fds[2], int pipe_fds[2]);
int		finish_execution(pid_t *pids, int count);
// void	close_pipes(int pipe_fds[2]);

// ======================== exe_cmd_utils ========================
int		preprocess_cmd(t_command *cmd);
int		execute_dispatcher(t_command *cmd, int in_pipeline);
void	close_previous_fd(int fd_to_close);
int		restore_check(t_command *cmd);

// ======================== assignments ========================
char	**handle_assignments(t_minishell *mnsh, t_list *assignments);
void	handle_assignments_and_run(t_minishell *mnsh, t_command *cmd,
		int *status, int (*run_func)(t_command *));
void	update_underscore(t_minishell *mnsh, t_command *cmd);

// ======================== cmd_built_in ========================
int		run_builtin(t_command *cmd);
int		match_built_in(t_command *cmd);

// ft_cd & helpers
int		ft_cd(t_command *cmd);
void	change_env_var(const char *name, char *value, t_command *cmd);
int		ft_cd_home(void);
int		ft_cd_oldpwd(char *oldpwd, char *pwd);
int		ft_cd_to_path(char *path);

int		ft_echo(t_command *cmd);
int		ft_exit(t_command *cmd);
int		ft_pwd(t_command *cmd);
int		ft_env(t_command *cmd);
int		ft_export(t_command *cmd);
void	ft_export_print_env(char **envp, int fd);
int		ft_unset(t_command *cmd);

// cmd_export helpers && cmd_assignments helpers

void	ft_export_print_env(char **envp, int fd);
int		is_valid_identifier(char *str);
void	update_env_var(char *arg, char ***envp);
void	replace_env_var(char **env_var, char *new_var);
void	append_env_var(char ***envp, char *new_var);

// ======================== cmd_external ========================
int		run_external(t_command *cmd);
int		run_external_no_fork(t_command *cmd);
char	*get_cmd_path(char *cmd_name, char **envp);

// ======================== redirections ========================
int		handle_redirections(t_command *cmd);
void	close_previous_fd(int fd_to_close);
// int		handle_input_redirection(t_command *cmd, const char *path);
int		open_input_file(const char *path);
int		open_output_file(const char *path, int append);
// int		handle_output_redirection(t_command *cmd, const char *path, int append);
int		handle_heredoc(t_redirection *redir, t_command *cmd);
int		ft_is_limiter(char *line, char *del);
void	ft_write_data_to_std(char *del, int fd);

#endif
