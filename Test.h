#pragma once
#include "task.h"
#include <random>
#include <cmath>

struct TestData
{
    unsigned int tests_amount;
    unsigned int side_length;
    unsigned long int squares_amount;
};

struct TestResultsExtended
{
    unsigned int squares_amount = 0;
    double average_total_time = 0;
    double average_step_time = 0;
    unsigned long int average_steps = 0;
    unsigned long int average_points = 0;
    unsigned long int average_error_amount = 0;
    vector<TaskResults> task_results;
};

class Test
{
    public:

        explicit Test(TestData data) : test_data(data){}

        void simple_test();

        void random_test_algorithm();

        void algorithm_results_console_print();

        void increase_random_test(unsigned int increase_squares, unsigned int step);

        void check_point(const vector <Square>& squares, const vector <Point>& points);

    private:

        Task *task = nullptr;
        TestData test_data{};

        pair<TestResultsExtended, TestResultsExtended> results;

        unsigned int tests = test_data.tests_amount;

        void algorithm_results_csv_print();

        bool belong(const Point &point, const Square &square);

        void save_results(TestResultsExtended &test_results, TaskResults &task_results);

        void conclude_average(TestResultsExtended &test_results);
};