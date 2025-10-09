# CASTLE Dataset Taint Analysis Configuration

This directory contains taint analysis configuration files for the CASTLE-C250 filtered dataset.

## Files

### `castle_taint_config.yaml`
Complete taint analysis configuration for CASTLE dataset containing:

**Sources (25+ functions across 7 categories):**
- Environment Accesses: `getenv`, `secure_getenv`
- Character Inputs: `fgetc`, `getc`, `getchar` 
- Line Inputs: `fgets`, `gets`, `getline`
- Formatted Inputs: `scanf`, `fscanf`, `sscanf`
- Files and Directories: `fopen`, `fread`
- Database Inputs: `mysql_fetch_row`, `sqlite3_column_*`
- User Input: `getpass`, `getpass_r`
- String Processing: `strtok`, `strdup`

**Sinks (50+ functions across 9 categories):**
- Memory Copy: `memcpy`, `memmove`, `memset`
- String Copy: `strcpy`, `strncpy`
- String Concatenation: `strcat`, `strncat`
- **Formatted Output**: `printf`, `fprintf`, `sprintf`, `snprintf` + variants (CWE-134)
- **Command Execution**: `system`, `popen`, `exec*` variants (CWE-78)
- **Database Queries**: `mysql_query`, `sqlite3_exec`, `sqlite3_prepare*` (CWE-89)
- **File Operations**: `fopen`, `open`, `opendir`, `remove`, `unlink` (CWE-22)
- Output: `puts`, `fputs`, `fwrite`, `putchar`
- Legacy Dangerous: `gets`

## CWE Coverage

This configuration provides comprehensive coverage for:

- **CWE-22** (Path Traversal): File operation sinks, input sources
- **CWE-78** (OS Command Injection): Command execution sinks, input sources
- **CWE-89** (SQL Injection): Database query sinks, database result sources
- **CWE-134** (Format String): Format function sinks, string input sources
- **CWE-190** (Integer Overflow): Input sources that can provide oversized values

## Usage

Use this configuration file with your taint analyzer (mole) by specifying it as the source/sink configuration:

```bash
mole --config /workspaces/CASTLE-datasets/config/castle_taint_config.yaml [other options]
```

## Analysis Basis

This configuration was generated based on comprehensive analysis of:
- 50 filtered CASTLE C files (10 files each for CWEs 22, 78, 89, 134, 190)
- 172 unique functions identified
- Security-relevant function categorization
- Cross-reference with existing taint analysis best practices

## Function Selection Criteria

Functions were included based on:
1. **Security Relevance**: Potential for vulnerability introduction
2. **Frequency**: Usage across multiple CASTLE files  
3. **CWE Coverage**: Relevance to target vulnerability classes
4. **Completeness**: Ensuring comprehensive taint flow coverage

## Validation

The configuration has been validated against the filtered CASTLE dataset to ensure:
- All critical input sources are covered
- All dangerous sinks are identified
- Proper parameter slicing for taint propagation
- Correct function signatures and symbol variants