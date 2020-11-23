#pragma once
#include "product_base.h"

namespace sict
{
    class Product : public iProduct
    {
        int _id;
        double _price;
    public:
        Product(int id, double price);

        [[nodiscard]]
        double price() const override;
        void display(std::ostream&) const override;
    };
}