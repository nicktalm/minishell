NAME = minishell
CFLAGS = -Wall -Werror -Wextra
LDFLAGS = -lreadline -lncurses -fsanitize=address #-L /Users/lbohm/LeakSanitizer -llsan
SRCS = minishell.c \
		cmd_prompt.c \
		quotes.c \
		quotes_utils.c \
		token.c \
		fill_struct.c \
		fill_struct_utils.c \
		execute.c \
		builtins.c \
		init_env.c \
		free.c \
		sort_export.c
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
				@cc $(OBJS) $(INLIBFT) $(INGETNEXT) -o $(NAME) $(LDFLAGS)

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