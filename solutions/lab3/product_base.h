#pragma once
#include <fstream>
#include <memory>

namespace sict
{
    class iProduct
    {
    public:
        [[nodiscard]]
        virtual double price() const = 0;
        virtual void display(std::ostream&) const = 0;
        virtual ~iProduct() = default;
    };

    using record_type = std::shared_ptr<iProduct>;
}

sict::record_type readRecord(std::ifstream&);
std::ostream &operator<<(std::ostream&, const sict::iProduct&);
