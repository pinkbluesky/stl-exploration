#include <iostream>
#include <stack>
#include <fstream>

// http://www.usaco.org/index.php?page=viewproblem2&cpid=922

std::ofstream fout("2.out");
std::ifstream fin("2.in");

int main()
{
    int n;
    std::stack<int> arr;

    fin >> n;

    // retrieve input
    for (int i = 0; i < n; i++)
    {
        int x;
        fin >> x;
        arr.push(x);
    }

    std::stack<int> dishes;
    // reverse stack
    while (arr.size())
    {
        int temp = arr.top();
        arr.pop();

        dishes.push(temp);
    }

    /*
    // new implementation
    int substack_cur = dishes.top();
    int substack_count = 0;

    int result = substack_cur;
    int result_count = 0;

    int max_dish = 0;
    int min_dish = 0;

    // for each dish
    for (int i = 0; i < n; i++)
    {
        int dish = dishes.top();

        // check if greater than top dish
        if (dish > top_dish)
        {
            top_dish = dish;
            substack_count++;
        }
        else
        {

        }
    }

    */

    // store the top dishes of every stack
    int stack_count = 0;
    int top_dishes[100000];
    std::fill(top_dishes, top_dishes + 100000, 0);
    // store the bottom of the last stack for comparison purposes
    int bottom = 0;

    // store the longest continuous stacking success
    int dish_count = 0;
    int max_count = 0;
    int cur_stack = dishes.top();

    int result = -1;

    for (int i = 0; i < n; i++)
    {
        // place plate in appropriate stack and update top plate values accordingly
        int x = dishes.top();


        int td_i = 1;

        bool existing_stack = false;

        // iterate through each top stack (except for the last one)
        while (td_i <= stack_count && (td_i == stack_count || top_dishes[td_i]))
        {
            // or, choose the stack where top dish is less, but next stack has top dish greater than

            if (x > top_dishes[td_i - 1] && (td_i == stack_count || x < top_dishes[td_i]))
            {
                // update top dish with newly stacked dish
                top_dishes[td_i - 1] = x;
                dish_count++;
                existing_stack = true;
                break;
            }

            td_i++;
        }

        // if no stack was found
        if (!existing_stack)
        {
            // make new stack if dish is less than all top stacks
            if (stack_count == 0 || x < bottom)
            {
                // new stack
                top_dishes[stack_count] = x;
                stack_count++;
                dish_count++;

                bottom = x;
            }
            // else, impossible stacking situation
            else
            {
                // is it our longest stack yet?
                if (dish_count > max_count)
                {
                    max_count = dish_count;
                    result = cur_stack;
                }

                // reset dish count, reset stacks to 0, reset stack count
                dish_count = 0;
                std::fill(top_dishes, top_dishes + stack_count, 0);
                stack_count = 0;

                cur_stack = x;
            }
        }

        dishes.pop();
    }

    // is it our longest stack yet?
    if (dish_count > max_count)
    {
        max_count = dish_count;
        result = cur_stack;
    }

    fout << result << "\n";
}
