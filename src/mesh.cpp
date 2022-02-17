#include "mesh.hpp"

// data structures and abstract data types
#include "grid.hpp"
#include <vector>

// algorithms
#include <ranges>
#include <algorithm>

// aliases and namespaces
namespace ranges = std::ranges;
namespace views = std::views;

namespace marching_squares {

// return a function that offsets a vertex by a constant offset
auto offset_by(vertex const & lower_left)
{
    return [&lower_left](vertex const & cell_vertex) {
        return lower_left + cell_vertex;
    };
}

// return a function that inserts cell vertices into a mesh
auto triangulate_cell_into_mesh(mesh & verts)
{
    auto into_verts = std::back_inserter(verts);
    return [into_verts](auto const & pair) {
        auto const &[lower_left, mask] = pair;

        // insert each vertex in the cell offset by the current lower-left
        ranges::transform(contours.at(mask), into_verts, offset_by(lower_left));
    };
}

mesh triangulate(node_grid const & grid)
{
    mesh verts;
    // reserve the maximum possible number of vertices (6 per cell)
    verts.reserve(grid.size() * 6); 

    ranges::for_each(grid, triangulate_cell_into_mesh(verts));
    return verts;
}

}
