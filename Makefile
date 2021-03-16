NAME 			=	minishell
OBJS_PATH		=	objects/
SRCS_PATH		=	source/
HEAD_PATH		=	includes/

SRCS_LIST 		=	main.c test.c ft_parse.c

SRCS			=	$(addprefix $(SRCS_PATH), $(SRCS_LIST))	
OBJS_LIST		=	$(patsubst %.c, %.o, $(SRCS_LIST))
OBJS			=	$(addprefix $(OBJS_PATH),$(OBJS_LIST))
RM				=	rm -rf
MAKE_LIBFT		=	make -C libs/libft

CC 				=	gcc
CFLAGS			=	-O2 -Wall -Wextra -Werror -I $(HEAD_PATH)
OFLAGS			=	-O2 -Wall -Wextra -Werror -c -I $(HEAD_PATH)
DFLAGS			=	-g -I $(HEAD_PATH)
LIBFT			= 	libs/libft/libft.a

all: $(NAME) 
$(NAME): $(OBJS_PATH) $(OBJS) $(HEAD_PATH) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT)  -o $(NAME)

$(OBJS_PATH):
	mkdir -p $(OBJS_PATH)

$(OBJS_PATH)%.o : $(SRCS_PATH)%.c  $(HEAD_PATH)	
	$(CC) $(OFLAGS) $< -o $@

$(LIBFT):
	$(MAKE_LIBFT)

debug:
	$(CC) -I $(HEAD_PATH) $(CFLAGS) $(SRCS) libft.a $(LIBFT)  -o $(NAME)

run:debug
	./minishell
test: test.c;
	$(CC) libft.a test.c -o test

testrun:test
	@./test
clean:
	$(MAKE_LIBFT) clean
	$(RM) $(OBJS_PATH)

fclean: clean
	$(MAKE_LIBFT) fclean
	$(RM) $(NAME)

re: fclean all