#include "vcore.h"
#include <ctime>
#include <chrono>
#include <thread>
#include <random>
#include <iostream>

/**
 * VCore Native Method Implementations
 */
namespace VCoreNative {

    Value now(std::vector<Value>& args) {
        return Value(static_cast<double>(std::time(0)));
    }

    Value sleep(std::vector<Value>& args) {
        if (args.empty()) throw std::runtime_error("vcore.sleep() expects 1 argument (ms)");
        long long ms = static_cast<long long>(args[0].asNumber());
        std::this_thread::sleep_for(std::chrono::milliseconds(ms));
        return Value(true);
    }

    Value platform(std::vector<Value>& args) {
        #if defined(_WIN64) || defined(_WIN32)
            return Value("Windows");
        #elif __linux__
            return Value("Linux");
        #elif __APPLE__
            return Value("macOS");
        #else
            return Value("Unknown");
        #endif
    }

    Value random(std::vector<Value>& args) {
        if (args.size() < 2) throw std::runtime_error("vcore.random() expects 2 arguments (min, max)");
        static std::random_device rd;
        static std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dist(
            static_cast<int>(args[0].asNumber()), 
            static_cast<int>(args[1].asNumber())
        );
        return Value(static_cast<double>(dist(gen)));
    }
}


void setupBuiltins(SymbolContainer& env) {
    if (env.find("global.vcore") == env.end()) {
        env["global.vcore"] = SymbolTable();
    }

    auto& vcore = env["global.vcore"];

    vcore["sub@now"]      = Value(VCoreNative::now);
    vcore["sub@sleep"]    = Value(VCoreNative::sleep);
    vcore["sub@platform"] = Value(VCoreNative::platform);
    vcore["sub@random"]   = Value(VCoreNative::random);
}