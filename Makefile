NAME			= minitalk
BONUS			= 

INC				= -I . -I includes $(LIBFT_INC)

LIBFT		= libft.a
LIBFT_DIR	= libft
LIBFT_LIB	= -L libft libft/libft.a
LIBFT_INC	= -I libft

SRCDIR			= ./src/
SRCNAME			= \
				$(SRCDIR)sigcom/sigcom \
				$(SRCDIR)ft_atoi_if_valid

SRCDIR_BONUS	= ./src_bonus/
SRCNAME_BONUS	= 

SRC				= $(addsuffix .c, $(SRCNAME))
OBJ				= $(addsuffix .o, $(SRCNAME))
SRC_BONUS		= $(addsuffix .c, $(SRCNAME_BONUS)))
OBJ_BONUS		= $(addsuffix .o, $(SRCNAME_BONUS))

RM				= rm -f
CC				= gcc
CFLAGS			= -Wall -Wextra -Werror

all : $(NAME) client_test

$(NAME) : $(OBJ) $(LIBFT) $(SRCDIR)server.o $(SRCDIR)client.o
	@$(CC) $(CFLAGS) $(INC) $(OBJ) $(SRCDIR)server.o -o server $(LIBFT_LIB)
	@$(CC) $(CFLAGS) $(INC) $(OBJ) $(SRCDIR)client.o -o client $(LIBFT_LIB)

client_test : $(OBJ) $(LIBFT) client_test.o
	@$(CC) $(CFLAGS) $(INC) $(OBJ) client_test.o -o client_test $(LIBFT_LIB)

bonus : $(OBJ_BONUS) $(LIBFT) $(SRCDIR_BONUS)server.o $(SRCDIR_BONUS)client.o
	@$(CC) $(CFLAGS) $(INC) $(OBJ) $(SRCDIR_BONUS)server.o -o server $(LIBFT_LIB)
	@$(CC) $(CFLAGS) $(INC) $(OBJ) $(SRCDIR_BONUS)client.o -o client $(LIBFT_LIB)

$(LIBFT) :
	make -C $(LIBFT_DIR) $(LIBFT)

%.o : %.c
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean :
	$(RM) $(OBJ) $(SRCDIR)server.o $(SRCDIR)client.o client_test.o
	$(RM) $(OBJ_BONUS) $(SRCDIR_BONUS)server.o $(SRCDIR_BONUS)client.o
	make clean -C $(LIBFT_DIR)

fclean : clean
	$(RM) server client client_test
	make fclean -C $(LIBFT_DIR)

re :
	make fclean
	make all

.PHONY : all bonus clean fclean re
