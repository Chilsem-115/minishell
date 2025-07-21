
CC      = cc
CFLAGS  = -Wall -Wextra -Werror
AR      = ar rcs
INCLUDE = -I.
OBJDIR  = obj
NAME    = libft.a

# Module directories
ASCII_DIR        = main/ascii
CONVERSION_DIR   = main/conversion
LIST_DIR         = main/linked_list
MEMORY_DIR       = main/memory
STDIO_DIR        = main/stdio
STRING_DIR       = main/string
STRUTILS_DIR     = main/strutils
GNL_DIR          = main/get_next_line
PRINTF_SUBDIR    = main/ft_printf

# Source files by category
ASCII_SRCS       = \
	$(ASCII_DIR)/ft_isalpha.c \
	$(ASCII_DIR)/ft_isalnum.c \
	$(ASCII_DIR)/ft_isdigit.c \
	$(ASCII_DIR)/ft_isascii.c \
	$(ASCII_DIR)/ft_isprint.c \
	$(ASCII_DIR)/ft_tolower.c \
	$(ASCII_DIR)/ft_toupper.c \
	$(ASCII_DIR)/ft_isspace.c

CONVERSION_SRCS  = \
	$(CONVERSION_DIR)/ft_atoi.c \
	$(CONVERSION_DIR)/ft_itoa.c

LIST_SRCS        = \
	$(LIST_DIR)/ft_lstnew_bonus.c \
	$(LIST_DIR)/ft_lstadd_front_bonus.c \
	$(LIST_DIR)/ft_lstadd_back_bonus.c \
	$(LIST_DIR)/ft_lstdelone_bonus.c \
	$(LIST_DIR)/ft_lstclear_bonus.c \
	$(LIST_DIR)/ft_lstiter_bonus.c \
	$(LIST_DIR)/ft_lstlast_bonus.c \
	$(LIST_DIR)/ft_lstmap_bonus.c \
	$(LIST_DIR)/ft_lstsize_bonus.c

MEMORY_SRCS      = \
	$(MEMORY_DIR)/ft_bzero.c \
	$(MEMORY_DIR)/ft_calloc.c \
	$(MEMORY_DIR)/ft_memchr.c \
	$(MEMORY_DIR)/ft_memcmp.c \
	$(MEMORY_DIR)/ft_memcpy.c \
	$(MEMORY_DIR)/ft_memmove.c \
	$(MEMORY_DIR)/ft_memset.c \
	$(MEMORY_DIR)/ft_realloc.c

STDIO_SRCS       = \
	$(STDIO_DIR)/ft_putchar_fd.c \
	$(STDIO_DIR)/ft_putstr_fd.c \
	$(STDIO_DIR)/ft_putendl_fd.c \
	$(STDIO_DIR)/ft_putnbr_fd.c

STRING_SRCS      = \
	$(STRING_DIR)/ft_strlen.c \
	$(STRING_DIR)/ft_strlcpy.c \
	$(STRING_DIR)/ft_strlcat.c \
	$(STRING_DIR)/ft_strchr.c \
	$(STRING_DIR)/ft_strrchr.c \
	$(STRING_DIR)/ft_strncmp.c \
	$(STRING_DIR)/ft_strnstr.c \
	$(STRING_DIR)/ft_strcpy.c \
	$(STRING_DIR)/ft_strncpy.c \
	$(STRING_DIR)/ft_strdup.c \
	$(STRING_DIR)/ft_strndup.c

STRUTILS_SRCS    = \
	$(STRUTILS_DIR)/ft_substr.c \
	$(STRUTILS_DIR)/ft_strjoin.c \
	$(STRUTILS_DIR)/ft_strtrim.c \
	$(STRUTILS_DIR)/ft_split.c \
	$(STRUTILS_DIR)/ft_strmapi.c \
	$(STRUTILS_DIR)/ft_striteri.c

GNL_SRCS         = \
	$(GNL_DIR)/get_next_line.c \
	$(GNL_DIR)/get_next_line_utils.c

# Pre-built printf objects from submodule
PRINTF_OBJS      = \
	$(PRINTF_SUBDIR)/obj/entry/ft_printf.o \
	$(PRINTF_SUBDIR)/obj/entry/ft_dprintf.o \
	$(PRINTF_SUBDIR)/obj/core/formatter.o \
	$(PRINTF_SUBDIR)/obj/writer/write_char.o \
	$(PRINTF_SUBDIR)/obj/writer/write_str.o \
	$(PRINTF_SUBDIR)/obj/writer/write_nbr.o \
	$(PRINTF_SUBDIR)/obj/writer/write_unsigned.o \
	$(PRINTF_SUBDIR)/obj/writer/write_hexa.o \
	$(PRINTF_SUBDIR)/obj/writer/write_ptr.o

# Combine all sources
SRCS             = \
	$(ASCII_SRCS) \
	$(CONVERSION_SRCS) \
	$(LIST_SRCS) \
	$(MEMORY_SRCS) \
	$(STDIO_SRCS) \
	$(STRING_SRCS) \
	$(STRUTILS_SRCS) \
	$(GNL_SRCS)

# Object files for root compilation
OBJS_OWN         = $(SRCS:%.c=$(OBJDIR)/%.o)
OBJS             = $(OBJS_OWN) $(PRINTF_OBJS)

.PHONY: all printf clean fclean re

# Default: build printf submodule then library
all: printf $(NAME)

# Build ft_printf submodule
printf:
	@$(MAKE) -C $(PRINTF_SUBDIR)

# Archive all objects into libft.a
$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)

# Compile own sources into OBJDIR
$(OBJDIR)/%.o: %.c libft.h
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

# Clean compiled objects and submodule
clean:
	@$(MAKE) -C $(PRINTF_SUBDIR) clean
	rm -rf $(OBJDIR)

# fclean also removes library and submodule archive
fclean: clean
	@$(MAKE) -C $(PRINTF_SUBDIR) fclean
	rm -f $(NAME)

# Rebuild all
re: fclean all
