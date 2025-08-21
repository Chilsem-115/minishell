
#include "expansion.h"

static int	precheck_consumed(int consumed)
{
	if (consumed < 0)
		return (-1);
	if (consumed == 0)
		return (0);
	if (consumed == 2)
		return (2);
	return (1);
}

static const char	*resolve_replacement(t_context *ctx, const char *name)
{
	t_env	*node;

	node = env_find_node(ctx->envp, name);
	if (node && node->value)
		return (node->value);
	return ("");
}

static int	apply_replacement(char **expanded, int pos, int consumed,
								const char *replacement)
{
	char	*new_str;

	new_str = str_replace_range(*expanded, (size_t)pos,
			(size_t)consumed, replacement);
	if (!new_str)
		return (-1);
	free(*expanded);
	*expanded = new_str;
	return (1);
}

static int	apply_qmark(char **expanded, int pos, int consumed, int code)
{
	char	*str;
	int		rc;

	str = ft_itoa(code);
	if (!str)
		return (-1);
	rc = apply_replacement(expanded, pos, consumed, str);
	printf("%s is the value of the qweoqoiejqwo\n", str);
	free(str);
	return (rc);
}

int	replace_one_at(char **expanded, int pos, t_context *ctx)
{
	char		*name;
	const char	*replacement;
	int			consumed;
	int			rc;

	name = NULL;
	replacement = "";
	consumed = grab_variable(*expanded, pos, &name);
	rc = precheck_consumed(consumed);
	if (rc == -1 || rc == 0)
		return (rc);
	if (rc == 2)
		return (apply_qmark(expanded, pos, consumed, ctx->exit_code));
	replacement = resolve_replacement(ctx, name);
	rc = apply_replacement(expanded, pos, consumed, replacement);
	free(name);
	return (rc);
}
