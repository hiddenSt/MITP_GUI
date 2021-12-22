#include "text_area.hpp"

#include <stdexcept>

namespace mitp::widget {

TextArea::TextArea(std::size_t line_length, const sf::Font& font, std::size_t font_size)
    : font_{font},
      text_{},
      line_length_{line_length},
      font_size_{font_size},
      current_position_{0},
      current_line_{0} {
}

void TextArea::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  std::string text_str;

  static bool Need_Blink = false;

  for (std::size_t i = 0; i < text_.size(); ++i) {
    if (i == current_line_) {
      for (std::size_t j = 0; j < text_[i].size(); ++j) {
        if (j == current_position_ - 1) {
          if (Need_Blink) {
            Need_Blink = false;
            text_str.push_back('_');
          } else {
            Need_Blink = true;
            text_str.push_back(text_[i][j]);
          }
        } else {
          text_str.push_back(text_[i][j]);
        }
      }
    } else {
      text_str.append(text_[i]);
    }

    text_str.append("\n");
  }

  sf::Text text{text_str, font_, static_cast<unsigned int>(font_size_)};
  target.draw(text);
}

void TextArea::Add(char symbol) {
  if (text_.empty()) {
    current_line_ = 0;
    current_position_ = 0;
    text_.emplace_back();
  }

  if (symbol == '\n') {
    InsertEmptyLine();
    return;
  }

  if (text_[current_line_].size() > line_length_) {
    InsertEmptyLine();
  }

  text_[current_line_].insert(current_position_, 1, symbol);

  ++current_position_;
}

void TextArea::RemoveCurrentSymbol() {
  if (text_.empty()) {
    return;
  }

  if (!text_[current_line_].empty()) {
    if (current_position_ > 0) {
      --current_position_;
    }

    text_[current_line_].erase(current_position_, 1);
  }

  if (text_[current_line_].empty()) {
    std::size_t i = 0;

    for (auto iter = text_.begin(); iter != text_.end(); ++iter) {
      if (i == current_line_) {
        text_.erase(iter);
        break;
      }

      ++i;
    }

    --current_line_;
    if (!text_[current_line_].empty()) {
      current_position_ = text_[current_line_].size() - 1;
    }
  }
}

void TextArea::MoveCursorLeft() {
  if (current_position_ == 0) {
    if (current_line_ != 0) {
      --current_line_;
      current_position_ = text_[current_line_].size();
    }

    return;
  }

  --current_position_;
}

void TextArea::MoveCursorRight() {
  if (current_position_ == text_[current_line_].size()) {
    if (current_line_ < text_.size() - 1) {
      ++current_line_;
      current_position_ = 0;
    }

    return;
  }
  ++current_position_;
}

void TextArea::MoveCursorUp() {
  if (current_line_ == 0) {
    return;
  }

  --current_line_;

  if (text_[current_line_].size() - 1 < current_position_) {
    current_position_ = text_[current_line_].size() - 1;
  }
}

void TextArea::MoveCursorDown() {
  if (current_line_ == text_.size() - 1) {
    return;
  }

  ++current_line_;

  if (text_[current_line_].size() - 1 < current_position_) {
    current_position_ = text_[current_line_].size();
  }
}

void TextArea::InsertEmptyLine() {
  std::size_t i = 0;

  for (auto iter = text_.begin(); iter != text_.end(); ++iter) {
    if (i == current_line_) {
      text_.emplace(++iter);
      break;
    }

    ++i;
  }

  current_position_ = 0;
  ++current_line_;
}

TextArea::TextArea(const sf::Font& font, const std::vector<std::string>& text,
                   std::size_t line_length, std::size_t font_size)
    : font_{font},
      text_{text},
      line_length_{line_length},
      font_size_{font_size},
      current_position_{0},
      current_line_{0} {
}

std::vector<std::string> TextArea::GetText() const {
  return text_;
}

void TextArea::MoveToStartOfLine() {
  current_position_ = 1;
}

void TextArea::MoveToEndOfLine() {
  current_position_ = text_[current_line_].size();
}

}  // namespace mitp::widget