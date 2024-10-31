NAME = philo_bonus
CC = cc

FLAGS = -Wall -Werror -Wextra -g

SRCS_MDIR = srcs/
OBJS_MDIR = objs/

HEADER = $(SRCS_MDIR)main_bonus.h

SRCS =	$(SRCS_MDIR)free_bonus.c \
    	$(SRCS_MDIR)init_bonus.c \
		$(SRCS_MDIR)main_bonus.c \
        $(SRCS_MDIR)routine_bonus.c \
        $(SRCS_MDIR)routine_take_fork_bonus.c \
        $(SRCS_MDIR)test_arg_bonus.c \
        $(SRCS_MDIR)utils_bonus.c

OBJS = $(patsubst $(SRCS_MDIR)%.c,$(OBJS_MDIR)%.o,$(SRCS))

$(OBJS_MDIR)%.o : $(SRCS_MDIR)%.c $(HEADER) | $(OBJS_MDIR)
	$(CC) $(FLAGS) -o $@ -c $<

$(NAME): $(OBJS) $(HEADER)
	$(CC) $(FLAGS) -o $@ $(OBJS) $(LIBFT_FLAG)

$(OBJS_MDIR) :
	mkdir -p $(OBJS_MDIR)

$(OBJS_BDIR) :
	mkdir -p $(OBJS_BDIR)

all : $(NAME)

sanitize : $(OBJS) $(HEADER)
	$(CC) $(FLAGS) -o $@ $(OBJS) $(LIBFT_FLAG) -fsanitize=thread -pthread

clean :
	rm -rf $(OBJS_MDIR)

fclean : clean
	rm -f $(NAME) sanitize

re : fclean $(OBJS_MDIR) $(NAME)
