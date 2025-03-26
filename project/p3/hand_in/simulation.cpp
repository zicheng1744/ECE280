#include "simulation.h"

using namespace std;

// initialize the world
bool initWorld(world_t &world, const string &speciesFileDirectory, const string speciesName[], const string &worldFileDirectory)
{
    setSpecies(world, speciesFileDirectory, speciesName);
    setGrid(world, worldFileDirectory);
    return true;
}

// set the species
void setSpecies(world_t &world, const string &speciesFileDirectory, const string speciesName[])
{
    ifstream speciesFile;
    string fileName;
    for (unsigned int i = 0; i < world.numSpecies; i++)
    {
        fileName = speciesFileDirectory + "/" + speciesName[i];
        world.species[i].name = speciesName[i];
        // cout << "Species: " << world.species[i].name << endl;
        // cout << "Opening file " << fileName << endl;
        speciesFile.open(fileName.c_str());
        if (!speciesFile.is_open())
        {
            cout << "Error: Cannot open file " << fileName << "!" << endl;
            exit(0);
        }
        unsigned int programSize = 0;
        while (!speciesFile.eof())
        {
            string line;
            getline(speciesFile, line);
            if (line == "")
            {
                break;
            }
            else
            {
                readCommand(line, world.species[i].program[programSize]);
                world.species[i].programSize = ++programSize;
            }
            if (programSize > MAXPROGRAM)
            {
                cout << "Error: Too many instructions for species " << world.species[i].name << "!" << endl;
                cout << "Maximal number of instructions is " << MAXPROGRAM << "." << endl;
                speciesFile.close();
                exit(0);
            }
            // cout << line << endl;
        }
        speciesFile.close();
    }
}

// set the grid
void setGrid(world_t &world, const string &worldFileDirectory)
{
    ifstream worldFile;
    worldFile.open(worldFileDirectory.c_str());
    // test if the file is open
    if (!worldFile.is_open())
    {
        cout << "Error: Cannot open file " << worldFileDirectory << "!" << endl;
        exit(0);
    }
    string height, width;
    getline(worldFile, height);
    getline(worldFile, width);
    world.grid.height = atoi(height.c_str());
    // test if the height is legal
    if (world.grid.height > MAXHEIGHT || world.grid.height < 1)
    {
        cout << "Error: The grid height is illegal!" << endl;
        worldFile.close();
        exit(0);
    }
    world.grid.width = atoi(width.c_str());
    // test if the width is legal
    if (world.grid.width > MAXWIDTH || world.grid.width < 1)
    {
        cout << "Error: The grid width is illegal!" << endl;
        worldFile.close();
        exit(0);
    }
    // build an empty grid
    buildEmptyGrid(world);
    unsigned int creatureCount = 0;
    while (!worldFile.eof())
    {
        string line;
        getline(worldFile, line);
        if (line == "")
        {
            break;
        }
        else
        {
            // cout << line << endl;
            setCreature(world.creatures[creatureCount], line, world, creatureCount);
            creatureCount++;
        }
        // test if the number of creatures is legal
        if (creatureCount > MAXCREATURES)
        {
            cout << "Error: Too many creatures!" << endl;
            cout << "Maximal number of creatures is " << MAXCREATURES << "." << endl;
            worldFile.close();
            exit(0);
        }
    }
    worldFile.close();
}

// build an empty grid
void buildEmptyGrid(world_t &world)
{
    for (unsigned int i = 0; i < world.grid.height; i++)
    {
        for (unsigned int j = 0; j < world.grid.width; j++)
        {
            world.grid.squares[i][j] = NULL;
        }
    }
}

