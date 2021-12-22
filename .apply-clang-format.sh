#!/bin/bash
find event_listener widget . -type f -name "*.hpp" | xargs clang-format-12 -i --style=file
find  event_listener widget . -type f -name "*.cpp" | xargs clang-format-12 -i --style=file
#find src tests include -type f -name "*.h" | xargs clang-format-12 -i --style=file

