TARGET := spaceinvader
CC := g++

SRCS_FOLDER := src
INCLUDE_FOLDER := include
PREREQUISITES_FOLDER := prerequisites
OBJS_FOLDER := objs
BIN_FOLDER := .

SDL_INCLUDE := -I./include

CFLAGS := -g -Wall -Wextra -flto -O1 -I$(INCLUDE_FOLDER) -I$(PREREQUISITES_FOLDER) -I$(SDL_INCLUDE) -MMD
LDFLAGS := -L./lib/

SRCS_RAW := main.cpp \
game.cpp \
graphics.cpp \
button.cpp 	\
character.cpp 	\
enemy.cpp 	\
entity.cpp 	\
inGameItem.cpp 	\
player.cpp 	\
level.cpp 	\
projectile.cpp 	\
text.cpp 	\
skillNode.cpp \
skillTree.cpp \
rect.cpp 	\
attack.cpp 	\
skills.cpp 	\
circle.cpp 	\


SRCS := $(addprefix $(SRCS_FOLDER)/, $(SRCS_RAW))
OBJS := $(SRCS:$(SRCS_FOLDER)/%.cpp=$(OBJS_FOLDER)/%.o)
DEPS := $(OBJS:.o=.d)
PREREQUISITES := $(wildcard $(PREREQUISITES_FOLDER)/*.cpp)

.PHONY: all clean re fclean test

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(BIN_FOLDER)/$@ $^ -lSDL2 -lSDL2_ttf -lSDL2_image

$(OBJS_FOLDER)/%.o: $(SRCS_FOLDER)/%.cpp | $(OBJS_FOLDER)
	$(CC) $(CFLAGS) -c $< -o $@ -MMD -MF $(@:.o=.d)

-include $(DEPS)

$(OBJS_FOLDER):
	mkdir -p $(OBJS_FOLDER)

clean:
	$(RM) $(OBJS) $(DEPS)

fclean: clean
	$(RM) $(BIN_FOLDER)/$(TARGET)

re: fclean all

test: all
	$(BIN_FOLDER)/$(TARGET).exe