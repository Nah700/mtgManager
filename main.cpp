/*
** EPITECH PROJECT, 2024
** mtgManager
** File description:
** main
*/

#include "mtgManager.hpp"
#include "Core.hpp"

std::string openFileExplorer()
{
    char filename[1024];
    std::string command = "zenity --file-selection > /tmp/selected_file.txt";

    system(command.c_str());
    FILE *file = fopen("/tmp/selected_file.txt", "r");
    if (file) {
        fgets(filename, sizeof(filename), file);
        fclose(file);
        filename[strcspn(filename, "\n")] = 0;
        return std::string(filename);
    }
    return "";
}

int main()
{
    std::unique_ptr<Core> core = std::make_unique<Core>();
    core->run();
}