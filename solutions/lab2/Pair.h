#pragma once

template<typename A, typename B>
class Pair
{
    A key;
    B value;
public:
    typedef const A& key_t;
    typedef const B& value_t;

    Pair() : key(), value() {}
    Pair(key_t a, value_t b);
    key_t getKey() const;
    value_t getValue() const;
};

template<typename A, typename B>
Pair<A, B>::Pair(key_t a, value_t b) : key(a), value(b) {}

template<typename A, typename B>
typename Pair<A, B>::key_t Pair<A, B>::getKey() const { return key; }

template<typename A, typename B>
typename Pair<A, B>::value_t Pair<A, B>::getValue() const { return value; }
