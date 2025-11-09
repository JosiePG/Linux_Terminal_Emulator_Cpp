# Linux Terminal — C++ Implementation

🚀 **A lightweight, efficient, and extensible file system simulation built from scratch in C++**

---

## About This Project

Have you ever wondered how file systems work behind the scenes? This project is my deep dive into the core concepts of file system architecture creating a fully functional, in-memory file system **from the ground up**.

Using C++, I designed and implemented a hierarchical directory structure with support for essential file system operations such as navigating directories, managing files/folders, and maintaining an organized file tree all without relying on external libraries or OS-level calls.

---

## Features

- **Robust Directory Tree**: Utilizes a custom tree structure with parent, child, and sibling pointers to efficiently model directories and files.
- **Dynamic Navigation**: Supports commands like `cd`, `pwd`, `ls`, and recursive directory visualization via `tree`.
- **File & Directory Management**:
  - Create new files with `touch`
  - Make directories using `mkdir`
  - Remove files/directories safely (`rm`, `rmdir`)
  - Move and rename files or directories with `mv`
- **Error Handling**: Prevents invalid operations such as deleting non-empty directories or moving files to conflicting destinations.
- **Pre-built Test Structures**: Quickly initialize the file system with sample directory trees for testing and demonstration purposes.

