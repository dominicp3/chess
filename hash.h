#ifndef HASH_H
#define HASH_H

#include <utility>

struct pair_hash
{
        std::size_t operator()(const std::pair<int, int>& pair) const
        {
                return 8 * pair.first + pair.second;
        }
};

#endif // HASH_H
