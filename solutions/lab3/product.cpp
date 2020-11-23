#include "product.h"
#include <iomanip>

extern int FW;

sict::Product::Product(int id, double price) : _id{id}, _price{price} {}

double sict::Product::price() const
{
    return _price;
}

void sict::Product::display(std::ostream &out) const
{
    out << std::setw(FW) << _id << std::setw(FW) << _price;
}
