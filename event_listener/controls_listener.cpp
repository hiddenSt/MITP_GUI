#include "controls_listener.hpp"

namespace mitp::event_listener {

ControlsListener::ControlsListener(const sf::Event& event) : event_(event) {
}

std::optional<Control> ControlsListener::GetControl() const noexcept {
  if (event_.type != sf::Event::KeyPressed) {
    return std::nullopt;
  }

  switch (event_.key.code) {
    case sf::Keyboard::Key::Backspace:
      return Control::Backspace;
    case sf::Keyboard::Key::Delete:
      return Control::Delete;
    case sf::Keyboard::Key::Up:
      return Control::Up;
    case sf::Keyboard::Key::Down:
      return Control::Down;
    case sf::Keyboard::Key::Left:
      return Control::Left;
    case sf::Keyboard::Key::Right:
      return Control::Right;
    case sf::Keyboard::Key::Space:
      return Control::Space;
    case sf::Keyboard::Key::Enter:
      return Control::Enter;
    case sf::Keyboard::Key::Home:
      return Control::Home;
    case sf::Keyboard::Key::Numpad1:
      return Control::End;
    default:
      return std::nullopt;
  }
}

}  // namespace mitp::event_listener