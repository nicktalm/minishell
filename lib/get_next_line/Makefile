NAME = libftget_next_line.a
CFLAGS = -Wall -Werror -Wextra
SRCS = get_next_line.c get_next_line_utils.c
OBJS = $(SRCS:.c=.o)

$(NAME):		$(OBJS)
				@ar rc $(NAME) $(OBJS)

all:			$(NAME)

%.o: %.c
				@cc -c $< -o $@ $(CFLAGS)

clean:
				@rm -f $(OBJS)

fclean:			clean
				@rm -f $(NAME)

re:				fclean all

.PHONY: all clean fclean re
