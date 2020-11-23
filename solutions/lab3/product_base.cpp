#include "product_base.h"
#include "product.h"
#include "taxable_product.h"

using namespace sict;

record_type readRecord(std::ifstream& in)
{
    int id;
    double price;
    in >> id;
    in >> price;

    if (in.fail())
        throw std::logic_error("Failed to read a record");

    char c;
    while ((c = in.get()) == ' '); // strip trailing spaces, if any

    if (in.eof() || std::isspace(c)) {
        // end of line or file is reached, so no tax type is provided
        return std::make_shared<Product>(id, price);
    } else {
        // interpret c as tax type
        return std::make_shared<TaxableProduct>(id, price, c);
    }
}

std::ostream &operator<<(std::ostream& out, const sict::iProduct& value)
{
    value.display(out);
    return out;
}
