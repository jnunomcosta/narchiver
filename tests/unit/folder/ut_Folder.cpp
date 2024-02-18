#include <Folder.h>

#include <gtest/gtest.h>

using namespace ::testing;

/**
 * @brief TODO-NC
 */
class FolderTest : public Test
{
protected:
    /**
     * @brief Class constructor.
     */
    FolderTest()
        : cFileName1{"DummyName1"}
        , cFileName2{"DummyName2"}
        , cFileSize1{111111}
        , cFileSize2{222222}
        , cFile1{cFileName1, cFileSize1}
        , cFile2{cFileName2, cFileSize2}
        , cFolderName{"DummyFolderName1"}
    {
    }

protected:
    /// Dummy file name.
    const std::string cFileName1;
    /// Dummy file name.
    const std::string cFileName2;
    /// Dummy file size.
    const uint64_t cFileSize1;
    /// Dummy file size.
    const uint64_t cFileSize2;
    /// Dummy file 1.
    File cFile1;
    /// Dummy file 2.
    File cFile2;
    /// Dummy folder name.
    const std::string cFolderName;
};

/**
 * @brief Tests that... TODO-NC
 */
TEST_F(FolderTest, folderConstructionDoesNotThrow)
{
    Folder folder = Folder(cFolderName, std::vector<File>{cFile1, cFile2}, std::vector<Folder>{});
}

/**
 * @brief Tests that... TODO-NC
 */
TEST_F(FolderTest, getsWork)
{
    Folder folder = Folder(cFolderName, std::vector<File>{cFile1, cFile2}, std::vector<Folder>{});

    auto files = folder.getFiles();
    EXPECT_EQ(files.size(), 2);
    EXPECT_EQ(files.at(0).getName(), cFileName1);
    EXPECT_EQ(files.at(0).getSize(), cFileSize1);
    EXPECT_EQ(files.at(1).getName(), cFileName2);
    EXPECT_EQ(files.at(1).getSize(), cFileSize2);
}
