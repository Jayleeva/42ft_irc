NAME = ft_IRC

#SRC_DIR = ./src
#OBJ_DIR = ./obj
#DIR = ./obj ./obj/Command

SRC = 	src/main.cpp \
		src/Server.cpp \
		src/Client.cpp \
		src/Channel.cpp \
		src/Command.cpp \
		src/Command/join.cpp \

#SRCS = $(addprefix $(SRC_DIR)/, $(SRC))

OBJ = $(SRC:.cpp=.o)
#OBJS = $(addprefix $(OBJ_DIR)/, $(OBJ))

CC = c++
CPPFLAGS = -Wall -Wextra -Werror -std=c++98 -I ./inc -g 

#MKDIR = mkdir -p
RM = rm -rf

all: $(NAME)

#$(DIR):
#	$(MKDIR) $(DIR)

$(NAME): $(OBJ) #$(OBJS) | $(DIR)
	$(CC) $(CPPFLAGS) $(OBJ) -o $(NAME) 
#${OBJS} instead of OBJ

#$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(DIR)
#	@$(CC) $(CFLAGS) -o $@ -c $< $(INCLUDES)

clean:
	$(RM) $(OBJ)
# $(OBJ_DIR) instead of OBJ

fclean: clean
	$(RM) $(NAME)

re: fclean $(NAME)

.PHONY: all clean fclean re