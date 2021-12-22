#include "keyboard_listener.hpp"

namespace mitp::event_listener {

KeyboardListener::KeyboardListener(const sf::Event& event) : event_(event) {
}

std::optional<char> KeyboardListener::GetSymbol() const noexcept {
  if (event_.type != sf::Event::KeyPressed) {
    return std::nullopt;
  }

  if (event_.key.code < 0 || event_.key.code > 26) {
    return std::nullopt;
  }

  constexpr std::size_t kToAsciiShift = 65;
  auto key_code = static_cast<std::size_t>(event_.key.code);

  return static_cast<char>(key_code + kToAsciiShift);
}

}  // namespace mitp::event_listener