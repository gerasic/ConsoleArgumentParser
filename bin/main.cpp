#include <functional>
#include <lib/ArgParser.h>

#include <iostream>
#include <numeric>

using namespace ArgumentParser;

struct Options {
    bool sum = false;
    bool mult = false;
};

int main(int argc, char** argv) {
    Options opt;
    std::vector<int> values;

    ArgumentParser::ArgParser parser("MyParser");
    parser.AddIntArgument("N").MultiValue(1).Positional().StoreValues(values);
    parser.AddFlag("sum", "Add args").StoreValue(opt.sum).Default(false);
    parser.AddFlag("mult", "Multiply args").StoreValue(opt.mult).Default(false);
    parser.AddHelp('h', "help", "Program accumulate arguments");

    // ./ConsoleArgumentParser --sum 1 2 3 4 5
    // ./ConsoleArgumentParser --mult 1 2 3 4 5
    // ./ConsoleArgumentParser --help
    if (!parser.Parse(argc, argv)) {
        std::cout << "Wrong argument, try --help." << std::endl;
        return 1;
    }

    if (opt.sum) {
        std::cout << "Result: " << std::accumulate(values.begin(), values.end(), 0) << std::endl;
    } else if (opt.mult) {
        std::cout << "Result: " << std::accumulate(values.begin(), values.end(), 1, std::multiplies<>()) << std::endl;
    } else {
        std::cout << "No one options had chosen, try --help." << std::endl;
        return 1;
    }

    return 0;

}
