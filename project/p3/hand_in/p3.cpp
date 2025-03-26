#include "simulation.h"

using namespace std;

int main(int argc, char *argv[])
{
    // test the command line arguments
    if (argc < 4)
    {
        cout << "Error: Missing arguments!" << endl;
        cout << "Usage: ./p3 <species-summary> <world-file> <rounds> [v|verbose]" << endl;
        return 0;
    }
    // get the command line arguments
    string speciesSummaryDirectory = argv[1];
    string worldFileDirctory = argv[2];
    int rounds = atoi(argv[3]);
    bool verbose = false;
    // check the validity of the arguments
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

    // initialize the world
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
    speciesSummary.close();

    // cout << "Species file directory: " << speciesFileDirectory << endl;

    // initialize the world
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

    // print the initial state of the world
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

    // simulate the world
    simulation(world, rounds, verbose);
    return 0;
}