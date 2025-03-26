#ifndef SIMULATION_H
#define SIMULATION_H

#include "world_type.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <cassert>

bool initWorld(world_t &world, const std::string &speciesFileDirectory, const std::string speciesName[], const std::string &worldFileDirectory);
void setSpecies(world_t &world, const std::string &speciesFileDirectory, const std::string speciesName[]);
void setGrid(world_t &world, const std::string &worldFileDirectory);
direction_t findDirection(const std::string &direction);
std::string directionFind_s(direction_t direction);
std::string directionFind_L(direction_t direction);
void buildEmptyGrid(world_t &world);
void getSpecies(world_t &world, const std::string &speciesName, unsigned int creatureCount);
void setCreature(creature_t &creature, const std::string line, world_t &world, unsigned int creatureCount);
void readCommand(const std::string &line, instruction_t &instruction);
void simulateCreature(creature_t &creature, grid_t &grid, bool verbose);
void printGrid(const grid_t &grid);
void simulation(world_t &world, int rounds, bool verbose);
point_t adjacentPoint(point_t pt, direction_t dir);
direction_t leftFrom(direction_t dir);
direction_t rightFrom(direction_t dir);
void printCreature(const creature_t &creature);
void printInstruction(const instruction_t &instruction, const creature_t &creature);
// void printSpecies(const species_t &species);
instruction_t getInstruction(const creature_t &creature);
creature_t *getCreature(const grid_t &grid, point_t location);
void play(creature_t &creature, grid_t &grid, bool verbose);
bool isEmpty(const point_t &pt, const grid_t &grid);
bool isWall(const point_t &pt, const grid_t &grid);
bool isEnemy(const creature_t &creature, const point_t &pt, const grid_t &grid);
bool isSame(const creature_t &creature, const point_t &pt, const grid_t &grid);

#endif // SIMULATION_H