NAME = minishell
CFLAGS = -Wall -Werror -Wextra
LDFLAGS = -lreadline -lncurses -fsanitize=address
SRCS = minishell.c \
		split_with_quotes.c \
		parsing.c \
		cmd_promt.c
OBJS = $(SRCS:.c=.o)
PATHLIBFT = lib/libft/
INLIBFT = -L $(PATHLIBFT) -lft

RED = '\033[1;31m'
BLUE ='\033[1;34m'
DEF_COLOR = '\033[0;39m'

$(NAME):		$(OBJS)
				@echo $(BLUE)"Compiling Libft..."$(DEF_COLOR)
				@cd $(PATHLIBFT) && $(MAKE) all
				@cd $(PATHLIBFT) && $(MAKE) bonus
				@echo $(BLUE)"Compiling $(NAME)..."$(DEF_COLOR)
				@cc $(OBJS) $(INLIBFT) -o $(NAME) $(LDFLAGS)

%.o:%.c
				@cc -c $< -o $@ $(CFLAGS)


all:			$(NAME)

clean:
				@echo $(RED)"Cleaning object files..."$(DEF_COLOR)
				@rm -f $(OBJS)
				@cd $(PATHLIBFT) && $(MAKE) clean

fclean:			clean
				@echo $(RED)"Cleaning executable files..."$(DEF_COLOR)
				@rm -f $(NAME)
				@cd $(PATHLIBFT) && $(MAKE) fclean

re:				fclean all

.PHONY:			all clean fclean re