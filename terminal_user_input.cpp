#include "splashkit.h"
#include <string>

using namespace std;

string read_string(string prompt)
{
    string result;
    write(prompt);
    result = read_line();
    return result;
}

int read_integer(string prompt)
{
    string line;
    line = read_string(prompt); 

    while (not is_integer(line))
    {
        write_line("Error: please enter a whole number");
        line = read_string(prompt);
    }

    return convert_to_integer(line);
}

double read_double(string prompt)
{
    string line;
    line = read_string(prompt); 

    while (not is_number(line))
    {
        write_line("Error: please enter a valid number");
        line = read_string(prompt);
    }
    return convert_to_double(line);
}

int read_integer(string prompt, int min, int max)
{
    int result;
    
    result = read_integer(prompt);

    while (result < min or result > max)
    {
        write_line("Error: please enter a whole number between " + to_string(min) + " and " + to_string(max));
        result = read_integer(prompt);
    }

    return result;
}

double read_double(string prompt, double min, double max)
{
    double result;
    
    result = read_double(prompt);

    while (result < min or result > max)
    {
        write_line("Error: please enter a number between " + to_string(min) + " and " + to_string(max));
        result = read_double(prompt);
    }

    return result;
}

bool read_boolean(string prompt)
{
    string line;
    line = read_string(prompt); 
    line = trim(to_lowercase(line));

    while (line != "yes" and line != "y" and line != "no" and line != "n")
    {
        write_line("Error: please enter a valid response");
        line = read_string(prompt); 
        line = trim(to_lowercase(line));
    }
       
    if (line == "yes" or line == "y")
    {
        return true;
    }
    else if (line == "no" or line == "n")
    {
        return false;
    }

    return 0;
}