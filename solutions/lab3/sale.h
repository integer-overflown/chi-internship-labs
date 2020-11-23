#pragma once
#include <iostream>
#include <list>
#include "product_base.h"

namespace sict
{
    class Sale
    {
    public:
        explicit Sale(const char *filename);
        void display(std::ostream&) const;

    private:
        std::list<record_type> products;
    };
}


