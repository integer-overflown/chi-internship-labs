#include "Txt.h"
#include <fstream>
#include <iostream>
#include <cstring>
#include <stdexcept>

using namespace l1;

Txt::Txt() : _size(0)
{
    content = new char[0];
}

Txt::Txt(const char *filename)
{
    std::ifstream in(filename);
    if (!in.is_open())
        throw std::invalid_argument("File does not exists");

    in.seekg(0, std::ios_base::end);
    ssize_t s_length = in.tellg();
    if (s_length < 0)
        throw std::bad_array_new_length();

    _size = s_length;

    in.seekg(0, std::ios_base::beg);
    content = new char[_size];
    in.read(content, s_length);
    if (in.fail())
        throw std::logic_error("Failed to retrieve file content");
    in.close();
}

Txt::Txt(const Txt &other) : _size(other._size)
{
    content = new char[_size];
    std::memcpy(content, other.content, _size);
}

Txt::Txt(Txt &&other) noexcept : _size(0), content(nullptr)
{
    swap(other);
}

Txt::~Txt()
{
    if (content) clear();
}

size_t Txt::size() const
{
    return _size;
}

const char *Txt::to_string()
{
    return content;
}

Txt& Txt::operator=(const Txt &other)
{
    if (&other != this)
        Txt(other).swap(*this);
    return *this;
}

Txt& Txt::operator=(Txt &&other) noexcept
{
    if (&other != this)
        swap(other);
    return *this;
}

std::ostream &l1::operator<<(std::ostream &out, const Txt &value)
{
    out.write(value.content, value._size);
    return out;
}

void Txt::clear() {
    delete[] content;
    content = nullptr;
    _size = 0;
}

void Txt::swap(Txt &other) {
    std::swap(content, other.content);
    std::swap(_size, other._size);
}




