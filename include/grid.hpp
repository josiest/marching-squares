#pragma once

// data types
#include <cstdint>
#include "point.hpp"

// data structures
#include <utility>
#include <unordered_map>
#include <bitset>
#include <array>

namespace marching_squares {

namespace cell {
using square = std::array<point, 4>;
inline std::size_t constexpr lower_left = 0;
inline std::size_t constexpr upper_left = 1;
inline std::size_t constexpr upper_right = 2;
inline std::size_t constexpr lower_right = 3;
}

namespace node {
using mask = std::bitset<4>;
inline mask constexpr lower_left{0b1};
inline mask constexpr upper_right{0b10};
inline mask constexpr upper_left{0b100};
inline mask constexpr lower_right{0b1000};
}

using node_grid = std::unordered_map<point, node::mask>;

// get the bottom-left and upper-right bounding corners of a pointset
std::pair<point, point> bounds(pointset const & points);

// compute a node from a point's surrounding neighbors
node::mask neighbors(pointset const & points, point const & cell_ll);

// create a grid of nodes from a pointset
node_grid make_grid(pointset const & points);
}
