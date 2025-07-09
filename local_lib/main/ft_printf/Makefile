
# ┌────────────────────────────────────────────────────────────┐
# │                    ft_printf/ Makefile                    │
# └────────────────────────────────────────────────────────────┘

CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDE = -Iinc
OBJDIR = obj

# Explicit source lists for 42 Norm compliance
SRCS_ENTRY = \
	entry/ft_printf.c \
	entry/ft_dprintf.c
SRCS_CORE = \
	core/formatter.c
SRCS_WRITER = \
	writer/write_char.c writer/write_str.c writer/write_nbr.c \
	writer/write_unsigned.c writer/write_hexa.c writer/write_ptr.c
SRCS = $(SRCS_ENTRY) $(SRCS_CORE) $(SRCS_WRITER)

# Object files
OBJS = $(SRCS:%.c=$(OBJDIR)/%.o)

# Default: build all object files
all: $(OBJS)

# Compile each source into OBJDIR, preserving structure
$(OBJDIR)/%.o: %.c inc/ft_printf.h
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

# Remove compiled objects
clean:
	rm -rf $(OBJDIR)

# fclean alias (no library to remove)
fclean: clean

# Rebuild all
re: fclean all

.PHONY: all clean fclean re
