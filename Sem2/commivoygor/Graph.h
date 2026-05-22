#pragma once
#include <vector>
#include <map>
#include <queue>
#include <stack>
#include <limits>
#include <algorithm>
#include <SFML/Graphics.hpp>

class Network {
private:
    struct Link {
        int destination;
        int weight;
    };

    std::vector<int> locations;
    std::vector<std::vector<Link>> connections;
    bool oneWay;

    int findLocation(int loc) const {
        auto pos = std::find(locations.begin(), locations.end(), loc);
        return (pos != locations.end()) ? std::distance(locations.begin(), pos) : -1;
    }

public:
    explicit Network(bool directional = false) : oneWay(directional) {}

    void addLocation(int loc) {
        if (findLocation(loc) == -1) {
            locations.push_back(loc);
            connections.resize(locations.size());
        }
    }

    void removeLocation(int loc) {
        int pos = findLocation(loc);
        if (pos != -1) {
            for (auto& links : connections) {
                links.erase(std::remove_if(links.begin(), links.end(),
                    [loc](const Link& l) { return l.destination == loc; }), links.end());
            }
            locations.erase(locations.begin() + pos);
            connections.erase(connections.begin() + pos);
        }
    }

    void createLink(int start, int end, int cost) {
        int startPos = findLocation(start);
        int endPos = findLocation(end);
        
        if (startPos != -1 && endPos != -1) {
            connections[startPos].push_back({end, cost});
            if (!oneWay) {
                connections[endPos].push_back({start, cost});
            }
        }
    }

    void deleteLink(int start, int end) {
        int startPos = findLocation(start);
        int endPos = findLocation(end);
        
        if (startPos != -1 && endPos != -1) {
            connections[startPos].erase(
                std::remove_if(connections[startPos].begin(), connections[startPos].end(),
                    [end](const Link& l) { return l.destination == end; }),
                connections[startPos].end());
            
            if (!oneWay) {
                connections[endPos].erase(
                    std::remove_if(connections[endPos].begin(), connections[endPos].end(),
                        [start](const Link& l) { return l.destination == start; }),
                    connections[endPos].end());
            }
        }
    }

    std::vector<int> exploreWide(int startLoc) {
        std::vector<int> journey;
        std::vector<bool> checked(locations.size(), false);
        std::queue<int> toExplore;

        int startPos = findLocation(startLoc);
        if (startPos == -1) return journey;

        toExplore.push(startPos);
        checked[startPos] = true;

        while (!toExplore.empty()) {
            int current = toExplore.front();
            toExplore.pop();
            journey.push_back(locations[current]);

            for (const Link& link : connections[current]) {
                int neighborPos = findLocation(link.destination);
                if (!checked[neighborPos]) {
                    checked[neighborPos] = true;
                    toExplore.push(neighborPos);
                }
            }
        }

        return journey;
    }

    std::vector<int> exploreDeep(int startLoc) {
        std::vector<int> journey;
        std::vector<bool> checked(locations.size(), false);
        std::stack<int> toExplore;

        int startPos = findLocation(startLoc);
        if (startPos == -1) return journey;

        toExplore.push(startPos);

        while (!toExplore.empty()) {
            int current = toExplore.top();
            toExplore.pop();

            if (!checked[current]) {
                checked[current] = true;
                journey.push_back(locations[current]);

                for (const Link& link : connections[current]) {
                    int neighborPos = findLocation(link.destination);
                    if (!checked[neighborPos]) {
                        toExplore.push(neighborPos);
                    }
                }
            }
        }

        return journey;
    }

    std::map<int, int> findShortest(int startLoc) {
        const int MAX = std::numeric_limits<int>::max();
        std::map<int, int> distances;
        std::priority_queue<std::pair<int, int>, 
                          std::vector<std::pair<int, int>>,
                          std::greater<std::pair<int, int>>> pq;

        for (int loc : locations) {
            distances[loc] = MAX;
        }

        int startPos = findLocation(startLoc);
        if (startPos == -1) return distances;

        distances[startLoc] = 0;
        pq.push({0, startLoc});

        while (!pq.empty()) {
            int currentDist = pq.top().first;
            int currentLoc = pq.top().second;
            pq.pop();

            if (currentDist > distances[currentLoc]) continue;

            int currentPos = findLocation(currentLoc);
            for (const Link& link : connections[currentPos]) {
                int newDist = currentDist + link.weight;
                if (newDist < distances[link.destination]) {
                    distances[link.destination] = newDist;
                    pq.push({newDist, link.destination});
                }
            }
        }

        return distances;
    }

    void draw(sf::RenderWindow& display) {
        const float size = 200.f;
        const sf::Vector2f middle(400.f, 300.f);
        std::map<int, sf::Vector2f> positions;

        float angle = 0.f;
        const float angleChange = 2 * 3.14159f / locations.size();

        for (size_t i = 0; i < locations.size(); ++i) {
            positions[locations[i]] = {
                middle.x + size * std::cos(angle),
                middle.y + size * std::sin(angle)
            };
            angle += angleChange;
        }

        sf::Font textStyle;
        if (textStyle.loadFromFile("arial.ttf")) {
            for (size_t i = 0; i < locations.size(); ++i) {
                for (const Link& link : connections[i]) {
                    sf::Vertex line[] = {
                        sf::Vertex(positions[locations[i]], sf::Color::Black),
                        sf::Vertex(positions[link.destination], sf::Color::Black)
                    };
                    display.draw(line, 2, sf::Lines);

                    sf::Text weightText;
                    weightText.setFont(textStyle);
                    weightText.setString(std::to_string(link.weight));
                    weightText.setCharacterSize(12);
                    weightText.setFillColor(sf::Color::Red);
                    weightText.setPosition(
                        (positions[locations[i]].x + positions[link.destination].x) / 2,
                        (positions[locations[i]].y + positions[link.destination].y) / 2
                    );
                    display.draw(weightText);
                }
            }

            for (const auto& pos : positions) {
                sf::CircleShape point(20.f);
                point.setPosition(pos.second.x - 20, pos.second.y - 20);
                point.setFillColor(sf::Color::Blue);
                display.draw(point);

                sf::Text label;
                label.setFont(textStyle);
                label.setString(std::to_string(pos.first));
                label.setCharacterSize(14);
                label.setFillColor(sf::Color::White);
                label.setPosition(pos.second.x - 5, pos.second.y - 8);
                display.draw(label);
            }
        }
    }
};