// data structures and data types
#include <unordered_set>
#include "point.hpp"
#include "grid.hpp"

// math and algorithms
#include "mesh.hpp"
#include <algorithm>

// i/o
#include <iostream>
#include <iomanip>

namespace ms = marching_squares;
namespace ranges = std::ranges;

void print(ms::vertex const & v)
{
    std::cout << std::setprecision(2)
              << "{" << v.x << ", " << v.y << "}" << std::endl;
}

int main()
{
    ms::pointset points{{0, 0}, {1, 0}, {0, 1}};
    auto grid = ms::make_grid(points);
    auto verts = ms::triangulate(grid);
    ranges::for_each(verts, &print);
}
