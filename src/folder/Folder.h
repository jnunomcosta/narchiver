#pragma once

#include <File.h>

#include <string>
#include <vector>

/**
 * @brief
 *
 */
class Folder
{
public:
    /**
     * @brief Construct a new Folder object
     *
     * @param name
     * @param files
     * @param folders
     */
    Folder(const std::string& name,
           const std::vector<File>& files,
           const std::vector<Folder>& folders);

    /**
     * @brief Get the Name object
     *
     * @return std::string
     */
    std::string getName();

    /**
     * @brief Get the Size object
     *
     * @return uint64_t
     */
    std::vector<File> getFiles();

    /**
     * @brief Get the Folders object
     *
     * @return std::vector<Folder>
     */
    std::vector<Folder> getFolders();

private:
    /// @brief
    const std::string mName;
    /// @brief
    const std::vector<File> mFiles;
    /// @brief
    const std::vector<Folder> mFolders;
};