// set the creature
void setCreature(creature_t &creature, const string line, world_t &world, unsigned int creatureCount)
{
    istringstream iss(line);
    string species;
    string direction;
    unsigned int r, c;
    iss >> species >> direction >> r >> c;
    // test if the creature is out of bound
    if (r < 0 || r >= world.grid.height || c < 0 || c >= world.grid.width)
    {
        cout << "Error: Creature (" << species << " " << direction << " " << r << " " << c << ") is out of bound!" << endl;
        cout << "The grid size is " << world.grid.height << "-by-" << world.grid.width << "." << endl;
        exit(0);
    }
    // test if the creature overlaps with another creature
    if (world.grid.squares[r][c] != NULL)
    {
        cout << "Error: Creature (" << species << " " << direction << " " << r << " " << c << ") overlaps with creature (" << world.grid.squares[r][c]->species->name << " " << directionFind_L(world.grid.squares[r][c]->direction) << " " << r << " " << c << ")!" << endl;
        exit(0);
    }
    // cout << species << " " << direction << " " << r << " " << c << endl;
    world.creatures[creatureCount].location.r = r;
    world.creatures[creatureCount].location.c = c;
    world.creatures[creatureCount].direction = findDirection(direction);
    getSpecies(world, species, creatureCount);
    world.creatures[creatureCount].programID = 0;
    world.grid.squares[world.creatures[creatureCount].location.r][world.creatures[creatureCount].location.c] = &world.creatures[creatureCount];
    world.numCreatures = creatureCount + 1;
}

// find the direction from string to direction_t
direction_t findDirection(const string &direction)
{
    if (direction == "east")
    {
        return EAST;
    }
    else if (direction == "west")
    {
        return WEST;
    }
    else if (direction == "north")
    {
        return NORTH;
    }
    else if (direction == "south")
    {
        return SOUTH;
    }
    else
    {
        cout << "Error: Direction " << direction << " is not recognized!" << endl;
        exit(0);
    }
}

// find the direction from direction_t to string in short form
string directionFind_s(direction_t direction)
{
    if (direction == EAST)
    {
        return "e";
    }
    else if (direction == WEST)
    {
        return "w";
    }
    else if (direction == NORTH)
    {
        return "n";
    }
    else if (direction == SOUTH)
    {
        return "s";
    }
    else
    {
        return "Error";
    }
}

// find the direction from direction_t to string in long form
string directionFind_L(direction_t direction)
{
    if (direction == EAST)
    {
        return "east";
    }
    else if (direction == WEST)
    {
        return "west";
    }
    else if (direction == NORTH)
    {
        return "north";
    }
    else if (direction == SOUTH)
    {
        return "south";
    }
    else
    {
        return "Error";
    }
}

// get the species
void getSpecies(world_t &world, const string &speciesName, unsigned int creatureCount)
{
    for (unsigned int i = 0; i < world.numSpecies; i++)
    {
        if (world.species[i].name == speciesName)
        {
            world.creatures[creatureCount].species = &world.species[i];
            return;
            // cout << "Species: " << world.creatures[creatureCount].species->name << endl;
        }
    }
    cout << "Error: Species " << speciesName << " not found!" << endl;
    exit(0);
    return;
}

// read the command in the species file
void readCommand(const string &line, instruction_t &instruction)
{
    istringstream iss(line);
    string command;
    iss >> command;
    if (command == "hop")
    {
        instruction.op = HOP;
        instruction.address = 0;
    }
    else if (command == "left")
    {
        instruction.op = LEFT;
        instruction.address = 0;
    }
    else if (command == "right")
    {
        instruction.op = RIGHT;
        instruction.address = 0;
    }
    else if (command == "infect")
    {
        instruction.op = INFECT;
        instruction.address = 0;
    }
    else if (command == "ifempty")
    {
        instruction.op = IFEMPTY;
        iss >> instruction.address;
    }
    else if (command == "ifwall")
    {
        instruction.op = IFWALL;
        iss >> instruction.address;
    }
    else if (command == "ifsame")
    {
        instruction.op = IFSAME;
        iss >> instruction.address;
    }
    else if (command == "ifenemy")
    {
        instruction.op = IFENEMY;
        iss >> instruction.address;
    }
    else if (command == "go")
    {
        instruction.op = GO;
        iss >> instruction.address;
    }
    else
    {
        cout << "Error: Instruction " << command << " is not recognized!" << endl;
        exit(0);
    }
}

