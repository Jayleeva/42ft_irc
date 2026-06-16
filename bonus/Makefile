NAME = ircserv

SRC_DIR = src
OBJ_DIR = obj

SRC = 	main.cpp \
		Server.cpp \
		Client.cpp \
		Channel.cpp \
		utils.cpp \
		parsing.cpp \
		Command.cpp \
		Bot.cpp \
		Command/pass.cpp \
		Command/nick.cpp \
		Command/user.cpp \
		Command/join.cpp \
		Command/invite.cpp \
		Command/mode.cpp \
		Command/kick.cpp \
		Command/part.cpp \
		Command/privmsg.cpp \
		Command/topic.cpp \
		


SRCS = $(addprefix $(SRC_DIR)/, $(SRC))
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))

CC = c++
CPPFLAGS = -Wall -Wextra -Werror -std=c++98 -I ./include -g

MKDIR = mkdir -p
RM = rm -rf

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CPPFLAGS) $(OBJS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@$(MKDIR) $(dir $@)
	$(CC) $(CPPFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME) valgrind.log

re: fclean all

leaks:	all
	valgrind -s --leak-check=full --log-file=valgrind.log --show-leak-kinds=all --track-fds=all --default-suppressions=yes ./$(NAME) 6667 password

.PHONY: all clean fclean re