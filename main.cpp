#include "cli/repl.h"
#include "cli/file_handler.h"

int main(int argc, char* argv[]) {
    SymbolContainer env;
    env["global"] = {};
    
    uint32_t piId = StringPool::instance().intern("pi");
    env["global"][piId] = Value(3.14159);

    if (argc > 1) {
        runFile(argv[1], env);
    } else {
        std::string input;
        init_REPL(input, env);
    }

    return 0;
}