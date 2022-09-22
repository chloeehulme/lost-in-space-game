#ifndef TERMINAL_USER_INPUT
#define TERMINAL_USER_INPUT

#include <string>
using std::string;


/**
 * Prompts the user for input and reads the text the user enters
 * at the Terminal. This will read in a line of text and return this
 * as a string.
 * 
 * @param prompt   The message displayed to the user
 * @returns        The text the user enters
 */
string read_string(string prompt);

/**
 * Prompts the user for input and reads the text the user enters
 * at the Terminal. This will read in a line of text and return this
 * as an integer.
 * 
 * @param prompt   The message displayed to the user
 * @returns        The text the user enters
 */
int read_integer(string prompt);

/**
 * Prompts the user for input and reads the text the user enters
 * at the Terminal. This will read in a line of text and return this
 * as an double.
 * 
 * @param prompt   The message displayed to the user
 * @returns        The text the user enters
 */
double read_double(string prompt);

/**
 * Prompts the user for input within a range and reads the text the user enters
 * at the Terminal. This will read in a line of text and return this
 * as an integer if within correct range.
 * 
 * @param prompt   The message displayed to the user
 * @returns        The text the user enters
 */
int read_integer(string prompt, int min, int max);

/**
 * Prompts the user for input within a range and reads the text the user enters
 * at the Terminal. This will read in a line of text and return this
 * as a double if within correct range.
 * 
 * @param prompt   The message displayed to the user
 * @returns        The text the user enters
 */
double read_double(string prompt, double min, double max);

/**
 * Prompts the user for input and reads the text the user enters
 * at the Terminal. This will read in a line of text and return this
 * as a boolean value.
 * 
 * @param prompt   The message displayed to the user
 * @returns        The text the user enters
 */
bool read_boolean(string prompt);

#endif