#ifndef JACY_H
#define JACY_H

#include <fstream>
#include <sstream>
#include <iostream>
#include <chrono>
#include <unordered_map>

#include "Exception.h"
#include "parser/Lexer.h"
#include "parser/Parser.h"
#include "tree/Printer.h"
#include "translator/Translator.h"

/**
 * Jacy
 * @brief The main class that controls all interpreter parts (lexer, parser, evaluator)
 * 
 * @details Singleton
 */
class Jacy {
public:
    Jacy();
    ~Jacy() = default;

    /**
     * @brief Launch Jacy
     * 
     * @param argc Count of command line arguments
     * @param argv List of command line arguments
     */
    void launch(int argc, const char * argv[]);

private:
    // Initial file that interpreter starts from (received as command line argument)
    std::string main_file;

    // Debug mode state
    bool debug;

    Lexer lexer;
    Parser parser;
    Translator translator;

    /**
     * @brief Run REPL
     */
    void run_repl();

    /**
     * @brief Run script file
     * 
     * @param path String path to file to run
     */
    void run_script(const std::string & path);

    /**
     * @brief Run source code
     * 
     * @param script Source code as string
     */
    void run(const std::string & script);

    /**
     * @brief Run source code in debug mode
     * 
     * @param script Source code as string
     */
    void run_debug(const std::string & script);
};

#endif
