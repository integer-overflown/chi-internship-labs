#ifndef RAII_TXT_TXT_H
#define RAII_TXT_TXT_H
#include <cstddef>
#include <ostream>

namespace l1 {
    struct Txt
    {
        Txt();
        explicit Txt(const char* filename);
        Txt(const Txt& other);
        Txt(Txt&& other) noexcept;
        ~Txt();

        Txt& operator=(const Txt& other);
        Txt& operator=(Txt&& other) noexcept;
        [[nodiscard]] size_t size() const;
        const char* to_string();

        friend std::ostream& operator<<(std::ostream& out, const Txt& value);
    private:
        char* content;
        size_t _size;

        void swap(Txt &other);
        void clear();
    };
    std::ostream& operator<<(std::ostream& out, const Txt& value);
}

#endif //RAII_TXT_TXT_H
