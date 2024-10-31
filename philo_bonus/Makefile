NAME = philo/philo
BONUS_NAME = philo_bonus/philo_bonus
CC = cc

FLAGS = -Wall -Werror -Wextra -g

SRCS_MDIR = srcs/
OBJS_MDIR = objs/

HEADER = $(SRCS_MDIR)main.h

SRCS = $(SRCS_MDIR)routine.c \
		$(SRCS_MDIR)free.c \
		$(SRCS_MDIR)init.c \
		$(SRCS_MDIR)main.c \
		$(SRCS_MDIR)meal_counter.c \
		$(SRCS_MDIR)test_arg.c \
		$(SRCS_MDIR)utils.c

BONUS_SRCS = $(SRCS_BDIR)free_bonus.c \
             $(SRCS_BDIR)init_bonus.c \
             $(SRCS_BDIR)main_bonus.c \
             $(SRCS_BDIR)routine_bonus.c \
             $(SRCS_BDIR)routine_take_fork_bonus.c \
             $(SRCS_BDIR)test_arg_bonus.c \
             $(SRCS_BDIR)utils_bonus.c

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
	rm -rf $(OBJS_MDIR)

re : fclean $(OBJS_MDIR) $(NAME)
