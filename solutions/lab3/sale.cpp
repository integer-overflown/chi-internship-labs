#include "sale.h"
#include "product_base.h"
#include <fstream>
#include <stdexcept>
#include <iomanip>

using namespace sict;

extern int FW;

Sale::Sale(const char *filename)
{
    std::ifstream in(filename);
    if (!in.is_open())
        throw std::invalid_argument("File not found");
    while (!in.eof()) products.push_back(readRecord(in));
}

void Sale::display(std::ostream &out) const
{
    out << "Product No" << std::setw(FW) << "Cost" << ' ' << "Taxable" << std::endl;
    for (auto &e : products) {
        e->display(out);
        out << std::endl;
    }
}
