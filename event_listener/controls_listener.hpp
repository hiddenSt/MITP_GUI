#pragma once

#include <optional>

#include <SFML/Window/Event.hpp>

namespace mitp::event_listener {

enum class Control {
  Up = 0,
  Down = 1,
  Left = 2,
  Right = 3,
  Backspace = 4,
  Space = 5,
  Enter = 6,
  Delete = 7,
  Home = 8,
  End = 9,
};

class ControlsListener {
 public:
  explicit ControlsListener(const sf::Event& event);

  [[nodiscard]] std::optional<Control> GetControl() const noexcept;

 private:
  const sf::Event& event_;
};

}  // namespace mitp::event_listener
