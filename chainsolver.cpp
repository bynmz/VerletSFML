#include <vector>
#include <cmath>
#include <SFML/Graphics.hpp>
#include "solver.hpp"

class ChainSolver
{
private:
    Solver m_solver;
public:
    ChainSolver() = default;

    // Add a new object to the chain
    VerletObject& addObject(sf::Vector2f position, float radius) {
        return m_solver.addObject(position, radius);
    }

    // Create constraints between adjacent objects in the chain
    void createConstraints() {
        auto objects = m_solver.getObjects();
        for (size_t i = 0; i < objects.size() - 1; ++i) {
            // Create a constraint between each pair of adjacent objects
            //if (i < objects.size() - 2) // Connect all except the last two objects
            m_solver.setObjectVelocity(objects[i + 1], {0.0f, 0.0f}); // Pinning objects in place
        }
    }

    // Update the chain state
    void update() {
        m_solver.update();
    }

    // Set the simulation update rate
    void setSimulationUpdateRate(uint32_t rate) {
        m_solver.setSimulationUpdateRate(rate);
    }

    // Set the sub-steps count
    void setSubStepsCount(uint32_t sub_steps) {
        m_solver.setSubStepsCount(sub_steps);
    }

    // Get the list of objects in the chain
    [[nodiscard]] 
    const std::vector<VerletObject>& getObjects() const {
        return m_solver.getObjects();
    }

    // Get the number of objects in the chain
    [[nodiscard]]
    uint64_t getObjectsCount() const {
        return m_solver.getObjectsCount();
    }

    // Get the current simulation time
    [[nodiscard]]
    float getTime() const {
        return m_solver.getTime();
    }

};

int32_t main(int32_t, char*[])
{
    // Create chain solver
    ChainSolver chainSolver;

    // Set screen dimensions
    const float screenWidth = 1000.0f;
    const float screenHeight = 1000.0f;

    // Add objects to the chain
    const int numObjects = 10;
    const float radius = 20.0f;
    const float spacing = 2.0f * radius;
    const float startX = screenWidth / 2.0f;
    const float startY = screenHeight / 2.0f;
    for (int i = 0; i < numObjects; ++i) {
        chainSolver.addObject({startX, startY + i * spacing}, radius);
    }

    // Create constraints between objects
    chainSolver.createConstraints();

    // Set simulation parameters
    chainSolver.setSimulationUpdateRate(60);
    chainSolver.setSubStepsCount(8);

    // Main loop
    sf::RenderWindow window(sf::VideoMode(static_cast<int>(screenWidth), static_cast<int>(screenHeight)), "Chain Simulation");
    sf::Clock clock;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // Update chain solver
        float dt = clock.restart().asSeconds();
        // chainSolver.update();

        // Clear the window
        window.clear(sf::Color::White);

        // Render chain objects
        const auto& objects = chainSolver.getObjects();
        for (const auto& object : objects) {
            sf::CircleShape shape(object.radius);
            shape.setOrigin(object.radius, object.radius);
            shape.setPosition(object.position);
            shape.setFillColor(sf::Color::Blue);
            window.draw(shape);
        }

        // Display the window
        window.display();
    }

    return 0;
}
