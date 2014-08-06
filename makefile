BASE_DIR= ${HOME}/develop/server

DEBUG_LIB_DIR = $(BASE_DIR)/lib/Debug
RELEASE_LIB_DIR = $(BASE_DIR)/lib/Release

ifeq ($(mode),d)
	BIN_SUFFIX = _dbg
	LIB_DIR = $(DEBUG_LIB_DIR)
	BIN_DIR = $(BASE_DIR)/bin/Debug
	CPPFLAGS= -g -fPIC -Wall -DDEBUG $(INC) -Wno-invalid-offsetof
	LDFLAGS = -g -fPIC -L$(LIB_DIR) -lpthread -lnetevent -llogger -lbasecommon -lframe -ltinyxml
	DEBUG_TARGET = $(BIN_DIR)/accountagent$(BIN_SUFFIX)
	TARGET	= $(DEBUG_TARGET)
else
	LIB_DIR = $(RELEASE_LIB_DIR)
	BIN_DIR = $(BASE_DIR)/bin/Release
	CPPFLAGS= -g -fPIC -Wall  $(INC) -Wno-invalid-offsetof
	LDFLAGS = -g -fPIC -L$(LIB_DIR) -lpthread -lnetevent -llogger -lbasecommon -lframe -ltinyxml
	RELEASE_TARGET = $(BIN_DIR)/accountagent$(BIN_SUFFIX)
	TARGET	= $(RELEASE_TARGET)
endif

ACCOUNTAGENT_DIR = $(BASE_DIR)/account_agent

SRC = $(wildcard *.cpp)
OBJ_DIR	= $(ACCOUNTAGENT_DIR)/.objs
ACCOUNTAGENT_OBJS = $(addprefix $(OBJ_DIR)/, $(subst .cpp,.o,$(SRC)))
OBJS = $(wildcard $(OBJ_DIR)/*.o)

CLIENT_AGENT_DIR = client_agent
CLIENT_AGENT_SRC = $(wildcard $(CLIENT_AGENT_DIR)/*.cpp)
WEB_AGENT_DIR = web_agent
WEB_AGENT_SRC = $(wildcard $(WEB_AGENT_DIR)/*.cpp)
HTTP_BUSINESS_DIR = http_business
HTTP_BUSINESS_SRC = $(wildcard $(HTTP_BUSINESS_DIR)/*.cpp)
SESSION_BANK_DIR = session_bank
SESSION_BANK_SRC = $(wildcard $(SESSION_BANK_DIR)/*.cpp)

COMMON_INCLUDE_DIR = $(BASE_DIR)/common
NETEVENT_INCLUDE_DIR = $(BASE_DIR)/netevent
LOGGER_INCLUDE_DIR = $(BASE_DIR)/logger
FRAME_INCLUDE_DIR = $(BASE_DIR)/frame
JSONCPP_INCLUDE_DIR = $(BASE_DIR)/jsoncpp
INC = -I$(COMMON_INCLUDE_DIR) -I$(NETEVENT_INCLUDE_DIR) -I$(LOGGER_INCLUDE_DIR) -I$(FRAME_INCLUDE_DIR)

all : $(TARGET)

$(TARGET) : $(ACCOUNTAGENT_OBJS) CLIENT_AGENT WEB_AGENT HTTP_BUSINESS SESSION_BANK
	$(CXX)  -o $@ $(OBJS) $(LDFLAGS)

$(OBJ_DIR)/%.o : %.cpp
	$(CXX) $(CPPFLAGS) -c $< -o $@

CLIENT_AGENT:
	cd $(CLIENT_AGENT_DIR); make
WEB_AGENT:
	cd $(WEB_AGENT_DIR); make
HTTP_BUSINESS:
	cd $(HTTP_BUSINESS_DIR); make
SESSION_BANK:
	cd $(SESSION_BANK_DIR); make
	
clean:
	cd $(CLIENT_AGENT_DIR); make clean;
	cd $(WEB_AGENT_DIR); make clean;
	cd $(HTTP_BUSINESS_DIR); make clean;
	cd $(SESSION_BANK_DIR); make clean;
	rm -f $(OBJS) $(TARGET)
