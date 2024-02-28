#pragma once

#include <utility>
#include <vector>

using namespace std;

struct Point
{
    double x;
    double y;
};

struct Square
{
    bool covered = false;
    Point left_corner{};
};

struct Segment
{
    double begin;
    double end;
};

struct TaskData
{
    unsigned int side_length;
    vector<Square> squares;
};

struct TaskResults
{
    double total_time;
    double step_time;
    unsigned long int steps;
    unsigned long int error_amount = 0;
    vector<Point> points;
};

class Task
{
    public:
        explicit Task(TaskData data) : data(std::move(data)) {}

        TaskResults res{};

        void complex_version();

        void simple_version();

private:

        TaskData data{};

        static int intersection(const Segment &first, const Segment &second);

        Point *middle(unsigned int first, unsigned int second);

};
