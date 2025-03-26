#include "dlist.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <cassert>

using namespace std;

// status of the customer
enum class status
{
    PLATINUM,
    GOLD,
    SILVER,
    REGULAR
};

// status name
const string statusName[] = {"platinum", "gold", "silver", "regular"};

// call struct
struct call
{
    int timestamp;
    string name;
    enum status status;
    int duration;
};

void readCommand(std::string &list, call &call);
void answerCall(Dlist<call> &Platinum, Dlist<call> &Gold, Dlist<call> &Silver, Dlist<call> &Regular, int &done, int &agentBusy);

int main()
{
    // get the number of customer
    int customerNum = 0;
    string number;
    getline(cin, number);
    customerNum = stoi(number);

    // get the call list
    call *callList = new call[customerNum];
    string list;
    int customerID = 0;
    while (getline(cin, list))
    {
        readCommand(list, callList[customerID]);
        customerID++;
    }

    // initial the tick
    int tick = 0;
    int done = 0;
    int agentBusy = 0;

    // initial the queue
    Dlist<call> Platinum;
    Dlist<call> Gold;
    Dlist<call> Silver;
    Dlist<call> Regular;

    // process the call
    while (done < customerNum)
    {
        cout << "Starting tick #" << tick << endl;
        // check if any more call is coming
        for (int i = 0; i < customerNum; i++)
        {
            if (callList[i].timestamp == tick)
            {
                if (callList[i].status == status::PLATINUM)
                {
                    Platinum.insertBack(&callList[i]);
                    cout << "Call from " << callList[i].name << " a " << statusName[0] << " member\n";
                }
                else if (callList[i].status == status::GOLD)
                {
                    Gold.insertBack(&callList[i]);
                    cout << "Call from " << callList[i].name << " a " << statusName[1] << " member\n";
                }
                else if (callList[i].status == status::SILVER)
                {
                    Silver.insertBack(&callList[i]);
                    cout << "Call from " << callList[i].name << " a " << statusName[2] << " member\n";
                }
                else
                {
                    Regular.insertBack(&callList[i]);
                    cout << "Call from " << callList[i].name << " a " << statusName[3] << " member\n";
                }
            }
        }
        // answer the call
        answerCall(Platinum, Gold, Silver, Regular, done, agentBusy);
        tick++;
    }
    cout << "Starting tick #" << tick << endl;

    // delete the call list
    delete[] callList;
    return 0;
}

void readCommand(std::string &list, call &call)
{
    // extract the timestamp
    string timestamp = list.substr(0, list.find(" "));
    list = list.substr(list.find(" ") + 1);
    // extract the name
    string name = list.substr(0, list.find(" "));
    list = list.substr(list.find(" ") + 1);
    // extract the status
    string status = list.substr(0, list.find(" "));
    // extract the duration
    string duration = list.substr(list.find(" ") + 1);

    // install the call
    call.timestamp = stoi(timestamp);
    call.name = name;
    if (status == "platinum")
    {
        call.status = status::PLATINUM;
    }
    else if (status == "gold")
    {
        call.status = status::GOLD;
    }
    else if (status == "silver")
    {
        call.status = status::SILVER;
    }
    else
    {
        call.status = status::REGULAR;
    }
    call.duration = stoi(duration);
}

void answerCall(Dlist<call> &Platinum, Dlist<call> &Gold, Dlist<call> &Silver, Dlist<call> &Regular, int &done, int &agentBusy)
{
    // check if the agent is busy
    if (agentBusy == 0)
    {
        if (!Platinum.isEmpty())
        {
            call *op = Platinum.removeFront();
            // the agent busy time is the duration of the call minus 1 because the agent is answering the call in this tick
            agentBusy = op->duration - 1;
            // if the duration time is 0, the call is done in this tick
            if (agentBusy == 0)
            {
                done++;
            }
            cout << "Answering call from " << op->name << endl;
        }
        else if (!Gold.isEmpty())
        {
            call *op = Gold.removeFront();
            // the agent busy time is the duration of the call minus 1 because the agent is answering the call in this tick
            agentBusy = op->duration - 1;
            // if the duration time is 0, the call is done in this tick
            if (agentBusy == 0)
            {
                done++;
            }
            cout << "Answering call from " << op->name << endl;
        }
        else if (!Silver.isEmpty())
        {
            call *op = Silver.removeFront();
            // the agent busy time is the duration of the call minus 1 because the agent is answering the call in this tick
            agentBusy = op->duration - 1;
            // if the duration time is 0, the call is done in this tick
            if (agentBusy == 0)
            {
                done++;
            }
            cout << "Answering call from " << op->name << endl;
        }
        else if (!Regular.isEmpty())
        {
            call *op = Regular.removeFront();
            // the agent busy time is the duration of the call minus 1 because the agent is answering the call in this tick
            agentBusy = op->duration - 1;
            // if the duration time is 0, the call is done in this tick
            if (agentBusy == 0)
            {
                done++;
            }
            cout << "Answering call from " << op->name << endl;
        }
        else
        {
            return;
        }
    }
    else
    {
        // the agent is busy
        agentBusy--;
        if (agentBusy == 0)
        {
            done++;
        }
    }
}
