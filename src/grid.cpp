#include "grid.hpp"

// algorithms
#include <algorithm>
#include <ranges>

// aliases and namespaces
namespace ranges = std::ranges;
namespace views = std::views;

namespace marching_squares {

std::pair<point, point> bounds(pointset const & points)
{
    // compare points by their components
    auto by_x = [](point const & p, point const & q) { return p.x < q.x; };
    auto by_y = [](point const & p, point const & q) { return p.y < q.y; };

    // find the points with the least and greatest x and y coordinates
    auto const &[xmin, xmax] = ranges::minmax(points, by_x);
    auto const &[ymin, ymax] = ranges::minmax(points, by_y);

    return std::make_pair(point{xmin.x, ymin.y}, point{xmax.x, ymax.y});
}

node::mask neighbors(pointset const & points, point const & cell_ll)
{
    node::mask bits;

    point const cell_ul = point::above(cell_ll);
    if (not points.contains(cell_ll)) {
        bits |= node::upper_left;
    }
    if (not points.contains(point::right(cell_ul))) {
        bits |= node::upper_right;
    }
    if (not points.contains(point::right(cell_ll))) {
        bits |= node::lower_right;
    }
    if (not points.contains(cell_ul)) {
        bits |= node::lower_left;
    }
    return bits;
}

node_grid make_grid(pointset const & points)
{
    auto const [ll, ur] = bounds(points);
    int const width = ur.x - ll.x;
    int const height = ur.y - ll.y;

    // compute a point from an index
    auto cell_from_index = [&ll, width](int i) {
        return ll + point{ i % width, i/width };
    };

    // create a point-node pair
    auto count_neighbors = [&points](point const & cell_ll) {
        return std::make_pair(cell_ll, neighbors(points, cell_ll));
    };

    // compute the node points from the full cartesian product of indices
    auto nodes = views::iota(0, width*height)
               | views::transform(cell_from_index);

    // compute the neighbors at each point and return the respective grid
    node_grid grid;
    auto into_grid = std::inserter(grid, grid.begin());
    ranges::transform(nodes, into_grid, count_neighbors);
    return grid;
}
}
