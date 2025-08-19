
# ┌────────────────────────────────────────────────────────────┐
# │                     Root-level Makefile                   │
# └────────────────────────────────────────────────────────────┘

# === Compiler and Flags ===
CC      = cc
CFLAGS  = -g  \
		  -Ilibft \
		  -Imain \
		  -Imain/tokenizer \
		  -Imain/tokenizer/handle_events \
		  -Imain/tokenizer/handle_events/errors \
		  -Imain/ast_generator \
		  -Imain/ast_generator/ast \
		  -Imain/ast_generator/ast/utils \
		  -Imain/ast_generator/error \
		  -Imain/execution \
		  -Imain/execution/pipe \
		  -Imain/execution/redirection \
		  -Imain/execution/environment

NAME    = minishell
OBJDIR  = obj
LIBFT_DIR = libft
LIBFT    = $(LIBFT_DIR)/libft.a

# === Sources ===
SRC_MAIN = \
	main/messh.c \
	main/print_func.c \
	main/core.c

SRC_TOKENIZER = \
	main/tokenizer/tokenize.c \
	main/tokenizer/handle_events/quote.c \
	main/tokenizer/handle_events/redirect.c \
	main/tokenizer/handle_events/control.c \
	main/tokenizer/handle_events/handler.c \
	main/tokenizer/handle_events/env.c \
	main/tokenizer/handle_events/errors/err_handler.c

SRC_AST_GEN = \
	main/ast_generator/ast_gen.c \
	main/ast_generator/ast/ast.c \
	main/ast_generator/ast/create_node.c \
	main/ast_generator/ast/utils/command_utils.c \
	main/ast_generator/ast/utils/type_mapping.c \
	main/ast_generator/error/error_handling.c

SRC_EXEC = \
	main/execution/cmd_execute/execute.c \
	main/execution/cmd_execute/execute_utls.c \
	main/execution/built_in/btn_utils.c \
	main/execution/environment/env.c \
	main/execution/built_in/export.c \
	main/execution/built_in/built_in.c \
	main/execution/redirection/heredoc.c \
	main/execution/redirection/redir.c \
	main/execution/pipe/pipe.c \
	main/execution/garbage_col.c 

# === Source & Object Management ===
SRCS = $(SRC_MAIN) $(SRC_TOKENIZER) $(SRC_AST_GEN) $(SRC_EXEC)
OBJS = $(SRCS:%.c=$(OBJDIR)/%.o)

# === Targets ===
all: $(LIBFT) $(NAME)

$(NAME): $(OBJS)
	@echo " Linking $@"
	$(CC) $(CFLAGS) -o $@ $^ -L$(LIBFT_DIR) -lft -lreadline

# === Object compilation ===
$(OBJDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@echo " Compiling $<"
	$(CC) $(CFLAGS) -c $< -o $@

# === Libft ===
$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

# === Cleaning ===
clean:
	@echo " Cleaning object files..."
	@rm -rf $(OBJDIR)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	@echo " Removing binary..."
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
