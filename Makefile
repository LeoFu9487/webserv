NAME = webserv

CXX = clang++

CXXFLAGS = -Wall -Werror -Wextra -std=c++98

SRCS_PATH = srcs/

SRCS_FILE = main.cpp

SRCS = $(addprefix $(SRCS_PATH), $(SRCS_FILE))

OBJS = $(SRCS:.cpp=.o)

#PUT HEADERS HERE
HEADER_FILE = webserv.hpp

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
