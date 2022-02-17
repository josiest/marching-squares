#pragma once

// data structures and data types
#include <cstddef> // std::size_t
#include <unordered_set>

namespace marching_squares {

// a simple 2d point
struct point {
    int x;
    int y;

    inline point(int x, int y) : x(x), y(y) {}

    inline point & operator+=(point const & p)
    {
        x += p.x;
        y += p.y;
        return *this;
    }

    // the points above, below, left and right
    static inline point above(point const & p) { return point(p.x, p.y+1); }
    static inline point below(point const & p) { return point(p.x, p.y-1); }
    static inline point left(point const & p) { return point(p.x-1, p.y); }
    static inline point right(point const & p) { return point(p.x+1, p.y); }
};

inline bool operator==(point const & lhs, point const & rhs)
{
    return lhs.x == rhs.x and lhs.y == rhs.y;
}

inline point operator+(point const & lhs, point const & rhs)
{
    point p(lhs);
    p += rhs;
    return p;
}
}

namespace std {

template<>
struct hash<marching_squares::point> {

    size_t operator()(marching_squares::point const & p) const
    {
        hash<int> inthash;
        return inthash(p.x) ^ (inthash(p.y) << 1);
    }
};
}

namespace marching_squares {

// a set of poinst
using pointset = std::unordered_set<point>;
}
