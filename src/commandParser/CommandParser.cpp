#include "CommandParser.h"

#include <algorithm>
#include <iostream>

std::optional<std::string> getOutputValues(int /* argc */, const char* argv[])
{
    std::string outputFlag(argv[2]);
    if (outputFlag == "-o" || outputFlag == "--output") {
        return std::string(argv[3]);
    }

    return {};
}

std::optional<std::vector<std::string>> getInputValues(int argc, const char* argv[])
{
    std::string inputFlag(argv[4]);
    if (inputFlag == "-i" || inputFlag == "--input") {
        std::vector<std::string> inputs;
        for (int i = 5; i <= argc; i++) {
            inputs.push_back(std::string(argv[i]));
        }
        return inputs;
    }

    return {};
}

std::optional<CommandParser> CommandParser::parseCommands(int argc, const char* argv[])
{
    if (argc < 2) {
        return {};
    }

    // TODO - Option validation can also be its own function that returns an optional string with
    // the option.
    std::string option(argv[1]);

    if (option == "-h" || option == "--help") {
        // TODO - Display help usage for archive and dearchive.
        printHelp();
        return {};
    }

    if (argc < 4) {
        return {};
    }

    if (option == "-a" || option == "--archive") {
        // TODO - This can be a function.
        std::cout << "Noice archive" << std::endl;
        auto parsedOutput = getOutputValues(argc, argv);
        if (!parsedOutput.has_value()) {
            return {};
        }
        std::string output = parsedOutput.value();

        auto parsedInputs = getInputValues(argc, argv);
        if (!parsedInputs.has_value()) {
            return {};
        }
        std::vector<std::string> inputs = parsedInputs.value();

        return CommandParser("archive", output, inputs);
    }

    if (option == "-d" || option == "--dearchive") {
        std::cout << "Noice dearchive" << std::endl;
        // TODO-NC Detail function to handle dearchive.
        return {};
    }

    return {};
}

void CommandParser::printHelp()
{
    // TODO - Needs more specific information regarding archive and dearchive.
    std::cout << "Usage: narchiver [options] <input-files-and-folders...>" << std::endl;
    std::cout << "Options:" << std::endl;
    std::cout << "  -h, --help       Display this help message" << std::endl;
    std::cout << "  -a, --archive    Specify the output archive file" << std::endl;
    std::cout << "  -d, --dearchive  Specify the action (archive/dearchive)" << std::endl;
}

CommandParser::CommandParser(std::string method,
                             std::string outputLocation,
                             std::vector<std::string> inputs)
    : mMethod{method}
    , mOutputLocation{outputLocation}
    , mInputs{inputs}
{
}

std::string CommandParser::getMethod()
{
    return mMethod;
}

std::string CommandParser::getOutput()
{
    return mOutputLocation;
}

std::vector<std::string> CommandParser::getInputs()
{
    return mInputs;
}
