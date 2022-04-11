//#ifndef LOGGING_H
//#define LOGGING_H
#pragma once

#define LOG(level) get_logger(level)

class NullStream : public std::ostream {
private:
    class NullBuffer : public std::streambuf {
    public:
        int overflow(int c) override { return c; }
    } buffer_;
public:
    NullStream() : std::ostream(&buffer_) {}
} nullStream;

enum {
    ERROR = 0,
    INFO,
    DEBUG
};

constexpr int logLevel = ERROR;

std::ostream& get_logger(int level) {
    return logLevel >= level ? std::cout : nullStream;
}

//#endif //LOGGING_H
