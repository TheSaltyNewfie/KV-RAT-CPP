CC = x86_64-w64-mingw32-g++
CFLAGS = -Wall

# Source Files and Object Files
# External files are like this
#	external/imgui/imgui.cpp \
    external/imgui/imgui_demo.cpp \
    external/imgui/imgui_draw.cpp \
    external/imgui/imgui_impl_dx9.cpp \
    external/imgui/imgui_impl_win32.cpp \
    external/imgui/imgui_tables.cpp \
    external/imgui/imgui_widgets.cpp \

SRC = src/Commands/CommandHandler.cpp \
      src/Commands/commands.cpp \
      src/KV-RAT.cpp \
      src/networking.cpp \
      src/onload.cpp \
      src/Utils/utils.cpp

OBJ = $(SRC:.cpp=.o)

# Executable Name
EXEC = KV-RAT.exe

# Targets
all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)