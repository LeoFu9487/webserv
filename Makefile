NAME = webserv

CXX = clang++

CXXFLAGS = -Wall -Werror -Wextra -std=c++98 -fsanitize=address -D TEST

CONF_PATH = conf/

CONF_FILE = ServerInfo.cpp	parse_servers.cpp

SOCK_PATH = socket/

SOCK_FILE = create_listening_sockets.cpp

SRCS_PATH = srcs/

SRCS_FILE = main.cpp	utils.cpp

SRCS_FILE += $(addprefix $(CONF_PATH), $(CONF_FILE))

SRCS_FILE += $(addprefix $(SOCK_PATH), $(SOCK_FILE))

SRCS = $(addprefix $(SRCS_PATH), $(SRCS_FILE))

OBJS = $(SRCS:.cpp=.o)

HEADER_FILE = webserv.hpp	ServerInfo.hpp	exception.hpp	utils.hpp	conf.hpp\
socket.hpp

HEADER_PATH = includes/

HEADER = $(addprefix $(HEADER_PATH), $(HEADER_FILE))

all : $(NAME)
	echo "Compile OK"

$(NAME) : $(OBJS)
	$(CXX) $(CXXFLAGS) -I $(HEADER_PATH) $(OBJS) -o $(NAME)

%.o : %.cpp $(HEADER)
	$(CXX) $(CXXFLAGS) -I $(HEADER_PATH) -c $< -o $@

clean :
	rm -rf $(OBJS)
	echo "clean OK"

fclean :
	rm -rf $(OBJS) $(NAME)
	echo "fclean OK"

re : fclean all

.PHONY: all clean fclean re

.SILENT :
