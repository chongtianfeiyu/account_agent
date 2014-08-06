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

HTTP_BUSINESS_DIR = $(BASE_DIR)/account_agent

HTTP_BUSINESS_OBJ_DIR = $(HTTP_BUSINESS_DIR)/.objs

SRC = $(wildcard *.cpp)
OBJS = $(addprefix $(HTTP_BUSINESS_OBJ_DIR)/, $(subst .cpp,.o,$(SRC)))

all : $(OBJS)

$(HTTP_BUSINESS_OBJ_DIR)/%.o : %.cpp
	$(CXX) $(CPPFLAGS) -c $< -o $@

clean: 
	rm -f $(OBJS)