
#include "messh.h"
#include "ast_gen.h"

static void	free_cmd_node(t_cmd_node *c)
{
	size_t	i;

	if (!c || !c->text)
		return ;
	i = 0;
	while (c->text[i])
		ft_free(c->text[i++]);
	ft_free(c->text);
}

static void	free_rec(t_ast_node *n)
{
	if (!n)
		return ;
	if (n->type == AST_CONTROL)
	{
		free_rec(n->data.ctrl.left);
		free_rec(n->data.ctrl.right);
	}
	else if (n->type == AST_REDIR)
	{
		free_rec(n->data.redir.child);
		ft_free(n->data.redir.file);
	}
	else
		free_cmd_node(&n->data.cmd);
	ft_free(n);
}

void	ast_clear(t_ast_node **root)
{
	t_ast_node	*tmp;

	if (!root || !*root)
		return ;
	tmp = *root;
	*root = NULL;
	free_rec(tmp);
}
