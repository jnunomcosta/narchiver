#include <CommandParser.h>

#include <gtest/gtest.h>

using namespace ::testing;

/**
 * @brief TODO - Documentation
 */
class CommandParserTest : public Test
{
protected:
    /**
     * @brief Class constructor.
     */
    CommandParserTest()
        : cArgc{2}
        , cArgv{"narchiver", "-h"}
    {
    }

protected:
    /// Dummy argument counter.
    int cArgc;
    /// Dummy argument values.
    const char* cArgv[2];
};

/**
 * @brief Tests if the command parser displays the help message with the --help flag.
 * TODO - The help message needs to be verified.
 */
TEST_F(CommandParserTest, commandParserHelpsUserWithHelpFlag)
{
    const char* archiveArgs[2] = {"narchiver", "--help"};
    std::optional<CommandParser> parsedCommand = CommandParser::parseCommands(2, archiveArgs);

    ASSERT_FALSE(parsedCommand.has_value());
}

/**
 * @brief Tests if the command parser displays the help message with the -h flag.
 * TODO - The help message needs to be verified.
 */
TEST_F(CommandParserTest, commandParserHelpsUserWithHFlag)
{
    const char* archiveArgs[2] = {"narchiver", "-h"};
    std::optional<CommandParser> parsedCommand = CommandParser::parseCommands(2, archiveArgs);

    ASSERT_FALSE(parsedCommand.has_value());
}

/**
 * @brief Tests if the command parser doesn't do anything when the argument counter is smaller
 * than 4.
 */
TEST_F(CommandParserTest, commandParserRejectsIncompleteArguments)
{
    const char* archiveArgs[1] = {"narchiver"};
    std::optional<CommandParser> parsedCommand = CommandParser::parseCommands(1, archiveArgs);
    ASSERT_FALSE(parsedCommand.has_value());

    const char* archiveArgs2[2] = {"narchiver", "-dummy"};
    std::optional<CommandParser> parsedCommand2 = CommandParser::parseCommands(3, archiveArgs2);
    ASSERT_FALSE(parsedCommand2.has_value());

    const char* archiveArgs3[3] = {"narchiver", "--dummy", "--dummy2"};
    std::optional<CommandParser> parsedCommand3 = CommandParser::parseCommands(3, archiveArgs3);
    ASSERT_FALSE(parsedCommand3.has_value());
}

/**
 * @brief Tests if the command parser successfully parses an archive command with the --archive
 * flag.
 */
TEST_F(CommandParserTest, commandParserSuccessfullyParsesArchiveFlag)
{
    const char* archiveArgs[7]
          = {"narchiver", "--archive", "-o", "dummyFileOut", "-i", "File1", "File2"};
    std::optional<CommandParser> parsedCommand = CommandParser::parseCommands(7, archiveArgs);

    ASSERT_TRUE(parsedCommand.has_value());
    CommandParser commandParser = parsedCommand.value();

    ASSERT_EQ(commandParser.getMethod(), "archive");
    ASSERT_EQ(commandParser.getOutput(), "dummyFileOut");
    ASSERT_EQ(commandParser.getInputs()[0], "File1");
    ASSERT_EQ(commandParser.getInputs()[1], "File2");
}

/**
 * @brief Tests if the command parser successfully parses an archive command with the -a flag.
 */
TEST_F(CommandParserTest, commandParserSuccessfullyParsesAFlag)
{
    const char* archiveArgs[7] = {"narchiver", "-a", "-o", "dummyFileOut", "-i", "File1", "File2"};
    std::optional<CommandParser> parsedCommand = CommandParser::parseCommands(7, archiveArgs);

    ASSERT_TRUE(parsedCommand.has_value());
    CommandParser commandParser = parsedCommand.value();

    ASSERT_EQ(commandParser.getMethod(), "archive");
    ASSERT_EQ(commandParser.getOutput(), "dummyFileOut");
    ASSERT_EQ(commandParser.getInputs()[0], "File1");
    ASSERT_EQ(commandParser.getInputs()[1], "File2");
}
