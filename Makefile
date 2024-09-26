CXX = g++

EXECUTABLE = gas

CXXFLAGS  = -D _DEBUG -ggdb3 -std=c++17 -O3 -Wall -Wextra -Weffc++ -Waggressive-loop-optimizations \
			-Wc++14-compat -Wmissing-declarations -Wcast-align -Wcast-qual -Wchar-subscripts       \
			-Wconditionally-supported -Wconversion -Wctor-dtor-privacy -Wempty-body -Wfloat-equal  \
			-Wformat-nonliteral -Wformat-security -Wformat-signedness -Wformat=2 -Winline          \
			-Wlogical-op -Wnon-virtual-dtor -Wopenmp-simd -Woverloaded-virtual -Wpacked            \
			-Wpointer-arith -Winit-self -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo  \
			-Wstrict-null-sentinel -Wstrict-overflow=2 -Wsuggest-attribute=noreturn                \
			-Wsuggest-final-methods -Wsuggest-final-types -Wsuggest-override -Wswitch-default      \
			-Wswitch-enum -Wsync-nand -Wundef -Wunreachable-code -Wunused -Wuseless-cast           \
			-Wvariadic-macros -Wno-literal-suffix -Wno-missing-field-initializers -Wno-narrowing   \
			-Wno-old-style-cast -Wno-varargs -Wstack-protector -fcheck-new -fsized-deallocation    \
			-fstack-protector -fstrict-overflow -fno-omit-frame-pointer -Wlarger-than=8192         \
			-Wstack-usage=8192 -fPIE -Werror=vla

HOME = $(shell pwd)

SOURCE_DIR = src
INCLUDE_DIR = include

LIB_INCLUDE = -I/opt/homebrew/Cellar/sfml/2.6.1/include -L/opt/homebrew/Cellar/sfml/2.6.1/lib -lsfml-graphics -lsfml-window -lsfml-system

CXXFLAGS  += -I $(HOME)/$(INCLUDE_DIR)
CXXFLAGS  += $(LIB_INCLUDE)

BUILD_DIR   = build

DOXYFILE = Doxyfile
DOXYBUILD = doxygen $(DOXYFILE)

# ==============================================================
# 						 FILE GROUPS
# ==============================================================

SOURCES = main.cpp

GUI_SOURCES = buttons.cpp manager.cpp
GUI_DIR = $(SOURCE_DIR)/gui

SCENE_SOURCES = molecules.cpp gas.cpp
SCENE_DIR = $(SOURCE_DIR)/scene

MATHS_SOURCES = coord_system.cpp vectors.cpp
MATHS_DIR = $(SOURCE_DIR)/maths

GRAPHICS_SOURCES = visual.cpp pixels_array.cpp convertion.cpp
GRAPHICS_DIR = $(SOURCE_DIR)/graphics

OBJECTS = $(SOURCES:%.cpp=$(BUILD_DIR)/%.o)
GUI_OBJECTS = $(GUI_SOURCES:%.cpp=$(BUILD_DIR)/%.o)
SCENE_OBJECTS = $(SCENE_SOURCES:%.cpp=$(BUILD_DIR)/%.o)
MATHS_OBJECTS = $(MATHS_SOURCES:%.cpp=$(BUILD_DIR)/%.o)
GRAPHICS_OBJECTS = $(GRAPHICS_SOURCES:%.cpp=$(BUILD_DIR)/%.o)

# ==============================================================

.PHONY: all
all: $(EXECUTABLE)

# -------------------------------------------------------------------------------

$(EXECUTABLE): $(OBJECTS) $(GUI_OBJECTS) $(SCENE_OBJECTS) $(MATHS_OBJECTS) $(GRAPHICS_OBJECTS)
	$(CXX) $^ -o $@ $(CXXFLAGS)

$(BUILD_DIR)/%.o : $(SOURCE_DIR)/%.cpp
	$(CXX) -c $^ -o $@ $(CXXFLAGS)

$(BUILD_DIR)/%.o : $(GUI_DIR)/%.cpp
	$(CXX) -c $^ -o $@ $(CXXFLAGS)

$(BUILD_DIR)/%.o : $(SCENE_DIR)/%.cpp
	$(CXX) -c $^ -o $@ $(CXXFLAGS)

$(BUILD_DIR)/%.o : $(MATHS_DIR)/%.cpp
	$(CXX) -c $^ -o $@ $(CXXFLAGS)

$(BUILD_DIR)/%.o : $(GRAPHICS_DIR)/%.cpp
	$(CXX) -c $^ -o $@ $(CXXFLAGS)

# -------------------------------------------------------------------------------

.PHONY: clean makedirs

clean:
	rm -rf  $(EXECUTABLE) $(BUILD_DIR)/*.o

makedirs:
	mkdir -p $(BUILD_DIR)




