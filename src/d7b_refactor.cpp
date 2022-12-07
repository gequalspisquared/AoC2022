#include <iostream>
#include <fstream>
#include <memory>
#include <vector>
#include <string>

class Directory
{
public:
    Directory *parent;
    std::vector<std::unique_ptr<Directory>> subdirs;
    std::string name;
    size_t size;

    Directory()
    {
        size = 0;
        parent = nullptr;
        name = "";
    }

    void addSubDirectory(const std::string &name)
    {
        std::unique_ptr<Directory> newSubDirectory = std::make_unique<Directory>();
        newSubDirectory->name = name;
        newSubDirectory->parent = this;
        subdirs.push_back(std::move(newSubDirectory));
    }

    size_t computeTotalSize() const
    {
        size_t totalSize = size;
        for (const auto& dir : subdirs)
            totalSize += dir->computeTotalSize();
        return totalSize;
    }

    size_t findDirectory(const std::string &name) const
    {
        for (size_t i = 0; i < subdirs.size(); i++)
            if (subdirs[i]->name == name) return i;
        std::cout << "Could not find directory\n";
        return 0;
    }
};

size_t sizeofSmallestDirectoryToDelete(const Directory *head, 
                                       size_t sizeNeeded, 
                                       size_t currentSmallest = SIZE_MAX)
{
    size_t smallest = currentSmallest;
    for (const auto& dir : head->subdirs) {
        size_t otherSmallest = sizeofSmallestDirectoryToDelete(dir.get(), sizeNeeded, smallest);
        if (otherSmallest < smallest) smallest = otherSmallest;
    }

    size_t size = head->computeTotalSize();
    if (size >= sizeNeeded && size < smallest) smallest = size;
    return smallest;
}

int main()
{
    std::ifstream commandsFile("inputs/d7.txt");
    std::string command, skip, nextDirectory;
    Directory home;
    home.name = "/";
    Directory *currentDir = &home;
    bool cd = false;

    getline(commandsFile, command); // ignore first line
    while (getline(commandsFile, command)) {
        if (command.substr(0, 4) == "$ cd") {
            cd = true;
            nextDirectory = command.substr(5);
        }

        if (cd && nextDirectory == "..") {
            currentDir = currentDir->parent;
            cd = false;
            continue;
        } else if (cd) {
            currentDir = currentDir->subdirs[currentDir->findDirectory(nextDirectory)].get();
            cd = false;
            continue;
        }

        if (command.substr(0, 4) == "$ ls") continue;

        if (command.substr(0, 3) == "dir") {
            currentDir->addSubDirectory(command.substr(4));
            continue;
        }

        currentDir->size += stoi(command.substr(0, command.find(" ")));
    }

    size_t numNeeded = 30'000'000 - (70'000'000 - home.computeTotalSize());
    std::cout << "Space needed: " << numNeeded << "\n";
    std::cout << "Size of smallest directory to delete: " 
              << sizeofSmallestDirectoryToDelete(&home, numNeeded) << "\n";
}