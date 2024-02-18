# Narchiver - A C++ Archiving Tool

Narchiver is a command-line program written in C++ that allows you to archive (compress) and dearchive (extract) files and folders. It provides a flexible and efficient way to manage your data, similar to popular tools like `zip`.

## Table of Contents

- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Contributing](#contributing)
- [License](#license)

## Features

- Archive files and folders into a single file.
- Dearchives archives to retrieve the original files and directory structure.
- Cross-platform compatibility (Linux, macOS, Windows).

## Installation

To build and use Narchiver, follow these steps:

### Prerequisites

- C++17 compatible compiler (e.g., GCC, Clang, or Visual C++)
- CMake (3.15 or higher)

### Building Narchiver

1. Clone the repository to your local machine:

   ```bash
   git clone https://github.com/jnunomcosta/narchiver.git
   cd narchiver
   ```

2. Create a build directory and navigate to it:

   ```bash
   mkdir build
   cd build
   ```

3. Generate build files with CMake:

   ```bash
   cmake ..
   ```

4. Build the project:

   ```bash
   make        # On Unix-based systems
   or
   make -j     # Specify the number of cores for parallel build (e.g., make -j4)
   ```

5. Once the build is complete, you'll find the Narchiver executable in the build directory. You can copy it to your preferred location or use it directly from there.

## Usage

### Archiving Files and Folders

To archive files and folders, use the following command: TODO

   ```bash
   ./narchiver archive <output-archive> <input-files-and-folders...>
   ```

For example, to create an archive named `my_archive.nar` containing files and the data folder:

   ```bash
   ./narchiver archive my_archive.nar file1.txt file2.jpg data/
      ```

### Dearchiving Archives

To dearchive an existing archive, use the following command: TODO

   ```bash
   ./narchiver dearchive <input-archive> <output-directory>
   ```

For example, to extract the contents of `my_archive.nar` to a folder called `extracted_data`:

   ```bash
   ./narchiver dearchive my_archive.nar extracted_data/
   ```

## Contributing

We welcome contributions! If you'd like to improve Narchiver or report issues, please open an issue or submit a pull request. Please refer to our [contributing guidelines](docs/CONTRIBUTING.md) for more details.

## License

This project is licensed under the MIT License. See the [License](docs/LICENSE) file for details.
