#include "minishell.h"

void	print_lst(t_list *lst)
{
	t_list	*tmp;

	tmp = lst;
	while (tmp)
	{
		printf("%s\n", (char *)tmp->content);
		tmp = tmp->next;
	}
}

void	print_tokens_var(t_list *tokens)
{
	t_list	*tmp;

	tmp = tokens;
	while (tmp)
	{
		if (((t_token *)tmp->content)->token == CMD)
			printf("CMD ");
		else if (((t_token *)tmp->content)->token == PIPE)
			printf("PIPE ");
		else if (((t_token *)tmp->content)->token == D_PIPE)
			printf("D_PIPE ");
		else if (((t_token *)tmp->content)->token == D_REDIR_IN)
			printf("D_REDIR_IN ");
		else if (((t_token *)tmp->content)->token == D_REDIR_OUT)
			printf("D_REDIR_OUT ");
		else if (((t_token *)tmp->content)->token == REDIR_IN)
			printf("REDIR_IN ");
		else if (((t_token *)tmp->content)->token == REDIR_OUT)
			printf("REDIR_OUT ");
		else if (((t_token *)tmp->content)->token == AND)
			printf("AND ");
		else if (((t_token *)tmp->content)->token == WILDCARD)
			printf("WILDCARD ");
		else if (((t_token *)tmp->content)->token == VAR)
			printf("VAR ");
		else if (((t_token *)tmp->content)->token == OPEN_P)
			printf("OPEN_P ");
		else if (((t_token *)tmp->content)->token == CLOSE_P)
			printf("CLOSE_P ");
		else
			printf("WORD ");
		tmp = tmp->next;
	}
	printf("\n");
}

void print_tokens(t_list *tokens, int mode)
{
  t_list  *tmp;
  t_token *token;

  if (!mode)
    print_tokens_var(tokens);
  else
  {
    tmp = tokens;
    while (tmp)
    {
      token = (t_token *)tmp->content;
      printf("%s", token->str);
      tmp = tmp->next;
    }
    printf("\n");
  }
}
