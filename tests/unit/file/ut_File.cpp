#include <File.h>

#include <gtest/gtest.h>

using namespace ::testing;

/**
 * @brief TODO-NC
 */
class FileTest : public Test
{
protected:
    /**
     * @brief Class constructor.
     */
    FileTest()
        : cFileName{"DummyName"}
        , cFileSize{111111}
        , cFile{cFileName, cFileSize}
    {
    }

protected:
    /// Dummy file name.
    const std::string cFileName;
    /// Dummy file size.
    const uint64_t cFileSize;
    /// Dummy file.
    const File cFile;
};

/**
 * @brief Tests that the gets for name and size work.
 */
TEST_F(FileTest, getNameAndSizeWork)
{
    File fil = File(cFileName, cFileSize);
    EXPECT_EQ(fil.getName(), cFileName);
    EXPECT_EQ(fil.getSize(), cFileSize);
}
