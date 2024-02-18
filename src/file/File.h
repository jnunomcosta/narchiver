#pragma once

#include <string>

/**
 * @brief TODO-NC
 */
class File
{
public:
    /**
     * @brief Construct a new File object
     *
     * @param name
     * @param size
     */
    File(const std::string& name, const uint64_t size);

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
    uint64_t getSize();

private:
    /// @brief
    const std::string mName;
    /// @brief
    const uint64_t mSize;
};
