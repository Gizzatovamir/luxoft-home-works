
#include <iostream>
#include <chrono>
#include <fstream>
#include <thread>
#include <vector>

using namespace std::chrono_literals;

class file_reader_t {
public:
    file_reader_t(const std::string& filename, std::size_t length, std::size_t retries = default_retries, const std::chrono::seconds& delay = default_delay) 
    : m_filename(filename)
    , m_length(length)
    , m_retries(retries)
    , m_delay(delay)
    {
    }

    std::vector<uint8_t> read() {
        std::size_t remaining_retries = m_retries;
        std::vector<uint8_t> result;
        char buffer[m_length + 1];
        while (remaining_retries > 0) {
            std::cout << "remain retries: " << remaining_retries << std::endl;
            std::ifstream is;
            is.exceptions(std::ifstream::badbit | std::ifstream::failbit );
            try {
                is.open(m_filename, std::ifstream::binary);
                std::cout << "file opened successful" << std::endl;
                is.read(buffer, m_length);
                uint8_t to_push = (uint8_t)atoi(buffer);
                result.push_back(to_push);
                std::cout << "file with sufficient length is read successful" << std::endl;
                break;
            } catch (const std::ifstream::failure& ex) {
                std::cout << ex.what() << std::endl;
                --remaining_retries;
                std::this_thread::sleep_for(m_delay);
            }
        }
        
        return result;
    }
private:
    const std::string m_filename;
    const std::size_t m_length;
    const std::size_t m_retries;
    const std::chrono::seconds m_delay;
    
    static inline std::size_t default_retries = 3;
    static inline std::chrono::seconds default_delay = 5s;
};

// https://stackoverflow.com/questions/440133/how-do-i-create-a-random-alpha-numeric-string-in-c
std::string gen_random(const int len) {
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
    std::string tmp_s;
    tmp_s.reserve(len);

    for (int i = 0; i < len; ++i) {
        tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];
    }
    
    return tmp_s;
}

int main() {
    std::string filename = "binary_file";
    std::size_t length = 256;
    std::size_t wrong_length = 128;

    file_reader_t reader(filename, length);
    auto writer = std::thread([&filename, &length, &wrong_length]() {
        std::this_thread::sleep_for(2s);
        {
            std::ofstream os(filename, std::ofstream::binary);
            std::string data = gen_random(wrong_length);
            os.write(&data[0], wrong_length);
            os.close();
        }
        std::this_thread::sleep_for(5s);
        {
            std::ofstream os(filename, std::ofstream::binary);
            std::string data = gen_random(length);
            os.write(&data[0], length);
            os.close();
        }
    });
    std::vector<uint8_t> result = reader.read();
    for(const auto &item: result){
        std::cout << item << std::endl;
    }

    writer.join();
    
    return EXIT_SUCCESS;
}