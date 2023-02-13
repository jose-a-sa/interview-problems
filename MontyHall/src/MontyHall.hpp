#pragma once
#include <numeric>
#include <random>

class MontyHall
{
private:
    std::mt19937 generator_;
    std::uniform_int_distribution<> randint2_;
    std::uniform_int_distribution<> randint3_;
    const std::size_t otherDoor_(std::size_t door1, std::size_t door2);

public:
    enum Strategies
    {
        KEEP = 0,
        CHANGE = 1
    };
    MontyHall();
    ~MontyHall() = default;
    const bool game(MontyHall::Strategies st);
    const std::size_t gameSample(std::size_t n, MontyHall::Strategies st);
};

inline const std::size_t MontyHall::otherDoor_(std::size_t door1, std::size_t door2)
{
    std::size_t other = 0;
    if (door1 != door2)
    {
        while (other == door1 || other == door2)
            other++;
    }
    else
    {
        other = randint2_(generator_);
        if (other >= door1)
            ++other;
    }
    return other;
}

inline MontyHall::MontyHall()
{
    std::random_device rd;
    generator_ = std::mt19937(rd());
    randint2_ = std::uniform_int_distribution<>(0, 1);
    randint3_ = std::uniform_int_distribution<>(0, 2);
}

inline const bool MontyHall::game(MontyHall::Strategies st)
{
    const std::size_t prizeDoor = randint3_(generator_);
    const std::size_t firstChoice = randint3_(generator_);
    const std::size_t openDoor = otherDoor_(prizeDoor, firstChoice);
    int const secondChoice =
        (st == MontyHall::Strategies::KEEP) ? firstChoice : otherDoor_(openDoor, firstChoice);

    return secondChoice == prizeDoor;
}

inline const std::size_t MontyHall::gameSample(std::size_t n, MontyHall::Strategies st)
{
    std::size_t winCount = 0;

    for (std::size_t i = 0; i < n; i++)
        winCount += this->game(st);

    return winCount;
}
