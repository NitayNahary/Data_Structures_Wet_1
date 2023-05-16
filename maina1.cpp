//
// 234218 Data Structures 1.
// Semester: 2023B (spring).
// Wet Exercise #1.
//
// Recommended TAB m_size to view this file: 8.
//
// The following main file is necessary to link and run your code.
// This file is READ ONLY: even if you submit something else, the compiler ..
// .. WILL use our file.
//

#include "StreamingDBa1.h"
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

void print(string cmd, StatusType res, ofstream& of);
void print(string cmd, output_t<int> res, ofstream& of);
void query_get_all_movies(string cmd, streaming_database *obj, Genre genre, ofstream& of);

int main()
{

//
    int d1, d2, d3, g1;
    string b1;
    bool b;

    // Init
    std::string op;
    std::ifstream nameFilein;
    std::string inputName, outputName;
    for(int i = 175; i < 176; i++) {
        streaming_database *obj = new streaming_database();
        inputName = "Testing/inFiles/test" + to_string(i) + ".in";
        outputName = "Testing/result_outFiles/test_result" + to_string(i) + ".txt";
        nameFilein.open(inputName);
        cout << i<< endl;
        std::ofstream nameFileout(outputName);
        while (nameFilein >> op) {
            cout << op << endl;
            if (!op.compare("add_movie")) {
                nameFilein >> d1 >> g1 >> d2 >> b1;
                if (!b1.compare("True")) {
                    b = true;
                }
                else if (!b1.compare("False")) {
                    b = false;
                }
                else {
                    nameFileout << "Invalid input format" << endl;
                    return -1;
                }
                print(op, obj->add_movie(d1, (Genre) g1, d2, b),nameFileout);
            } else if (!op.compare("remove_movie")) {
                nameFilein >> d1;
                print(op, obj->remove_movie(d1),nameFileout);
            } else if (!op.compare("add_user")) {
                nameFilein >> d1 >> b1;
                if (!b1.compare("True")) {
                    b = true;
                }
                else if (!b1.compare("False")) {
                    b = false;
                }
                else {
                    nameFileout << "Invalid input format" << endl;
                    return -1;
                }
                print(op, obj->add_user(d1, b),nameFileout);
            } else if (!op.compare("remove_user")) {
                nameFilein >> d1;
                print(op, obj->remove_user(d1),nameFileout);
            } else if (!op.compare("add_group")) {
                nameFilein >> d1;
                print(op, obj->add_group(d1),nameFileout);
            } else if (!op.compare("remove_group")) {
                nameFilein >> d1;
                print(op, obj->remove_group(d1),nameFileout);
            } else if (!op.compare("add_user_to_group")) {
                nameFilein >> d1 >> d2;
                print(op, obj->add_user_to_group(d1, d2),nameFileout);
            } else if (!op.compare("get_all_movies_count")) {
                nameFilein >> g1;
                print(op, obj->get_all_movies_count((Genre) g1),nameFileout);
            } else if (!op.compare("get_all_movies")) {
                nameFilein >> g1;
                query_get_all_movies(op, obj, (Genre) g1,nameFileout);
            } else if (!op.compare("user_watch")) {
                nameFilein >> d1 >> d2;
                print(op, obj->user_watch(d1, d2),nameFileout);
            } else if (!op.compare("group_watch")) {
                nameFilein >> d1 >> d2;
                print(op, obj->group_watch(d1, d2),nameFileout);
            } else if (!op.compare("get_num_views")) {
                nameFilein >> d1 >> g1;
                print(op, obj->get_num_views(d1, (Genre) g1),nameFileout);
            } else if (!op.compare("rate_movie")) {
                nameFilein >> d1 >> d2 >> d3;
                print(op, obj->rate_movie(d1, d2, d3),nameFileout);
            } else if (!op.compare("get_group_recommendation")) {
                nameFilein >> d1;
                print(op, obj->get_group_recommendation(d1),nameFileout);
            } else {
                nameFileout << "Unknown command: " << op << endl;
                return -1;
            }
        // Verify no faults
            if (nameFileout.fail()){
                nameFileout << "Invalid input format" << endl;
                return -1;
            }
        }
    // Quit
        delete obj;
        nameFileout.close();
        nameFilein.close();
    }
    return 0;
}


// Helpers
static const char *StatusTypeStr[] =
        {
                "SUCCESS",
                "ALLOCATION_ERROR",
                "INVALID_INPUT",
                "FAILURE"
        };

void print(string cmd, StatusType res, ofstream& of)
{
    of << cmd << ": " << StatusTypeStr[(int) res] << endl;
}

void print(string cmd, output_t<int> res, ofstream& of)
{
    if (res.status() == StatusType::SUCCESS) {
        of << cmd << ": " << StatusTypeStr[(int) res.status()] << ", " << res.ans() << endl;
    } else {
        of << cmd << ": " << StatusTypeStr[(int) res.status()] << endl;
    }
}

void query_get_all_movies(string cmd, streaming_database *obj, Genre genre, ofstream& of)
{
    output_t<int> count = obj->get_all_movies_count(genre);
    int to_alloc = count.ans();
    if (to_alloc == 0)
    {
        //if there are no movies we will allocate 1 so that we will get failure instead of invalid input
        ++to_alloc;
    }
    // Allocate if okay
    int *out_mem = nullptr;
    if (count.status() == StatusType::SUCCESS)
    {
        out_mem = new int[to_alloc];
        for (int i = 0; i < to_alloc; ++i) out_mem[i] = -1;
    }
    // Call function
    StatusType status = obj->get_all_movies(genre, out_mem);
    print(cmd, status,of);
    if (status == StatusType::SUCCESS) {
        for (int i = 0; i < to_alloc; ++i)
        {
            of << out_mem[i] << endl;
        }
    }
    delete[] out_mem;
}
