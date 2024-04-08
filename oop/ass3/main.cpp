#include <iostream>
#include <vector>
#include <fstream>
#include <random>
#include <bitset>

#define MAP_DIR "./data/map.txt"

enum Direction
{
    NORTH,
    EAST,
    SOUTH,
    WEST
};

class Room
{
public:
    virtual void enter() const = 0;
    virtual bool isAccessible() { return true; }
    void setExit(Direction dir, bool isExit)
    {
        allow_exit[dir] = isExit;
    }
    std::vector<Direction> getExits()
    {
        std::vector<Direction> exits;
        for (int dir = 0; dir < 4; ++dir)
        {
            if (allow_exit[dir])
            {
                exits.push_back(static_cast<Direction>(dir));
            }
        }
        return exits;
    }
    bool is_exit(Direction dir)
    {
        return allow_exit[static_cast<int>(dir)];
    }
    friend int main();

    void print_exits()
    {
        auto cnt = allow_exit.count();
        std::cout << "There are " << cnt << ((cnt == 1) ? " exit: " : " exits: ");
        for (int i = 0, n = 0; n != cnt; ++n)
        {
            while (!allow_exit[i])
                ++i;
            switch (i)
            {
            case 0:
                std::cout << "north";
                break;
            case 1:
                std::cout << "east";
                break;
            case 2:
                std::cout << "south";
                break;
            case 3:
                std::cout << "west";
                break;
            }
            if (n != cnt - 1)
                std::cout << ", ";
            ++i;
        }
        std::cout << '\n';
    }

private:
    std::bitset<4> allow_exit; // 0: north, 1: east, 2: south, 3: west
};
class NotARoom : public Room
{
public:
    void enter() const override
    {
        std::cout << "This is not a room. You can't enter.\n";
    }
    bool isAccessible() override { return false; }
};

class NormalRoom : public Room
{
public:
    void enter() const override
    {
        std::cout << "You are in a normal room.\n";
    }
};

class LobbyRoom : public Room
{
public:
    void enter() const override
    {
        std::cout << "Welcome to the lobby.\n";
    }
};

class MonsterRoom : public Room
{
public:
    void enter() const override
    {
        std::cout << "You've entered a room with a monster! Game over.\n";
        // exit(0);
    }
};

class PrincessRoom : public Room
{
public:
    void enter() const override
    {
        std::cout << "You've found the princess! Now find your way out.\n";
    }
};

class Map
{
public:
    Map(int n, int m) : n(n), m(m)
    {
        rooms = std::vector<std::vector<Room *>>(n, std::vector<Room *>(m, nullptr));
    }
    Map(int n, int m, std::string filename) : n(n), m(m)
    {
        rooms = std::vector<std::vector<Room *>>(n, std::vector<Room *>(m, nullptr));
        loadFromFile(filename);
    }
    void loadFromFile(std::string filename);
    Room *getRoom(int i, int j);
    friend int main();

private:
    int n, m;
    std::vector<std::vector<Room *>> rooms;
};

class Game
{
public:
    Game(Map *map) : map(map), player_i(0), player_j(0), found_princess(false) {}
    void start();

private:
    Map *map;
    int player_i, player_j;
    bool found_princess;
};

void Map::loadFromFile(std::string filename)
{
    std::ifstream typeStream(filename);
    for (int i = n - 1; i >= 0; --i)
    {
        for (int j = 0; j < m; ++j)
        {
            int type;
            typeStream >> type;
            switch (type)
            {
            case 0:
                rooms[i][j] = new NotARoom();
                break;
            case 1:
                rooms[i][j] = new NormalRoom();
                break;
            case 2:
                rooms[i][j] = new LobbyRoom();
                break;
            case 3:
                rooms[i][j] = new MonsterRoom();
                break;
            case 4:
                rooms[i][j] = new PrincessRoom();
                break;
            default:
                std::cerr << "Invalid room type: " << type << "\n";
                exit(1);
            }
        }
    }
    for (int i = n - 1; i >= 0; --i)
    {
        for (int j = 0; j < m; ++j)
        {
            int exits;
            typeStream >> exits;
            std::bitset<4> exitBits(exits);
            for (int dir = 0; dir < 4; ++dir)
            {
                if (exitBits[dir])
                {
                    int ni = i, nj = j;
                    switch (dir)
                    {
                    case NORTH:
                        ++ni;
                        break;
                    case EAST:
                        ++nj;
                        break;
                    case SOUTH:
                        --ni;
                        break;
                    case WEST:
                        --nj;
                        break;
                    }
                    if (ni >= 0 && ni < n && nj >= 0 && nj < m && rooms[ni][nj]->isAccessible())
                    {
                        rooms[i][j]->setExit(static_cast<Direction>(dir), true);
                    }
                }
            }
        }
    }
}

Room *Map::getRoom(int i, int j)
{
    return rooms[i][j];
}

void Game::start()
{
    while (true)
    {
        Room *current_room = map->getRoom(player_i, player_j);
        current_room->enter();
        if (dynamic_cast<MonsterRoom *>(current_room))
        {
            std::cout << "Game over.\n";
            break;
        }
        if (dynamic_cast<PrincessRoom *>(current_room))
        {
            if (!found_princess)
            {
                std::cout << "Congratulations, you've found the princess!\n";
                found_princess = true;
            }
        }
        if (dynamic_cast<LobbyRoom *>(current_room) && found_princess)
        {
            std::cout << "Congratulations, you've found the way out! Game end.\n";
            break;
        }
        std::vector<Direction> exits = current_room->getExits();
        std::string command[2];
        bool bad_flag = false;
        do
        {
            current_room->print_exits();
            if (bad_flag)
                std::cerr << "Error: command invalid or exit non-exist\n";
            std::cout << "Enter your command: ";
            std::cin >> command[0] >> command[1];
            bad_flag = true;
            if (command[0] == "go")
            {
                if (command[1] == "north" && current_room->is_exit(Direction::NORTH))
                {
                    bad_flag = false;
                    player_i += 1;
                }
                else if (command[1] == "east" && current_room->is_exit(Direction::EAST))
                {
                    bad_flag = false;
                    player_j += 1;
                }
                else if (command[1] == "south" && current_room->is_exit(Direction::SOUTH))
                {
                    bad_flag = false;
                    player_i -= 1;
                }
                else if (command[1] == "west" && current_room->is_exit(Direction::WEST))
                {
                    bad_flag = false;
                    player_j -= 1;
                }
            }
        } while (bad_flag);
    }
}

int main()
{
    Map map(3, 3, MAP_DIR);

    Game game(&map);
    // for (int i = 0; i != 3; ++i)
    //     for (int j = 0; j != 3; ++j)
    //     {
    //         std::cout << "(i, j) = (" << i << "," << j << ")\n";
    //         map.getRoom(i, j)->enter();
    //     }

    // for (int i = 2; i >= 0; --i)
    // {
    //     for (int j = 0; j != 3; ++j)
    //     {
    //         std::cout << map.getRoom(i, j)->allow_exit << ' ';
    //     }
    //     std::cout << '\n';
    // }
    game.start();

    return 0;
}