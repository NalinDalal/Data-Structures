#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>

const float PI = 3.14159265359f;

class KochSnowflake {
public:
  KochSnowflake(int level, float sideLength, sf::Vector2f start)
      : recursionLevel(level), side(sideLength), startPoint(start) {
    angle = 0;
  }

  void draw(sf::RenderWindow &window) {
    points.clear();
    curr = startPoint;
    angle = 0;
    drawEdge(side, recursionLevel);
    rotate(120);
    drawEdge(side, recursionLevel);
    rotate(120);
    drawEdge(side, recursionLevel);

    // Draw the lines
    sf::VertexArray lines(sf::LineStrip, points.size());
    for (size_t i = 0; i < points.size(); i++) {
      lines[i].position = points[i];
      lines[i].color = sf::Color::Cyan;
    }
    window.draw(lines);
  }

private:
  int recursionLevel;
  float side, angle;
  sf::Vector2f curr;
  sf::Vector2f startPoint;
  std::vector<sf::Vector2f> points;

  void rotate(float deg) { angle += deg; }

  void drawEdge(float length, int level) {
    if (level == 0) {
      float rad = angle * PI / 180.0f;
      sf::Vector2f next =
          curr + sf::Vector2f(std::cos(rad) * length, std::sin(rad) * length);
      points.push_back(curr);
      points.push_back(next);
      curr = next;
    } else {
      drawEdge(length / 3, level - 1);
      rotate(-60);
      drawEdge(length / 3, level - 1);
      rotate(120);
            [48;52;178;1768;2848tdrawEdge(length / 3, level - 1);
            rotate(-60);
            drawEdge(length / 3, level - 1);
    }
  }
};

int main() {
  int level = 4; // Try levels 0 to 5

  sf::RenderWindow window(sf::VideoMode(800, 600), "Koch Snowflake - SFML");
  window.setFramerateLimit(60);

  KochSnowflake snowflake(level, 400.0f, sf::Vector2f(200, 300));

  while (window.isOpen()) {
    sf::Event e;
    while (window.pollEvent(e)) {
      if (e.type == sf::Event::Closed)
        window.close();
    }

    window.clear(sf::Color::Black);
    snowflake.draw(window);
    window.display();
  }

  return 0;
}
