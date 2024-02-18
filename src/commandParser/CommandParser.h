#pragma once

#include <optional>
#include <string>
#include <vector>

/**
 * @brief TODO-NC
 */
class CommandParser
{
public:
    /**
     * @brief Parses the commands provided by the user.
     *
     * @return std::optional<CommandParser> TODO-NC
     */
    static std::optional<CommandParser> parseCommands(int argc, const char* argv[]);

    /**
     * @brief Prints the available commands to help the user.
     */
    static void printHelp();

    /**
     * @brief Construct a new Parsed Command object TODO-NC
     *
     * @param method
     * @param outputLocation
     * @param inputs
     */
    CommandParser(std::string method, std::string outputLocation, std::vector<std::string> inputs);

    /**
     * @brief Get the Method object TODO-NC
     *
     * @return std::string TODO-NC
     */
    std::string getMethod();

    /**
     * @brief Get the Output object TODO-NC
     *
     * @return std::string TODO-NC
     */
    std::string getOutput();

    /**
     * @brief Get the Inputs object TODO-NC
     *
     * @return std::vector<std::string> TODO-NC
     */
    std::vector<std::string> getInputs();

private:
    /// @brief Describes if the operation will be archive or dearchive.
    std::string mMethod;
    /// @brief Output location of the resulting operation.
    std::string mOutputLocation;
    /// @brief Input content to provide the operation.
    std::vector<std::string> mInputs;
};
