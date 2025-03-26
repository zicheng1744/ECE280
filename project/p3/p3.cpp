#include "simulation.h"

using namespace std;

int main(int argc, char *argv[])
{
    if (argc < 4)
    {
        cout << "Error: Missing arguments!" << endl;
        cout << "Usage: ./p3 <species-summary> <world-file> <rounds> [v|verbose]" << endl;
        return 0;
    }
    string speciesSummaryDirectory = argv[1];
    string worldFileDirctory = argv[2];
    int rounds = atoi(argv[3]);
    bool verbose = false;
    if (rounds < 0)
    {
        cout << "Error: Number of simulation rounds is negative!" << endl;
        return 0;
    }
    if (argc == 5)
    {
        string strverbose = argv[4];
        if (strverbose == "v" || strverbose == "verbose")
        {
            verbose = true;
        }
        else
        {
            cout << "Error: Invalid argument " << verbose << "!" << endl;
            cout << "Usage: ./p3 <species-summary> <world-file> <rounds> [v|verbose]" << endl;
            return 0;
        }
    }
    world_t world;
    ifstream speciesSummary(speciesSummaryDirectory);
    if (!speciesSummary.is_open())
    {
        cout << "Error: Cannot open file " << speciesSummaryDirectory << "!" << endl;
        return 0;
    }
    // the first line of the file is the directory of the species files
    string speciesFileDirectory;
    getline(speciesSummary, speciesFileDirectory);
    // the following lines are the species file names
    string speciesName[MAXSPECIES];
    string speciesNames;
    world.numSpecies = 0;
    while (getline(speciesSummary, speciesNames))
    {
        if (world.numSpecies == MAXSPECIES)
        {
            cout << "Error: Too many species!" << endl;
            cout << "Maximal number of species is " << MAXSPECIES << "." << endl;
            return 0;
        }
        world.species[world.numSpecies].name = speciesNames;
        speciesName[world.numSpecies] = speciesNames;
        world.numSpecies++;
    }

    // cout << "Species file directory: " << speciesFileDirectory << endl;

    initWorld(world, speciesFileDirectory, speciesName, worldFileDirctory);
    // for (unsigned int i = 0; i < world.numCreatures; i++)
    // {
    //     printCreature(world.creatures[0]);
    // }
    // for (unsigned int i = 0; i < world.numSpecies; i++)
    // {
    //     printInstruction(world.species[i].program[0]);
    // }
    // cout << world.numSpecies << endl;
    cout << "Initial state" << endl;
    printGrid(world.grid);
    // for (unsigned int i = 0; i < world.numSpecies; i++)
    // {
    //     printSpecies(world.species[i]);
    // }
    //  cout << "Number of species: " << world.numSpecies << endl;
    //  cout << "Number of creatures: " << world.numCreatures << endl;
    //  cout << "Grid height: " << world.grid.height << endl;
    //  cout << "Grid width: " << world.grid.width << endl;
    //  cout << "Number of rounds: " << rounds << endl;
    //  cout << "Verbose: " << verbose << endl;
    simulation(world, rounds, verbose);
    return 0;
}