#include <iostream>
#include <string>

#include "hide-secret.hpp"


int main(int argc, char** argv)
{
    if (argc < 3)
    {
        std::cerr << "Not enough arguments!" << std::endl;
        return EXIT_FAILURE;
    }

    std::string text{argv[1]};
    const std::string secret{argv[2]};

    hide_secret(text.data(), secret.data());
    std::cout << text << std::endl;
}
