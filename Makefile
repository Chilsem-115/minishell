
# ┌────────────────────────────────────────────────────────────┐
# │                     Root-level Makefile                   │
# └────────────────────────────────────────────────────────────┘

CC      = cc
CFLAGS = -Wall -Wextra -Werror -Ilibft -Imain \
		 -Imain/tokenizer -Imain/ast_generator \
		 -Imain/ast_generator/ast \
		 -Imain/ast_generator/ast/utils
NAME    = mesh
OBJDIR  = obj
LIBFT_DIR = libft
LIBFT    = $(LIBFT_DIR)/libft.a

# === Sources ===
SRC_MAIN = \
	main/messh.c \
	main/print_ast.c

SRC_TOKENIZER = \
	main/tokenizer/tokenize.c \
	main/tokenizer/handle_events/quote.c \
	main/tokenizer/handle_events/redirect.c \
	main/tokenizer/handle_events/control.c \
	main/tokenizer/handle_events/handler.c \
	main/tokenizer/handle_events/env.c \
	main/tokenizer/handle_events/errors/err_handler.c \

SRC_AST_GEN = \
	main/ast_generator/ast_gen.c \
	main/ast_generator/ast/ast.c \
	main/ast_generator/ast/create_node.c \
	main/ast_generator/ast/utils/command_utils.c \
	main/ast_generator/ast/utils/type_mapping.c

# Add more later as needed
SRCS = $(SRC_MAIN) $(SRC_TOKENIZER) $(SRC_AST_GEN)

# === Object files ===
OBJS = $(SRCS:%.c=$(OBJDIR)/%.o)

# === Default ===
all: $(LIBFT) $(NAME)

# === Build main binary ===
$(NAME): $(OBJS)
	@echo " Linking $@"
	$(CC) $(CFLAGS) -o $@ $^ -L$(LIBFT_DIR) -lft -lreadline

# === Compile rule ===
$(OBJDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@echo " Compiling $<"
	$(CC) $(CFLAGS) -c $< -o $@

# === Build libft ===
$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

# === Clean ===
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
