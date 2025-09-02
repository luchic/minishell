
#include "ft_defines.h"
#include "minishell.h"
#include "libft.h"

extern char **environ;

// move to common utils later
int count_args(char **args)
{
    int count = 0;
    while (args && args[count])
        count++;
    return count;
}


int ft_cd_home(void)
{
    char *home;

    home = getenv("HOME");
    if (!home)
    {
        ft_putstr_fd("cd: HOME not set\n", 2);
        return (1);
    }
    if (chdir(home) != 0)
    {
        perror("cd");
        return (1);
    }
    return (0);
}

int ft_cd_oldpwd(char *oldpwd, char *pwd)
{
    if (!oldpwd)
    {
        ft_putstr_fd("cd: OLDPWD not set\n", 2);
        return (1);
    }
    if (chdir(oldpwd) != 0)
    {
        perror("cd");
        return (1);
    }
    pwd = getenv("PWD");
    if (pwd)
        ft_putstr_fd(pwd, 1);
    ft_putstr_fd("\n", 1);
    return (0);
}

int ft_cd_to_path(char *path)
{
    if (chdir(path) != 0)
    {
        perror("cd");
        return (1);
    }
    return (0);
}

//initialize new env var if not exist, else update existing one

void    update_env_var(const char *name, char *value, t_command *cmd)
{
    char *new;
    char *new_name;
    int  i;
    size_t new_size;

    new_name = ft_strjoin(name, "=");
    if (!new_name)
        return ;
    new_size = ft_strlen(new_name) + ft_strlen(value) + 1;
    new = (char *)malloc(new_size);
    if (!new)
        return ;
    ft_strlcpy(new, new_name, new_size);
    ft_strlcat(new, value, new_size);
    i = 0;
    while (cmd->mnsh->envp[i])
    {
        if (ft_strncmp(cmd->mnsh->envp[i], new_name, ft_strlen(new_name)) == 0)
        {
            free(cmd->mnsh->envp[i]);
            cmd->mnsh->envp[i] = new;
            return (free(new_name));
        }
        i++;
    }
    cmd->mnsh->envp = ft_realloc(cmd->mnsh->envp, sizeof(char *) * (i + 1), sizeof(char *) * (i + 2));
    if (!cmd->mnsh->envp)
        return (free(new_name), free(new));
    cmd->mnsh->envp[i] = new;
    cmd->mnsh->envp[i + 1] = NULL;
}


int ft_cd(t_command *cmd)
{   
    char pwd[1024];
    char oldpwd[1024];
    int status; //0 for success, 1 for failure

    getcwd(oldpwd, sizeof(oldpwd));
    getcwd(pwd, sizeof(pwd));
    if (count_args(cmd->args) > 2)
    {
        ft_putstr_fd("cd: too many arguments\n", 2);
        return (1);
    }
    if (!cmd->args[1] || ft_strcmp(cmd->args[1], "~") == 0)
        status = ft_cd_home();
    else if (cmd->args[1] && ft_strcmp(cmd->args[1], "-") == 0)
        status = ft_cd_oldpwd(oldpwd, pwd);
    else
        status = ft_cd_to_path(cmd->args[1]);
    if (status != 0)
        return (status);
    printf("Changed directory to: %s\n", cmd->args[1] ? cmd->args[1] : getenv("HOME"));
    update_env_var("OLDPWD", pwd, cmd); //update OLDPWD first
    getcwd(pwd, sizeof(pwd)); //get the newpwd
    update_env_var("PWD", pwd, cmd); //update PWD
    return (0);
}

/* int main(void)
{
    t_command cmd;
    t_minishell mnsh;
    
    ft_memset(&mnsh, 0, sizeof(t_minishell));
    mnsh.envp = malloc(sizeof(char *) * (count_args(environ) + 1));
    if (!mnsh.envp)
        return (1);
    int i = 0;
    while (environ[i])
    {
        mnsh.envp[i] = ft_strdup(environ[i]);
        if (!mnsh.envp[i])
        {
            while (i > 0)
                free(mnsh.envp[--i]);
            free(mnsh.envp);
            return (1);
        }
        i++;
    }
    mnsh.envp[i] = NULL;
    
    cmd.type = CMD_BUILTIN;
    cmd.fd_in = -1;
    cmd.fd_out = STDOUT_FILENO;
    cmd.name = "cd";
    cmd.mnsh = &mnsh;
    
    cmd.args = malloc(sizeof(char *) * 3);
    cmd.args[0] = "cd";
    cmd.args[1] = "..";
    cmd.args[2] = NULL;
    
    ft_cd(&cmd);
    free(cmd.args);
    free(mnsh.envp);
    return (0);
} */