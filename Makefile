NAME	:= pipex

CFLAGS	:= -Wextra -Wall -Werror

HEADERS	:= -I ./inc

SRCDIR := ./src/

SRCS	:=  $(SRCDIR)pipex.c \
			$(SRCDIR)utils.c

OBJS	:= ${SRCS:.c=.o}

CC		:= gcc

all: $(NAME)

libft:
	@make -C ./lib/printf

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)"

$(NAME): $(OBJS) libft
	@$(CC) $(OBJS) $(LIBS) ./lib/printf/libftprintf.a $(HEADERS) -o $(NAME)

clean:
	@make -C ./lib/printf clean
	@rm -rf $(OBJS)

fclean: clean
	@make -C ./lib/printf fclean
	@rm -rf $(NAME)

re: clean all

.PHONY: all, clean, fclean, re