// simulate the world
void simulation(world_t &world, int rounds, bool verbose)
{
    for (int i = 0; i < rounds; i++)
    {
        cout << "Round " << i + 1 << endl;
        for (unsigned int j = 0; j < world.numCreatures; j++)
        {
            simulateCreature(world.creatures[j], world.grid, verbose);
        }
        if (!verbose)
        {
            printGrid(world.grid);
        }
    }
}

// simulate the creature
void simulateCreature(creature_t &creature, grid_t &grid, bool verbose)
{
    if (verbose)
    {
        cout << "Creature (" << creature.species->name << " " << directionFind_L(creature.direction) << " " << creature.location.r << " " << creature.location.c << ") takes action:" << endl;

        // printInstruction(instruction);
        play(creature, grid, verbose);
        printGrid(grid);
    }
    else
    {
        cout << "Creature (" << creature.species->name << " " << directionFind_L(creature.direction) << " " << creature.location.r << " " << creature.location.c << ") takes action:";
        play(creature, grid, verbose);
    }

    return;
}

// the logic of the creature
void play(creature_t &creature, grid_t &grid, bool verbose)
{
    instruction_t instruction = getInstruction(creature);
    while (instruction.op != HOP && instruction.op != LEFT && instruction.op != RIGHT && instruction.op != INFECT)
    {
        if (verbose)
        {
            printInstruction(instruction, creature);
        }
        if (instruction.op == IFEMPTY)
        {
            if (isEmpty(adjacentPoint(creature.location, creature.direction), grid))
            {
                creature.programID = instruction.address - 1;
            }
            else
            {
                creature.programID++;
            }
        }
        else if (instruction.op == IFENEMY)
        {
            if (isEnemy(creature, adjacentPoint(creature.location, creature.direction), grid))
            {
                creature.programID = instruction.address - 1;
            }
            else
            {
                creature.programID++;
            }
        }
        else if (instruction.op == IFSAME)
        {
            if (isSame(creature, adjacentPoint(creature.location, creature.direction), grid))
            {
                creature.programID = instruction.address - 1;
            }
            else
            {
                creature.programID++;
            }
        }
        else if (instruction.op == IFWALL)
        {
            if (isWall(adjacentPoint(creature.location, creature.direction), grid))
            {
                creature.programID = instruction.address - 1;
            }
            else
            {
                creature.programID++;
            }
        }
        else if (instruction.op == GO)
        {
            creature.programID = instruction.address - 1;
        }
        instruction = getInstruction(creature);
    }
    if (verbose)
    {
        printInstruction(instruction, creature);
    }
    else
    {
        cout << " " << opName[instruction.op] << endl;
    }
    if (instruction.op == HOP)
    {
        point_t newPoint = adjacentPoint(creature.location, creature.direction);
        if (isWall(newPoint, grid))
        {
            creature.programID++;
        }
        else if (!isEmpty(newPoint, grid))
        {
            creature.programID++;
        }
        else
        {
            grid.squares[creature.location.r][creature.location.c] = NULL;
            creature.location = newPoint;
            grid.squares[creature.location.r][creature.location.c] = &creature;
            creature.programID++;
        }
    }
    else if (instruction.op == LEFT)
    {
        creature.direction = leftFrom(creature.direction);
        creature.programID++;
    }
    else if (instruction.op == RIGHT)
    {
        creature.direction = rightFrom(creature.direction);
        creature.programID++;
    }
    else if (instruction.op == INFECT)
    {
        point_t newPoint = adjacentPoint(creature.location, creature.direction);
        if (isWall(newPoint, grid))
        {
            creature.programID++;
        }
        else if (isEmpty(newPoint, grid))
        {
            creature.programID++;
        }
        else if (isSame(creature, newPoint, grid))
        {
            creature.programID++;
        }
        else
        {
            grid.squares[newPoint.r][newPoint.c]->species = creature.species;
            grid.squares[newPoint.r][newPoint.c]->programID = 0;
            creature.programID++;
        }
    }
    return;
}

// check if the point is a wall
bool isWall(const point_t &pt, const grid_t &grid)
{
    if (pt.r < 0 || pt.r >= static_cast<int>(grid.height) || pt.c < 0 || pt.c >= static_cast<int>(grid.width))
    {
        return true;
    }
    return false;
}

