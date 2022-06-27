NAME    	= receiver
CC      	= c++
RM			= rm -rf

srcs		= receiver.cpp\
			  client.cpp\
			  event.cpp\
			  socket.cpp\
			  worker.cpp

SRCS    	= $(srcs:%=srcs/%)

OBJS		= $(SRCS:srcs/%.cpp=objs/%.o)

all     	: $(NAME)

objs/%.o   	: srcs/%.cpp
	@mkdir -p $(dir ./objs/$*)
	$(CC) -c $< -o $@

$(NAME) 	: $(OBJS)
	$(CC) $(OBJS) -o $(NAME)

clean   	:
	$(RM) ./objs

fclean    	: clean
	$(RM) $(NAME)

re			: fclean all

.PHONY		: all clean fclean re
