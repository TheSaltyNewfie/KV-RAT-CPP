CC = x86_64-w64-mingw32-g++
CFLAGS = -Wall -I/usr/x86_64-w64-mingw32/include/ -I./external/SDL2 -O0
LFLAGS = -lws2_32 -lole32 -lgdi32 -luuid -static-libgcc -static-libstdc++ -lshlwapi -L./Libs/ -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -lwindowscodecs -llua54 -fpthread -lz

# Directories
SRC_DIR = src
BUILD_DIR = build
UTIL_DIR = $(SRC_DIR)/Utils
CMD_DIR = $(SRC_DIR)/Commands
NET_DIR = $(SRC_DIR)/Networking

# Source files
SRCS = $(SRC_DIR)/main.cpp $(UTIL_DIR)/Utils.cpp $(CMD_DIR)/Commands.cpp $(CMD_DIR)/CommandHandler.cpp $(CMD_DIR)/LuaBackend.cpp $(NET_DIR)/Networking.cpp
OBJS = $(addprefix $(BUILD_DIR)/, $(notdir $(SRCS:.cpp=.o)))

.PHONY: directories clean all post-build

all: directories KV-RAT post-build
	@echo "Debug: CFLAGS= $(CFLAGS)"

directories:
	mkdir -p $(BUILD_DIR)

KV-RAT: $(OBJS)
	$(CC) $(CFLAGS) -o $(BUILD_DIR)/KV-RAT.exe $^ $(LFLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(UTIL_DIR)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(CMD_DIR)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(NET_DIR)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

post-build: 
	cp /usr/x86_64-w64-mingw32/bin/libgcc_s_seh-1.dll $(BUILD_DIR)
	cp /usr/x86_64-w64-mingw32/bin/libstdc++-6.dll $(BUILD_DIR)
	cp /usr/x86_64-w64-mingw32/bin/libwinpthread-1.dll $(BUILD_DIR)
	rm -f $(BUILD_DIR)/*.o

clean:  
	rm -rf $(BUILD_DIR)/*.o $(BUILD_DIR)/KV-RAT.exe
