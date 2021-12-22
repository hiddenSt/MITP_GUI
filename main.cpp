#include <iostream>
#include <fstream>
#include <filesystem>

#include <SFML/Graphics.hpp>

#include <widget/text_area.hpp>
#include <event_listener/controls_listener.hpp>
#include <event_listener/keyboard_listener.hpp>

void ProcessControlKey(mitp::widget::TextArea& text_area, mitp::event_listener::Control control) {
  switch (control) {
    case mitp::event_listener::Control::Space:
      text_area.Add(' ');
      break;
    case mitp::event_listener::Control::Enter:
      text_area.Add('\n');
      break;
    case mitp::event_listener::Control::Up:
      text_area.MoveCursorUp();
      break;
    case mitp::event_listener::Control::Down:
      text_area.MoveCursorDown();
      break;
    case mitp::event_listener::Control::Left:
      text_area.MoveCursorLeft();
      break;
    case mitp::event_listener::Control::Right:
      text_area.MoveCursorRight();
      break;
    case mitp::event_listener::Control::Backspace:
      text_area.RemoveCurrentSymbol();
      break;
    case mitp::event_listener::Control::Delete:
      break;
    case mitp::event_listener::Control::Home:
      text_area.MoveToStartOfLine();
      break;
    case mitp::event_listener::Control::End:
      text_area.MoveToEndOfLine();
      break;
  }
}

int main(int argc, char* argv[]) {
  std::string filename{"./default"};

  if (argc == 2) {
    filename = argv[1];
  }

  std::vector<std::string> text;

  if (std::filesystem::exists(filename)) {
    std::ifstream fin{filename};
    std::string line;

    while (std::getline(fin, line)) {
      text.emplace_back(std::move(line));
    }
    fin.close();
  }

  sf::VideoMode video_mode{500, 500};
  sf::RenderWindow window(video_mode, "Test");
  window.setFramerateLimit(60);

  sf::Font font;

  if (!font.loadFromFile("/usr/local/share/fonts/TerminusTTF-Bold-4.49.1.ttf")) {
    std::cerr << "Failed to load font.\n";
    return EXIT_FAILURE;
  }

  mitp::widget::TextArea text_area{font, text, 20, 50};
  sf::Event event{};
  mitp::event_listener::ControlsListener controls_listener{event};
  mitp::event_listener::KeyboardListener keyboard_listener{event};

  while (true) {
    window.pollEvent(event);

    if (event.type == sf::Event::Closed) {
      window.close();
      std::cout << "Window is closed\n";
      break;
    }

    auto key_event = keyboard_listener.GetSymbol();
    auto control_event = controls_listener.GetControl();

    if (control_event.has_value()) {
      ProcessControlKey(text_area, control_event.value());
    }

    if (event.type == sf::Event::KeyPressed) {
      if (event.key.code == sf::Keyboard::Key::LControl) {
        auto lines = text_area.GetText();
        std::ofstream fout;
        fout.open(filename);

        if (!fout.is_open()) {
          std::cerr << "Can not open the file.\n";
        }

        for (const auto& line : lines) {
          fout << line << std::endl;
        }

        fout.close();
      }
    }

    if (key_event.has_value()) {
      text_area.Add(key_event.value());
    }

    window.clear();
    window.draw(text_area);
    window.display();
  }

  return EXIT_SUCCESS;
}
