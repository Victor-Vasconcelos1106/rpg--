CXX      = g++
CXXFLAGS = -std=c++17 -Wall -Wextra
TARGET   = meu_exe

# Diretorios
SRC_DIR  = src
BUILD_DIR = build

# Arquivos fonte e objetos
SOURCES  = $(SRC_DIR)/main.cpp $(SRC_DIR)/rpg_engine.cpp
OBJECTS  = $(BUILD_DIR)/main.o $(BUILD_DIR)/rpg_engine.o

# Regra padrao (Compila sem flags de sanitize por padrao)
all: $(BUILD_DIR) $(TARGET)

# Regra para o modo Debug com AddressSanitizer (Solicitado no Teste 7)
debug: CXXFLAGS += -g -fsanitize=address,undefined
debug: LDFLAGS  += -fsanitize=address,undefined
debug: clean $(BUILD_DIR) $(TARGET)

# Linkagem do executavel
$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET) $(LDFLAGS)

# Compilacao dos arquivos objeto
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Criacao do diretorio de build
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Limpeza dos arquivos gerados
clean:
	rm -rf $(BUILD_DIR) $(TARGET)

.PHONY: all debug clean
