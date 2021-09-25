#pragma once
#include <ifstream>
#include <list>

struct Symbol
{
    char* m_name;
    size_t m_nameLen;
    u32 address;
};

class SymbolFile
{
private:
    int getChar() {
        if (m_pos >= m_inputSize)
            return -1; /* EOF */
        char c = m_input[m_pos];
        if (m_pos > m_latestPos) {
            m_latestPos = m_pos;
            m_lineNumber += c == '\n' ? 1 : 0;
        }
        m_pos++;
        return c;
    }

    int getChar(ssize_t pos) {
        if (m_pos >= m_inputSize)
            return -1; /* EOF */
        char c = m_input[m_pos + pos];
        if (m_pos + pos > m_latestPos) {
            m_latestPos = m_pos + pos;
            m_lineNumber += c == '\n' ? 1 : 0;
        }
        return c;
    }

    char* posToString(ssize_t pos = 0) {
        return m_input + m_pos + pos;
    }

    void updatePos(ssize_t pos) {
        m_pos += pos;
    }

    bool isWhitespace(char c) const {
        return c == ' ' || c == '\r' || c == '\n' || c == '\t';
    }

    int getNextNotWhitespace() {
        int c = getChar();
        if (c < 0 || isWhitespace(c))
            return c;
        return getNextNotWhitespace();
    }

    int findNextNotWhitespace(ssize_t pos = 0) {
        int c = getChar(pos);
        if (c < 0 || isWhitespace(c))
            return pos;
        return findNextNotWhitespace(c + 1);
    }

    int findNextWhitespace(ssize_t pos = 0) {
        int c = getChar(pos);
        if (c < 0 || !isWhitespace(c))
            return pos;
        return findNextWhitespace(c + 1);
    }

    bool isValidCLabelChar(char c) const {
        return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')
            || (c >= '0' && c <= '9') || c == '_';
    }

    bool isNumber(char c) const {
        return c >= '0' && c <= '9';
    }

    size_t getVersionString(char* str, size_t n, size_t startlen = 0) {
        int c = getChar(0);
        if (c < 0 || isWhitespace(c) || !isValidCLabelChar(c))
            return startlen;
        *str = c;
        if (startlen >= n - 1) {
            str[1] = 0;
            return startlen;
        }
        updatePos(1);
        return getVersionString(str + 1, n - 1, startlen + 1);
    }

    size_t getSymbolNameEnd(size_t startlen = 0) {
        int c = getChar(0);
        if (c < 0 || isWhitespace(c) || c == '=' || c == ';')
            return startlen;
        updatePos(1);
        return getVersionString(startlen + 1);
    }

    // [FIXME] this function is messy and bad
    void processVersions(char* version)
    {
        int c = getNextNotWhitespace();
        while (1)
        {
            if (c == ']')
                return;
            if (c == -1) {
                errorEof();
                return;
            }
        
            char str[14];
            updatePos(-1);
            size_t len = getVersionString(str, 14);
            if (len > 12) {
                std::fprintf(stderr,
                    "error: %s: version name '%s...' is too long. "
                    "must be at most 12 characters\n", m_filename, str);
                return;
            }

            c = getNextNotWhitespace();
            if (c == -1) {
                errorEof();
                return;
            }
    
            if (c != ',' && c != ']') {
                errorSyntax();
                return;
            }
            if (!std::strcmp(version, str))
                m_verIndex = m_verCount;

            m_verCount++;
        }
    }

    // [FIXME] this function looks like something Leseratte would write
    u32 processSymbolAddress(int index = 0, u32 address = 0)
    {
        if (index >= m_verCount) {
            std::fprintf(stderr, "error: %s line %d: expected %d values\n"
                m_filename, m_lineNumber, m_verCount);
            m_isErr = true;
            return 0;
        }

        int c = getNextNotWhitespace();
        if (c == '_' && index == m_verIndex) {
            return 0;
        }
        if (c != '_')
        {
            if (!isNumber(c)) {
                errorSyntax();
                return 0;
            }

            u32 addr;
            for (int i = 0; i < 8; i++)
            {
                c = getChar();
                if (!isNumber(c)) {
                    if (isWhitespace(c))
                        c = getNextNotWhitespace();
                    if (c == -1) {
                        errorEof();
                        return 0;
                    }
                    break;
                }
                addr <<= 4;
                addr |= c - '0';
            }

            if (isNumber(c)) {
                /* only other explanation */
                std::fprintf(stderr, "error: %s line %d: address is too"
                        "big. must be at most 32-bit\n",
                        m_filename, m_lineNumber);
                m_isErr = true;
                return 0;
            }

            if (index == m_verIndex)
                address = addr;
        } else
            c = getNextNotWhitespace();

        if (c == ';') {
            if (index + 1 != m_verCount) {
                std::fprintf(stderr,
                    "error: %s line %d: expected %d values\n"
                     m_filename, m_lineNumber, m_verCount);
                m_isErr = true;
                return 0;
            }
            return address;
        } else if (c != ',') {
            errorSyntax();
            return 0;
        }
    
        return processSymbolAddress(index + 1, address);
    }

    void processSymbols()
    {
        int c = getNextNotWhitespace();
        if (c == -1)
            return;
        
        updatePos(-1);
        Symbol sym;
        sym.m_name = posToString();
        sym.m_nameLen = getSymbolNameEnd();

        updatePos(-1);
        c = getNextNotWhitespace();
        if (c == -1) {
            errorEof();
            return;
        }

        if (c != '=') {
            errorSyntax();
            return;
        }

        sym.m_address = processSymbolAddress();
        if (m_isErr)
            return;

        processSymbols();
    }

    void processText(char* version)
    {
        char c = getNextNotWhitespace();
        if (c == '[') {
            processVersions(version);
            if (m_isErr)
                return;
            if (m_verIndex == -1) {
                std::fprintf(stderr, "error: no version matching '%s'\n",
                    version);
                m_isErr = true;
                return;
            }
        } else {
            m_verCount = 1;
            m_verIndex = 0;
            updatePos(-1);
        }

        processSymbols();
    }




    void errorEof() {
        std::fprintf(stderr, "error: %s: unexpected end of file\n", m_filename);
        m_isErr = true;
    }

    void errorSyntax() {
        std::fprintf(stderr, "error: %s line %d: syntax error\n",
            m_filename, m_lineNumber);
        m_isErr = true;
    }

private:
    char* m_filename = nullptr;
    char* m_input = nullptr;
    size_t m_inputSize = 0;
    size_t m_pos = 0;
    size_t m_latestPos = 0;
    size_t m_lineNumber = 0;

    std::list<Symbol> m_syms;

    int m_verCount = 0;
    int m_verIndex = -1;

    bool m_isErr = false;
};