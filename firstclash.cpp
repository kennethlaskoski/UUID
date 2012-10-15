#include "kashmir/uuid.h"
#include "kashmir/devrandom.h"

#include <iostream>
#include <set>

int main()
{
   using kashmir::uuid_t;
   using kashmir::system::DevRandom;

    DevRandom devrandom;
    uuid_t uuid;

    std::set<uuid_t> set;

    const size_t count = -1;
    for (size_t i = 0; i < count; ++i)
    {
        if (i != set.size())
            break;

        if (!(i%1000000))
            std::cout << '.' << std::flush;

        devrandom >> uuid;
        set.insert(uuid);
    }

    std::cout << '\n' << set.size() << '\n';
}
