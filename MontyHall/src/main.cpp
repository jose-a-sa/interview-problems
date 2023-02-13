#include <iostream>

#include "MontyHall.hpp"

int main()
{
    MontyHall mt;
    std::size_t n = 10000;
    std::size_t wins_keep = mt.gameSample(n, MontyHall::Strategies::KEEP);
    std::size_t wins_change = mt.gameSample(n, MontyHall::Strategies::CHANGE);
    std::cout << "Running " << n << " games: " << '\n';
    std::cout << "KEEP strategy: \t\t" << wins_keep << " wins" << '\t' << 100.0L*wins_keep/n << "%" << '\n';
    std::cout << "CHANGE strategy: \t" << wins_change << " wins" << '\t' << 100.0L*wins_change/n << "%" << std::endl;
}