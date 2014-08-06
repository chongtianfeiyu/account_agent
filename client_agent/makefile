BASE_DIR= ${HOME}/develop/server

COMMON_INCLUDE_DIR = $(BASE_DIR)/common
NETEVENT_INCLUDE_DIR = $(BASE_DIR)/netevent
LOGGER_INCLUDE_DIR = $(BASE_DIR)/logger
FRAME_INCLUDE_DIR = $(BASE_DIR)/frame
TINYXML_INCLUDE_DIR = $(BASE_DIR)/tinyxml
JSONCPP_INCLUDE_DIR = $(BASE_DIR)/jsoncpp
INC = -I$(COMMON_INCLUDE_DIR) -I$(NETEVENT_INCLUDE_DIR) -I$(LOGGER_INCLUDE_DIR)
ifeq ($(mode),d)
	CPPFLAGS= -g -fPIC -Wall -DDEBUG $(INC) -Wno-invalid-offsetof
else
	CPPFLAGS= -g -fPIC -Wall $(INC) -Wno-invalid-offsetof
endif

CLIENT_AGENT_DIR = $(BASE_DIR)/account_agent

CLIENT_AGENT_OBJ_DIR = $(CLIENT_AGENT_DIR)/.objs

SRC = $(wildcard *.cpp)
OBJS = $(addprefix $(CLIENT_AGENT_OBJ_DIR)/, $(subst .cpp,.o,$(SRC)))

all : $(OBJS)

$(CLIENT_AGENT_OBJ_DIR)/%.o : %.cpp
	$(CXX) $(CPPFLAGS) -c $< -o $@

clean: 
	rm -f $(OBJS)