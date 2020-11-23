#pragma once
#include <unordered_map>
#include "product_base.h"

namespace sict
{
    class TaxableProduct : public iProduct
    {
        static std::unordered_map<char, double> tax_types;
        int _id;
        double _price;
        char _tax_type;

    public:
        TaxableProduct(int id, double price, char tax_type);

        [[nodiscard]]
        double price() const override;
        void display(std::ostream&) const override;
    };
}


