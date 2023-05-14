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
#include <sstream>

using namespace std;

void print(string cmd, StatusType res);
void print(string cmd, output_t<int> res);
void query_get_all_movies(string cmd, streaming_database *obj, Genre genre);

int main()
{
    std::streambuf* orig = std::cin.rdbuf();
    std::istringstream input("add_user_to_group 29076 3836\n"
                             "add_group 26348\n"
                             "add_group 5304\n"
                             "remove_movie 34152\n"
                             "rate_movie 34212 37408 86\n"
                             "user_watch 48722 20888\n"
                             "get_num_views 24991 1\n"
                             "add_group 26143\n"
                             "user_watch 48464 9959\n"
                             "add_group 25771\n"
                             "add_movie 22189 1 16 False\n"
                             "get_all_movies 4\n"
                             "add_group 32937\n"
                             "add_user_to_group 27526 32937\n"
                             "group_watch 37423 22189\n"
                             "add_user 5257 False\n"
                             "get_all_movies_count 3\n"
                             "get_group_recommendation 46742\n"
                             "remove_movie 22189\n"
                             "add_group 49\n"
                             "get_all_movies_count 0\n"
                             "get_all_movies_count 1\n"
                             "remove_user 5257\n"
                             "add_group 37800\n"
                             "get_num_views 25951 1\n"
                             "get_all_movies_count 3\n"
                             "add_user 44579 False\n"
                             "get_group_recommendation 17870\n"
                             "add_user_to_group 44579 26143\n"
                             "remove_group 25771\n"
                             "group_watch 26143 17562\n"
                             "remove_group 49\n"
                             "add_user_to_group 3634 5304\n"
                             "add_movie 40343 1 7 True\n"
                             "get_all_movies_count 2\n"
                             "add_group 10170\n"
                             "add_movie 39489 3 1 True\n"
                             "group_watch 26143 37719\n"
                             "add_group 37099\n"
                             "add_movie 44059 3 9 False\n"
                             "get_group_recommendation 26143\n"
                             "group_watch 26143 44059\n"
                             "remove_movie 40343\n"
                             "user_watch 44579 44059\n"
                             "user_watch 44579 44059\n"
                             "add_movie 17167 0 11 True\n"
                             "add_group 38192\n"
                             "add_user_to_group 10247 38192\n"
                             "user_watch 44579 44059\n"
                             "get_all_movies_count 4\n"
                             "add_user 448 False\n"
                             "group_watch 26143 44059\n"
                             "add_user 41050 True\n"
                             "add_group 41587\n"
                             "get_all_movies 3\n"
                             "group_watch 26143 44059\n"
                             "add_movie 23159 2 4 True\n"
                             "user_watch 41050 44059\n"
                             "add_user_to_group 41050 32937\n"
                             "remove_movie 39489\n"
                             "get_num_views 41050 4\n"
                             "add_group 46171\n"
                             "user_watch 41050 23159\n"
                             "get_num_views 41050 2\n"
                             "user_watch 41050 17167\n"
                             "user_watch 41050 23159\n"
                             "group_watch 32937 44059\n"
                             "user_watch 44579 44059\n"
                             "group_watch 32937 23159\n"
                             "remove_group 32937\n"
                             "add_movie 19652 4 5 False\n"
                             "add_group 4786\n"
                             "remove_group 26348\n"
                             "get_group_recommendation 26143\n"
                             "get_group_recommendation 26143\n"
                             "user_watch 448 44059\n"
                             "get_all_movies 1\n"
                             "add_movie 29318 3 19 False\n"
                             "user_watch 41050 29318\n"
                             "add_movie 29281 2 3 True\n"
                             "user_watch 41050 29318\n"
                             "get_all_movies 1\n"
                             "get_all_movies 0\n"
                             "add_user_to_group 41050 38192\n"
                             "get_all_movies_count 2\n"
                             "get_all_movies_count 3\n"
                             "add_movie 2772 0 14 False\n"
                             "add_user_to_group 448 38192\n"
                             "get_all_movies 0\n"
                             "get_all_movies 2\n"
                             "add_user_to_group 11753 37099\n"
                             "get_group_recommendation 26143\n"
                             "remove_movie 44059\n"
                             "remove_user 448\n"
                             "get_all_movies 1\n"
                             "get_all_movies_count 2\n"
                             "remove_group 10170\n"
                             "remove_group 46171\n"
                             "get_num_views 44579 3\n"
                             "add_user_to_group 42147 37099\n"
                             "get_all_movies_count 0\n"
                             "add_movie 35004 3 20 True\n"
                             "add_group 30729\n"
                             "add_group 35460\n"
                             "get_all_movies_count 2\n"
                             "get_all_movies 0\n"
                             "group_watch 38192 29318\n"
                             "user_watch 41050 29318\n"
                             "user_watch 44579 2772\n"
                             "get_all_movies_count 0\n"
                             "get_group_recommendation 26143\n"
                             "add_user_to_group 9673 37099\n"
                             "user_watch 44579 2772\n"
                             "add_movie 6653 1 12 True\n"
                             "group_watch 38192 35004\n"
                             "add_group 3176\n"
                             "add_user_to_group 2278 41587\n"
                             "group_watch 38192 35004\n"
                             "user_watch 41050 17167\n"
                             "get_num_views 41050 0\n"
                             "user_watch 44579 29318\n"
                             "group_watch 26143 2772\n"
                             "remove_group 26143\n"
                             "add_user_to_group 44579 35460\n"
                             "get_all_movies 3\n"
                             "add_movie 23161 4 19 True\n"
                             "add_user_to_group 1404 4786\n"
                             "add_user_to_group 45872 37800\n"
                             "get_group_recommendation 38192\n"
                             "add_user 32741 False\n"
                             "remove_movie 23159\n"
                             "add_group 6530\n"
                             "rate_movie 44579 29318 17\n"
                             "get_all_movies 3\n"
                             "rate_movie 44579 2772 35\n"
                             "remove_movie 2772\n"
                             "user_watch 44579 29318\n"
                             "remove_user 32741\n"
                             "add_user 20129 True\n"
                             "group_watch 38192 29318\n"
                             "remove_group 3176\n"
                             "get_group_recommendation 35460\n"
                             "add_user_to_group 20129 41587\n"
                             "user_watch 44579 29318\n"
                             "user_watch 44579 29318\n"
                             "get_all_movies 0\n"
                             "user_watch 44579 29318\n"
                             "get_group_recommendation 35460\n"
                             "remove_user 20129\n"
                             "add_group 21233\n"
                             "remove_group 37099\n"
                             "get_num_views 41050 3\n"
                             "add_user 46636 True\n"
                             "add_group 16278\n"
                             "get_all_movies 4\n"
                             "get_num_views 46636 2\n"
                             "remove_group 16278\n"
                             "add_user_to_group 46636 37800\n"
                             "group_watch 38192 6653\n"
                             "get_group_recommendation 38192\n"
                             "remove_user 44579\n"
                             "add_group 5417\n"
                             "get_group_recommendation 38192\n"
                             "remove_group 37800\n"
                             "add_movie 26386 1 13 False\n"
                             "user_watch 41050 29318\n"
                             "user_watch 32023 29318\n"
                             "get_all_movies_count 2\n"
                             "add_user_to_group 46636 5417\n"
                             "remove_user 46636\n"
                             "remove_user 41050\n"
                             "rate_movie 48046 26386 56\n"
                             "add_user_to_group 7296 5304\n"
                             "get_all_movies 1\n"
                             "add_group 12746\n"
                             "add_user_to_group 37719 5417\n"
                             "get_group_recommendation 32038\n"
                             "add_movie 23904 0 18 True\n"
                             "add_user 47461 False\n"
                             "get_all_movies 0\n"
                             "add_group 29018\n"
                             "get_num_views 47461 1\n"
                             "get_all_movies 1\n"
                             "user_watch 18730 23904\n"
                             "get_all_movies 0\n"
                             "add_user_to_group 47461 12746\n"
                             "add_user 28012 True\n"
                             "add_user_to_group 28012 5304\n"
                             "add_user 10393 False\n"
                             "get_group_recommendation 5304\n"
                             "group_watch 12746 26386\n"
                             "get_group_recommendation 5304\n"
                             "get_group_recommendation 5304\n"
                             "add_movie 27654 1 12 True\n"
                             "remove_movie 27654\n"
                             "group_watch 12746 29318\n"
                             "add_user 3579 True\n"
                             "get_all_movies_count 0\n"
                             "remove_user 10393\n"
                             "rate_movie 28012 29318 88");

    std::cin.rdbuf(input.rdbuf());
    int d1, d2, d3, g1;
    string b1;
    bool b;

    // Init
    streaming_database *obj = new streaming_database();

    // Execute all commands in file
    string op;
    while (cin >> op)
    {
        if (!op.compare("add_movie")) {
            cin >> d1 >> g1 >> d2 >> b1;
            if (!b1.compare("True")) {
                b = true;
            }
            else if (!b1.compare("False")) {
                b = false;
            }
            else {
                cout << "Invalid input format" << endl;
                return -1;
            }
            print(op, obj->add_movie(d1, (Genre) g1, d2, b));
        } else if (!op.compare("remove_movie")) {
            cin >> d1;
            print(op, obj->remove_movie(d1));
        } else if (!op.compare("add_user")) {
            cin >> d1 >> b1;
            if (!b1.compare("True")) {
                b = true;
            }
            else if (!b1.compare("False")) {
                b = false;
            }
            else {
                cout << "Invalid input format" << endl;
                return -1;
            }
            print(op, obj->add_user(d1, b));
        } else if (!op.compare("remove_user")) {
            cin >> d1;
            print(op, obj->remove_user(d1));
        } else if (!op.compare("add_group")) {
            cin >> d1;
            print(op, obj->add_group(d1));
        } else if (!op.compare("remove_group")) {
            cin >> d1;
            print(op, obj->remove_group(d1));
        } else if (!op.compare("add_user_to_group")) {
            cin >> d1 >> d2;
            print(op, obj->add_user_to_group(d1, d2));
        } else if (!op.compare("get_all_movies_count")) {
            cin >> g1;
            print(op, obj->get_all_movies_count((Genre) g1));
        } else if (!op.compare("get_all_movies")) {
            cin >> g1;
            query_get_all_movies(op, obj, (Genre) g1);
        } else if (!op.compare("user_watch")) {
            cin >> d1 >> d2;
            print(op, obj->user_watch(d1, d2));
        } else if (!op.compare("group_watch")) {
            cin >> d1 >> d2;
            print(op, obj->group_watch(d1, d2));
        } else if (!op.compare("get_num_views")) {
            cin >> d1 >> g1;
            print(op, obj->get_num_views(d1, (Genre) g1));
        } else if (!op.compare("rate_movie")) {
            cin >> d1 >> d2 >> d3;
            print(op, obj->rate_movie(d1, d2, d3));
        } else if (!op.compare("get_group_recommendation")) {
            cin >> d1;
            print(op, obj->get_group_recommendation(d1));
        } else {
            cout << "Unknown command: " << op << endl;
            return -1;
        }
        // Verify no faults
        if (cin.fail()){
            cout << "Invalid input format" << endl;
            return -1;
        }
    }
    std::cin.rdbuf(orig);
    // Quit
    delete obj;
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

void print(string cmd, StatusType res)
{
    cout << cmd << ": " << StatusTypeStr[(int) res] << endl;
}

void print(string cmd, output_t<int> res)
{
    if (res.status() == StatusType::SUCCESS) {
        cout << cmd << ": " << StatusTypeStr[(int) res.status()] << ", " << res.ans() << endl;
    } else {
        cout << cmd << ": " << StatusTypeStr[(int) res.status()] << endl;
    }
}

void query_get_all_movies(string cmd, streaming_database *obj, Genre genre)
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
    print(cmd, status);
    if (status == StatusType::SUCCESS) {
        for (int i = 0; i < to_alloc; ++i)
        {
            cout << out_mem[i] << endl;
        }
    }
    delete[] out_mem;
}
