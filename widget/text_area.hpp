#pragma once

#include <iostream>
#include <string>
#include <vector>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>

namespace mitp::widget {

class TextArea : public sf::Drawable {
 public:
  TextArea() = delete;

  explicit TextArea(const sf::Font& font, const std::vector<std::string>& text,
                    std::size_t line_length, std::size_t font_size);
  explicit TextArea(std::size_t line_length, const sf::Font& font, std::size_t font_size);
  ~TextArea() override = default;

  void MoveCursorLeft();
  void MoveCursorRight();
  void MoveCursorUp();
  void MoveCursorDown();
  void Add(char symbol);
  void RemoveCurrentSymbol();
  void MoveToStartOfLine();
  void MoveToEndOfLine();
  std::vector<std::string> GetText() const;

 protected:
  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

 private:
  void InsertEmptyLine();

 private:
  sf::Font font_;
  std::vector<std::string> text_;
  std::size_t line_length_;
  std::size_t font_size_;
  std::size_t current_position_;
  std::size_t current_line_;
};

}  // namespace mitp::widget
