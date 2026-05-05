# ============================================================
#  PkmnRPG – Makefile
# ============================================================

CXX      := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -O2

TARGET   := PkmnRPG

# ── Source & object files ───────────────────────────────────
SRC_DIR  := src
INC_DIR  := inc
SRCS     := $(wildcard $(SRC_DIR)/*.cpp)
OBJS     := $(SRCS:$(SRC_DIR)/%.cpp=$(SRC_DIR)/%.o)

# ── Local lib layout ────────────────────────────────────────
LIB_DIR      := lib/lib
LIB_INC_DIR  := lib/include

STATIC_LIBS := \
    $(LIB_DIR)/libsfml-graphics-s.a \
    $(LIB_DIR)/libsfml-window-s.a   \
    $(LIB_DIR)/libsfml-system-s.a   \
    $(LIB_DIR)/libsqlite3.a

SYS_LIBS := -lGL -lX11 -lXrandr -lXcursor -ludev -lfreetype -lpthread -ldl

# ── Flags ───────────────────────────────────────────────────
CXXFLAGS += -I$(INC_DIR) -I$(LIB_INC_DIR)
LDFLAGS  := $(STATIC_LIBS) $(SYS_LIBS)

# ── Rules ───────────────────────────────────────────────────
.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

$(SRC_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)