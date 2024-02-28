#include <iostream>
#include <fstream>
#include <cstring>
#include "Test.h"


int main()
{

    char word[15];
    Test test(TestData{10, 100, 10000});
    cout<<"Hello user!\n Please select the test:\n For simple test write <simple>, \n For random test write <random>,\n For increase test write <increase>,\n"<<endl;
    cin >> word;



    if(!strcmp(word, "random"))
    {
        test.random_test_algorithm();
        test.algorithm_results_console_print();
    }
    else if(!strcmp(word, "simple"))
    {
        test.simple_test();
        test.algorithm_results_console_print();
    }
    else if(!strcmp(word, "increase"))
        test.increase_random_test(100000, 10000);
    else
        cout << "ERROR!" << endl;

    return 0;
}


