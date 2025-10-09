# Makefile for CASTLE-C250 filtered dataset
# Compiles all C files with specified security-testing flags

# Compiler settings
CC = gcc
CFLAGS = -O0 -fno-omit-frame-pointer -fno-stack-protector -no-pie

# Directories
SRC_DIR = /workspaces/CASTLE-datasets/CASTLE-C250-filtered
BIN_DIR = /workspaces/CASTLE-datasets/CASTLE-C250_binaries

# Library flags
MYSQL_LIBS = -lmysqlclient
SQLITE_LIBS = -lsqlite3
OPENSSL_LIBS = -lssl -lcrypto
CURL_LIBS = -lcurl
PTHREAD_LIBS = -lpthread

# Find all C source files
SOURCES = $(wildcard $(SRC_DIR)/*.c)
BASENAMES = $(basename $(notdir $(SOURCES)))
BINARIES = $(addprefix $(BIN_DIR)/, $(BASENAMES))

# Default target
.PHONY: all clean help setup

all: setup $(BINARIES)

# Create binary directory if it doesn't exist
setup:
	@mkdir -p $(BIN_DIR)
	@echo "Building $(words $(SOURCES)) CASTLE binaries..."

# Generic rule for most files
$(BIN_DIR)/%: $(SRC_DIR)/%.c
	@echo "Compiling $< -> $@"
	@if grep -q "#include <mysql/mysql.h>" "$<"; then \
		$(CC) $(CFLAGS) "$<" -o "$@" $(MYSQL_LIBS); \
	elif grep -q "#include <sqlite3.h>" "$<"; then \
		$(CC) $(CFLAGS) "$<" -o "$@" $(SQLITE_LIBS); \
	elif grep -q "#include <openssl/" "$<"; then \
		$(CC) $(CFLAGS) "$<" -o "$@" $(OPENSSL_LIBS); \
	elif grep -q "#include <curl/curl.h>" "$<"; then \
		$(CC) $(CFLAGS) "$<" -o "$@" $(CURL_LIBS); \
	elif grep -q "#include <pthread.h>" "$<"; then \
		$(CC) $(CFLAGS) "$<" -o "$@" $(PTHREAD_LIBS); \
	else \
		$(CC) $(CFLAGS) "$<" -o "$@"; \
	fi

# Clean target
clean:
	@echo "Cleaning binaries..."
	@rm -f $(BIN_DIR)/CASTLE-*
	@echo "Clean complete."

# Help target
help:
	@echo "CASTLE-C250 Filtered Dataset Makefile"
	@echo "======================================"
	@echo ""
	@echo "Available targets:"
	@echo "  all     - Build all binaries (default)"
	@echo "  clean   - Remove all built binaries"
	@echo "  setup   - Create binary directory"
	@echo "  help    - Show this help message"
	@echo ""
	@echo "Compiler flags: $(CFLAGS)"
	@echo "Source directory: $(SRC_DIR)"
	@echo "Binary directory: $(BIN_DIR)"
	@echo ""
	@echo "Library support:"
	@echo "  - MySQL: $(MYSQL_LIBS)"
	@echo "  - SQLite: $(SQLITE_LIBS)"
	@echo "  - OpenSSL: $(OPENSSL_LIBS)"
	@echo "  - cURL: $(CURL_LIBS)"
	@echo "  - pthreads: $(PTHREAD_LIBS)"

# Individual CWE targets for convenience
.PHONY: cwe-22 cwe-78 cwe-89 cwe-134 cwe-190

cwe-22: setup
	@echo "Building CWE-22 (Path Traversal) binaries..."
	@$(MAKE) $(filter $(BIN_DIR)/CASTLE-22-%, $(BINARIES))

cwe-78: setup
	@echo "Building CWE-78 (OS Command Injection) binaries..."
	@$(MAKE) $(filter $(BIN_DIR)/CASTLE-78-%, $(BINARIES))

cwe-89: setup
	@echo "Building CWE-89 (SQL Injection) binaries..."
	@$(MAKE) $(filter $(BIN_DIR)/CASTLE-89-%, $(BINARIES))

cwe-134: setup
	@echo "Building CWE-134 (Format String) binaries..."
	@$(MAKE) $(filter $(BIN_DIR)/CASTLE-134-%, $(BINARIES))

cwe-190: setup
	@echo "Building CWE-190 (Integer Overflow) binaries..."
	@$(MAKE) $(filter $(BIN_DIR)/CASTLE-190-%, $(BINARIES))

# Test compilation - build a few samples to verify everything works
.PHONY: test
test: setup
	@echo "Testing compilation with sample files..."
	@$(MAKE) $(BIN_DIR)/CASTLE-22-1
	@$(MAKE) $(BIN_DIR)/CASTLE-78-1
	@$(MAKE) $(BIN_DIR)/CASTLE-89-1
	@$(MAKE) $(BIN_DIR)/CASTLE-134-1
	@$(MAKE) $(BIN_DIR)/CASTLE-190-1
	@echo "Test compilation successful!"

# Show statistics
.PHONY: stats
stats:
	@echo "CASTLE-C250 Filtered Dataset Statistics"
	@echo "======================================="
	@echo "Total source files: $(words $(SOURCES))"
	@echo "CWE breakdown:"
	@echo "  CWE-22:  $(words $(filter $(SRC_DIR)/CASTLE-22-%, $(SOURCES))) files"
	@echo "  CWE-78:  $(words $(filter $(SRC_DIR)/CASTLE-78-%, $(SOURCES))) files"
	@echo "  CWE-89:  $(words $(filter $(SRC_DIR)/CASTLE-89-%, $(SOURCES))) files"
	@echo "  CWE-134: $(words $(filter $(SRC_DIR)/CASTLE-134-%, $(SOURCES))) files"
	@echo "  CWE-190: $(words $(filter $(SRC_DIR)/CASTLE-190-%, $(SOURCES))) files"
	@echo ""
	@echo "Dependencies found:"
	@echo "  MySQL:   $(shell grep -l 'mysql/mysql.h' $(SRC_DIR)/*.c 2>/dev/null | wc -l) files"
	@echo "  SQLite:  $(shell grep -l 'sqlite3.h' $(SRC_DIR)/*.c 2>/dev/null | wc -l) files"
	@echo "  OpenSSL: $(shell grep -l 'openssl/' $(SRC_DIR)/*.c 2>/dev/null | wc -l) files"
	@echo "  cURL:    $(shell grep -l 'curl/curl.h' $(SRC_DIR)/*.c 2>/dev/null | wc -l) files"
	@echo "  pthread: $(shell grep -l 'pthread.h' $(SRC_DIR)/*.c 2>/dev/null | wc -l) files"