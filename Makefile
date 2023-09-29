NAME = server client
CC = cc
CFLAGS = -Wall -Werror -Wextra
LIBFT = ./libft/libft.a
INCLUDES = -I./include  -I./libft/include
SRC_DIR = src
OBJ_DIR = obj
SERVER_SRCS = server.c
CLIENT_SRCS = client.c utils.c
SERVER_OBJS = $(addprefix $(OBJ_DIR)/, $(notdir $(SRCS:.c=.o)))
BONUS_OBJS = $(addprefix $(OBJ_DIR)/, $(notdir $(BONUS_SRCS:.c=.o)))
SERVER_OBJS = $(addprefix $(OBJ_DIR)/server/, $(SERVER_SRCS:.c=.o))
CLIENT_OBJS = $(addprefix $(OBJ_DIR)/client/, $(CLIENT_SRCS:.c=.o))

all: $(NAME) $(LIBFT)

$(OBJ_DIR)/server/%.o : $(SRC_DIR)/server/%.c
	@mkdir -p $(OBJ_DIR)/server
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR)/client/%.o : $(SRC_DIR)/client/%.c
	@mkdir -p $(OBJ_DIR)/client
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

server: $(SERVER_OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^ 

client: $(CLIENT_OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^

bonus: $(NAME) $(LIBFT)

$(LIBFT):
	@$(MAKE) -C ./libft
	@echo "$(GREEN) Libft compiled $(RESET)"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@  

clean:
	rm -rf $(OBJ_DIR)/server
	rm -rf $(OBJ_DIR)/client
	$(MAKE) -C ./libft clean

fclean: clean
	rm -f $(NAME) 
	$(MAKE) -C ./libft fclean

re: fclean all

.PHONY: all clean fclean re bonus
