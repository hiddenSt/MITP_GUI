#pragma once

#include <optional>

#include <SFML/Window/Event.hpp>

namespace mitp::event_listener {

enum class Key {

};

class KeyboardListener {
 public:
  explicit KeyboardListener(const sf::Event& event);

  [[nodiscard]] std::optional<char> GetSymbol() const noexcept;

 private:
  const sf::Event& event_;
};

}  // namespace mitp::event_listener
