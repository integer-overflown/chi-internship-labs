#include "taxable_product.h"
#include <iomanip>

extern int FW;

sict::TaxableProduct::TaxableProduct(int id, double price, char tax_type) : _id{id}
{
    auto tax = tax_types.find(tax_type);
    if (tax != tax_types.end())
    {
        _tax_type = tax_type;
        _price = price * (1 + tax->second);
    }
}

double sict::TaxableProduct::price() const
{
    return _price;
}

void sict::TaxableProduct::display(std::ostream &ostream) const
{
    ostream << std::setw(FW) << _id << std::setw(FW) << _price << ' ' << _tax_type << "ST";
}

std::unordered_map<char, double> sict::TaxableProduct::tax_types{{'H', .13},
                                                                 {'P', .08}};