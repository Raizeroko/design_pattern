#pragma once

#include <string>

namespace command::before {

class Editor {
public:
    void append(const std::string& text) { text_ += text; }
    void erase_last(int count) { text_.erase(text_.size() - static_cast<std::size_t>(count)); }
    const std::string& text() const { return text_; }

private:
    std::string text_;
};

} // namespace command::before
