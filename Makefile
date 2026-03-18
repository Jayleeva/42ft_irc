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
		utils.cpp

SRCS = $(addprefix $(SRC_DIR)/, $(SRC))

OBJ = $(SRCS:.cpp=.o)
#OBJS = $(addprefix $(OBJ_DIR)/, $(OBJ))

CC = c++
CPPFLAGS = -Wall -Wextra -Werror -std=c++98 -I ./inc -g 

MKDIR = mkdir -p
RM = rm -rf

all: $(NAME)

$(DIR):
	$(MKDIR) $(DIR)

$(NAME): $(OBJ) #| $(DIR)
	$(CC) $(CPPFLAGS) $(OBJ) -o $(NAME)
# $(OBJ_DIR) instead of OBJ

#$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(DIR)
#	@$(CC) $(CFLAGS) -o $@ -c $< $(INCLUDES)

clean:
	$(RM) $(OBJ)
# $(OBJ_DIR) instead of OBJ

fclean: clean
	$(RM) $(NAME)

re: fclean $(NAME)

.PHONY: all clean fclean re