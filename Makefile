NAME = philo
BONUS_NAME = bonus
CC = cc

FLAGS = -Wall -Werror -Wextra -g

SRCS_MDIR = srcs/mandatory/
SRCS_BDIR = srcs/bonus/
OBJS_MDIR = objs/mandatory/
OBJS_BDIR = objs/bonus/

HEADER = $(SRCS_MDIR)main.h
BONUS_HEADER = $(SRCS_BDIR)philo_bonus.h

SRCS = $(SRCS_MDIR)routine.c \
		$(SRCS_MDIR)free.c \
		$(SRCS_MDIR)init.c \
		$(SRCS_MDIR)main.c \
		$(SRCS_MDIR)test_arg.c \
		$(SRCS_MDIR)utils.c \


BONUS_SRCS = 

OBJS = $(patsubst $(SRCS_MDIR)%.c,$(OBJS_MDIR)%.o,$(SRCS))

BONUS_OBJS = $(patsubst $(SRCS_BDIR)%.c,$(OBJS_BDIR)%.o,$(BONUS_SRCS))

$(OBJS_MDIR)%.o : $(SRCS_MDIR)%.c $(HEADER) | $(OBJS_MDIR)
	$(CC) $(FLAGS) -o $@ -c $<

$(OBJS_BDIR)%.o : $(SRCS_BDIR)%.c $(BONUS_HEADER) | $(OBJS_BDIR)
	$(CC) $(FLAGS) -o $@ -c $<

$(NAME): $(OBJS) $(HEADER)
	$(CC) $(FLAGS) -o $@ $(OBJS) $(LIBFT_FLAG)

$(BONUS_NAME): $(BONUS_OBJS) $(BONUS_HEADER)
	$(CC) $(FLAGS) -o $@ $(BONUS_OBJS) $(LIBFT_FLAG)

$(OBJS_MDIR) :
	mkdir -p $(OBJS_MDIR)

$(OBJS_BDIR) :
	mkdir -p $(OBJS_BDIR)

all : $(NAME) $(BONUS_NAME)

sanitize : $(OBJS) $(HEADER)
	$(CC) $(FLAGS) -o $@ $(OBJS) $(LIBFT_FLAG) -fsanitize=thread -pthread

clean :
	rm -rf $(OBJS_MDIR) $(OBJS_BDIR)

fclean : clean
	rm -f $(NAME) $(BONUS_NAME) sanitize
	rm -rf $(OBJS_MDIR) $(OBJS_BDIR)

re : fclean $(OBJS_MDIR) $(NAME)