// check if the point is empty
bool isEmpty(const point_t &pt, const grid_t &grid)
{
    if (isWall(pt, grid))
    {
        return false;
    }
    else if (grid.squares[pt.r][pt.c] == NULL)
    {
        return true;
    }
    return false;
}

// check if the point is an enemy
bool isEnemy(const creature_t &creature, const point_t &pt, const grid_t &grid)
{
    if (isWall(pt, grid))
    {
        return false;
    }
    else if (grid.squares[pt.r][pt.c] == NULL)
    {
        return false;
    }
    else if (grid.squares[pt.r][pt.c]->species->name != creature.species->name)
    {
        return true;
    }
    return false;
}

// check if the point is the same species
bool isSame(const creature_t &creature, const point_t &pt, const grid_t &grid)
{
    if (isWall(pt, grid))
    {
        return false;
    }
    else if (grid.squares[pt.r][pt.c] == NULL)
    {
        return false;
    }
    else if (grid.squares[pt.r][pt.c]->species->name == creature.species->name)
    {
        return true;
    }
    return false;
}

// print the grid
void printGrid(const grid_t &grid)
{
    for (unsigned int i = 0; i < grid.height; i++)
    {
        for (unsigned int j = 0; j < grid.width; j++)
        {
            if (grid.squares[i][j] == NULL)
            {
                cout << "____ ";
            }
            else
            {
                cout << grid.squares[i][j]->species->name[0] << grid.squares[i][j]->species->name[1] << "_" << directionFind_s(grid.squares[i][j]->direction) << " ";
            }
        }
        cout << endl;
    }

    return;
}

// get the adjacent point
point_t adjacentPoint(point_t pt, direction_t dir)
{

    point_t newPoint;
    newPoint.r = pt.r;
    newPoint.c = pt.c;

    if (dir == EAST)
    {
        newPoint.c++;
    }
    else if (dir == WEST)
    {
        newPoint.c--;
    }
    else if (dir == NORTH)
    {
        newPoint.r--;
    }
    else if (dir == SOUTH)
    {
        newPoint.r++;
    }

    return newPoint;
}

// get the left direction
direction_t leftFrom(direction_t dir)
{
    if (dir == EAST)
    {
        return NORTH;
    }
    else if (dir == WEST)
    {
        return SOUTH;
    }
    else if (dir == NORTH)
    {
        return WEST;
    }
    else if (dir == SOUTH)
    {
        return EAST;
    }
    return dir;
}

// get the right direction
direction_t rightFrom(direction_t dir)
{
    if (dir == EAST)
    {
        return SOUTH;
    }
    else if (dir == WEST)
    {
        return NORTH;
    }
    else if (dir == NORTH)
    {
        return EAST;
    }
    else if (dir == SOUTH)
    {
        return WEST;
    }
    return dir;
}

// get the instruction of the creature
instruction_t getInstruction(const creature_t &creature)
{
    return creature.species->program[creature.programID];
}

// get the creature at the location
creature_t *getCreature(const grid_t &grid, point_t location)
{
    return grid.squares[location.r][location.c];
}

// void printCreature(const creature_t &creature)
// {
//     cout << "Location: " << creature.location.r << " " << creature.location.c << endl;
//     cout << "Direction: " << creature.direction << endl;
//     cout << "Species: " << creature.species->name << endl;
//     cout << "Program ID: " << creature.programID << endl;
// }

// print the instruction
void printInstruction(const instruction_t &instruction, const creature_t &creature)
{
    cout << "Instruction " << creature.programID + 1 << ": " << opName[instruction.op];
    if (instruction.address == 0)
    {
        cout << endl;
    }
    else
    {
        cout << " " << instruction.address << endl;
    }
}

// void printSpecies(const species_t &species)
// {
//     cout << "Species: " << species.name << endl;
//     cout << "Program Size: " << species.programSize << endl;
//     for (unsigned int i = 0; i < species.programSize; i++)
//     {
//         printInstruction(species.program[i], species);
//     }
// }