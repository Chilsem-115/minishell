

#include "messh.h"
#include "ast_gen.h"

void	free_token(void *ptr)
{
	t_token	*token;

	token = (t_token *)ptr;
	if (token->text)
		ft_free(token->text);
	ft_free(token);
}

static void	ft_lstdelone_gc(t_list *lst, void (*del)(void*))
{
	if (!del)
		return ;
	if (lst)
	{
		(*del)(lst->content);
		ft_free(lst);
	}
}

void	ft_lstclear_gc(t_list **lst, void (*del)(void*))
{
	t_list	*tmp;

	if (!lst || !*lst || !del)
		return ;
	while (lst && *lst)
	{
		tmp = (*lst)->next;
		ft_lstdelone_gc(*lst, del);
		(*lst) = tmp;
	}
	*lst = NULL;
}
