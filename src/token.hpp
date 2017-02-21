#pragma once

class Token {
private:
    std::string data;

public:
    Token(std::string data) : data(data) {}
    size_t size() const;
    std::string operator[](size_t idx) const;
    std::string type() const;
    std::string name() const;
    std::string line() const;
    std::string toknum() const;
    int param() const;
    std::string full() const;
};
