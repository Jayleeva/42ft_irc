NAME = ft_IRC

SRC_DIR = ./src
OBJ_DIR = ./obj
DIR = ./obj ./obj/Command

SRC = 	main.cpp \
		Server.cpp \
		Client.cpp \
		Channel.cpp \
		Command.cpp \
		Command/join.cpp \
		
SRCS = $(addprefix $(SRC_DIR)/, $(SRC))

OBJ = $(SRC:.c=.o)
OBJS = $(addprefix $(OBJ_DIR)/, $(OBJ))

CC = c++
CFLAGS = -Wall -Wextra -Werror -std=C++98 -I ./inc -g 

INCLUDES = -I/usr/include

MKDIR = mkdir -p
RM = rm -rf

all: $(NAME)

$(DIR):
	$(MKDIR) $(DIR)

$(NAME): $(OBJS) | $(DIR)
	@${CC} ${CFLAGS} ${OBJS} -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(DIR)
	@$(CC) $(CFLAGS) -o $@ -c $< $(INCLUDES)

clean:
	@$(RM) $(OBJ_DIR)
fclean: clean
	@$(RM) $(NAME)
re: fclean all

.PHONY : all clean fclean re