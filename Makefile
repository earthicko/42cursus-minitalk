NAME			= minitalk
BONUS			= 

INC				= -I . -I includes -I includes_bonus -I includes_utils $(LIBFT_INC)

LIBFT			= libft.a
LIBFT_DIR		= libft
LIBFT_LIB		= -L libft libft/libft.a
LIBFT_INC		= -I libft

SRCDIR			= ./src/
SRCNAME			= \
				$(SRCDIR)sigcom/sigcom

SRCDIR_BONUS	= ./src_bonus/
SRCNAME_BONUS	= \
				$(SRCDIR_BONUS)sigcom/sigcom_bonus \
				$(SRCDIR_BONUS)sigcom/sigcom_ready_bonus \
				$(SRCDIR_BONUS)sigcom/sigcom_rx_bonus \
				$(SRCDIR_BONUS)sigcom/sigcom_tx_bonus \
				$(SRCDIR_BONUS)sigcom/sigcom_tx_sender_bonus

SRCDIR_UTILS	= ./utils/
SRCNAME_UTILS	= \
				$(SRCDIR_UTILS)ft_atoi_if_valid

SRC				= $(addsuffix .c, $(SRCNAME))
OBJ				= $(addsuffix .o, $(SRCNAME))
SRC_BONUS		= $(addsuffix .c, $(SRCNAME_BONUS))
OBJ_BONUS		= $(addsuffix .o, $(SRCNAME_BONUS))
SRC_UTILS		= $(addsuffix .c, $(SRCNAME_UTILS))
OBJ_UTILS		= $(addsuffix .o, $(SRCNAME_UTILS))

RM				= rm -f
CC				= gcc
CFLAGS			= -Wall -Wextra -Werror

all : $(NAME)

$(NAME) : $(OBJ) $(OBJ_UTILS) $(LIBFT) $(SRCDIR)server.o $(SRCDIR)client.o
	@$(CC) $(CFLAGS) $(INC) $(OBJ) $(OBJ_UTILS) $(SRCDIR)server.o -o server $(LIBFT_LIB)
	@$(CC) $(CFLAGS) $(INC) $(OBJ) $(OBJ_UTILS) $(SRCDIR)client.o -o client $(LIBFT_LIB)

bonus : $(OBJ_BONUS) $(OBJ_UTILS) $(LIBFT) $(SRCDIR_BONUS)server_bonus.o $(SRCDIR_BONUS)client_bonus.o
	@$(CC) $(CFLAGS) $(INC) $(OBJ_BONUS) $(OBJ_UTILS) $(SRCDIR_BONUS)server_bonus.o -o server $(LIBFT_LIB)
	@$(CC) $(CFLAGS) $(INC) $(OBJ_BONUS) $(OBJ_UTILS) $(SRCDIR_BONUS)client_bonus.o -o client $(LIBFT_LIB)

$(LIBFT) :
	make -C $(LIBFT_DIR) $(LIBFT)

%.o : %.c
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean :
	$(RM) $(OBJ_UTILS)
	$(RM) $(OBJ) $(SRCDIR)server.o $(SRCDIR)client.o
	$(RM) $(OBJ_BONUS) $(SRCDIR_BONUS)server_bonus.o $(SRCDIR_BONUS)client_bonus.o
	make clean -C $(LIBFT_DIR)

fclean : clean
	$(RM) server client
	make fclean -C $(LIBFT_DIR)

re :
	make fclean
	make all

.PHONY : all bonus clean fclean re
