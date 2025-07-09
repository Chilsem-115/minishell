
# ┌────────────────────────────────────────────────────────────┐
# │                     Root-level Makefile                   │
# └────────────────────────────────────────────────────────────┘

CC      = cc
CFLAGS  = -Wall -Wextra -Werror -Ilocal_lib -Imain -Imain/tokenizer
NAME    = mesh
OBJDIR  = obj
LIBFT_DIR = local_lib
LIBFT    = $(LIBFT_DIR)/libft.a

# === Sources ===
SRC_MAIN = \
	main/messh.c

SRC_TOKENIZER = \
	main/tokenizer/tokenize.c \
	main/tokenizer/handle_events/quote.c \
	main/tokenizer/handle_events/redirect.c \
	main/tokenizer/handle_events/control.c \
	main/tokenizer/handle_events/errors/err_handler.c \
	main/tokenizer/handle_events/word.c

# Add more later as needed
SRCS = $(SRC_MAIN) $(SRC_TOKENIZER)

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
