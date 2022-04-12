#include "minishell.h"

void    free_tokens(t_token *tokens)
{
    int i;

    i = -1;
    while (tokens[++i].str)
        free(tokens[i].str);
    free(tokens);
}

void    exit_cmd(int exit_code, t_data *data)
{
    free(data->line);
    free_tab(data->path);
    free_tokens(data->tokens);
    exit(exit_code);
}
