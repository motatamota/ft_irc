CPP = c++
CPP_FLAGS = -Wall -Werror -Wextra -std=c++98

PROGRAM_NAME = ircserv

SRCDIR := ./src
CLASSDIR := class
INCDIR := ./includes

SRC := $(SRCDIR)/main.cpp
SRC += $(SRCDIR)/$(CLASSDIR)/Channel.cpp $(SRCDIR)/$(CLASSDIR)/ErrorCode.cpp $(SRCDIR)/$(CLASSDIR)/Everyone.cpp $(SRCDIR)/$(CLASSDIR)/MessageTranslator.cpp $(SRCDIR)/$(CLASSDIR)/RefCounted.cpp $(SRCDIR)/$(CLASSDIR)/Sender.cpp $(SRCDIR)/$(CLASSDIR)/SocketServer.cpp

INCLUDES := -I$(INCDIR)

OBJDIR := objs
OBJS := $(SRC:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
OBJS := $(OBJS:$(SRCDIR)/$(CLASSDIR)/%.cpp=$(OBJDIR)/$(CLASSDIR)/%.o)

all: $(PROGRAM_NAME)

obj: $(OBJS)

$(PROGRAM_NAME): $(OBJS)
	$(CPP) $(CPP_FLAGS) $(INCLUDES) -o $@ $^

$(OBJDIR):
	@mkdir -p $(OBJDIR)/$(CLASSDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CPP) $(CPP_FLAGS) $(INCLUDES) -o $@ -c $<

$(OBJDIR)/$(CLASSDIR)/%.o: $(CLASSDIR)/%.cpp | $(OBJDIR)
	$(CPP) $(CPP_FLAGS) $(INCLUDES) -o $@ -c $<

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(PROGRAM_NAME)

re: fclean all

.PHONY: all clean fclean re
