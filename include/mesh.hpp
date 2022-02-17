#pragma once

// data structures and abstract data types
#include "point.hpp"
#include "grid.hpp"
#include <vector>
#include <array>

namespace marching_squares {

struct vertex {
    float x;
    float y;

    inline vertex(point const & p) : x(p.x), y(p.y) {}
    inline vertex(float x, float y) : x(x), y(y) {}

    inline vertex & operator+=(vertex const & p)
    {
        x += p.x;
        y += p.y;
        return *this;
    }

    static vertex const lower_left() { return vertex(0.f, 0.f); }
    static vertex const center_left() { return vertex(0.f, .5f); }
    static vertex const upper_left() { return vertex(0.f, 1.f); }
    static vertex const upper_center() { return vertex(.5f, 1.f); }
    static vertex const upper_right() { return vertex(1.f, 1.f); }
    static vertex const center_right() { return vertex(1.f, .5f); }
    static vertex const lower_right() { return vertex(1.f, 0.f); }
    static vertex const lower_center() { return vertex(.5f, 0.f); }
};

inline vertex operator+(vertex const & lhs, vertex const & rhs)
{
    vertex p(lhs);
    p += rhs;
    return p;
}

using triangle = std::array<vertex, 3>;
using mesh = std::vector<vertex>;

// map cells to their respective contours - always moving clockwise
inline std::unordered_map<node::mask, mesh> const contours{
    {node::mask(0b0), mesh{}},

    // 1-point cses
    {node::mask(0b1),
     mesh{vertex::lower_left(), vertex::center_left(),
          vertex::lower_center()}},

    {node::mask(0b10),
     mesh{vertex::lower_center(), vertex::center_right(),
          vertex::lower_right()}},

    {node::mask(0b100),
     mesh{vertex::upper_center(), vertex::upper_right(),
          vertex::center_right()}},

    {node::mask(0b1000),
     mesh{vertex::center_left(), vertex::upper_left(),
          vertex::upper_center()}},

    // 2-point cases
    {node::mask(0b11),
     mesh{vertex::lower_left(), vertex::center_left(),
          vertex::center_right(), vertex::lower_right()}},

    {node::mask(0b101),
     mesh{vertex::lower_left(), vertex::center_left(),
          vertex::upper_center(), vertex::upper_right(),
          vertex::center_right(), vertex::lower_center()}},

    {node::mask(0b110),
     mesh{vertex::lower_center(), vertex::upper_center(),
          vertex::upper_right(), vertex::lower_right()}},

    {node::mask(0b1001),
     mesh{vertex::lower_left(), vertex::upper_left(),
          vertex::upper_center(), vertex::lower_center()}},

    {node::mask(0b1100),
     mesh{vertex::center_left(), vertex::upper_left(),
          vertex::upper_right(), vertex::center_right()}},

    {node::mask(0b1010),
     mesh{vertex::lower_center(), vertex::center_left(),
          vertex::upper_left(), vertex::upper_center(),
          vertex::center_right(), vertex::lower_right()}},

    // 3-point cases
    {node::mask(0b111),
     mesh{vertex::lower_left(), vertex::center_left(),
          vertex::upper_center(), vertex::upper_right(),
          vertex::lower_right()}},

    {node::mask(0b1011),
     mesh{vertex::lower_left(), vertex::upper_left(),
          vertex::upper_center(), vertex::center_right(),
          vertex::lower_left()}},

    {node::mask(0b1101),
     mesh{vertex::lower_left(), vertex::upper_left(),
          vertex::upper_right(), vertex::center_right(),
          vertex::lower_center()}},

    {node::mask(0b1110),
     mesh{vertex::center_left(), vertex::upper_left(),
          vertex::upper_right(), vertex::lower_right(),
          vertex::lower_center()}},

    // 4-point cases
    {node::mask(0b1111),
     mesh{vertex::lower_left(), vertex::upper_left(),
          vertex::upper_right(), vertex::lower_right()}}
};

mesh triangulate(node_grid const & grid);
}
