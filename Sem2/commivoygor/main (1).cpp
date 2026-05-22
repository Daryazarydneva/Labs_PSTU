#include "Graph.h"
#include <iostream>
#include <SFML/Graphics.hpp>

void loadFont(sf::Font& f) {
    const std::string paths[] = {
        "arial.ttf",
        "fonts/arial.ttf",
        "C:/Windows/Fonts/arial.ttf"
    };

    for (const auto& p : paths) {
        if (f.loadFromFile(p)) {
            return;
        }
    }
    std::cerr << "Failed to load font\n";
}

void showPathResults(const std::vector<int>& wide, 
                   const std::vector<int>& deep,
                   const std::map<int, int>& paths) {
    std::cout << "Wide exploration: ";
    for (int loc : wide) std::cout << loc << " ";
    std::cout << "\nDeep exploration: ";
    for (int loc : deep) std::cout << loc << " ";
    
    std::cout << "\nPath lengths:\n";
    for (const auto& p : paths) {
        std::cout << "To " << p.first << ": " << p.second << "\n";
    }
}

int main() {
    sf::Font mainFont;
    loadFont(mainFont);

    sf::RenderWindow mainWindow(sf::VideoMode(800, 600), "Network Viewer");
    mainWindow.setFramerateLimit(60);

    Network system(false);
    
    for (int i = 1; i <= 6; ++i) {
        system.addLocation(i);
    }

    system.createLink(1, 2, 8);
    system.createLink(2, 3, 12);
    system.createLink(3, 4, 16);
    system.createLink(4, 5, 5);
    system.createLink(5, 6, 6);
    system.createLink(6, 1, 11);
    system.createLink(4, 6, 9);
    system.createLink(3, 1, 7);
    system.createLink(5, 2, 4);
    system.createLink(3, 5, 6);
    system.createLink(1, 5, 11);
    system.createLink(3, 6, 8);
    system.createLink(2, 6, 14);
    system.createLink(1, 4, 11);
    system.createLink(2, 4, 7);

    auto widePath = system.exploreWide(6);
    auto deepPath = system.exploreDeep(6);
    auto shortPaths = system.findShortest(6);

    showPathResults(widePath, deepPath, shortPaths);

    while (mainWindow.isOpen()) {
        sf::Event interaction;
        while (mainWindow.pollEvent(interaction)) {
            if (interaction.type == sf::Event::Closed) {
                mainWindow.close();
            }
        }

        mainWindow.clear(sf::Color::White);
        system.draw(mainWindow);

        if (mainFont.loadFromFile("arial.ttf")) {
            sf::Text title;
            title.setFont(mainFont);
            title.setString("Network Path Visualization");
            title.setCharacterSize(24);
            title.setFillColor(sf::Color::Black);
            title.setPosition(20, 20);
            mainWindow.draw(title);
        }

        mainWindow.display();
    }

    return 0;
}