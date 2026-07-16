# Compilador e Flags obrigatórias
CXX      = g++
CXXFLAGS = -std=c++17 -Wall -Wextra
TARGET   = meu_sistema

# Diretorios
SRC_DIR   = src
BUILD_DIR = build

# Fontes e Objetos
SOURCES  = $(SRC_DIR)/main.cpp $(SRC_DIR)/rpg_engine.cpp
OBJECTS  = $(BUILD_DIR)/main.o $(BUILD_DIR)/rpg_engine.o

# Regra padrao de build
all: $(BUILD_DIR) $(TARGET)

# Regra Debug com AddressSanitizer (Para checar vazamentos do Teste 6)
debug: CXXFLAGS += -g -fsanitize=address,undefined
debug: LDFLAGS  += -fsanitize=address,undefined
debug: clean $(BUILD_DIR) $(TARGET)

# Linkagem do executavel final
$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET) $(LDFLAGS)

# Compilacao dos objetos em /build
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Criacao da pasta build
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Limpeza completa
clean:
	rm -rf $(BUILD_DIR) $(TARGET)

.PHONY: all debug clean