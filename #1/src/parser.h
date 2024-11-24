#ifndef PARSER_H
#define PARSER_H

#include <argp.h>

typedef struct {
  bool is_from_stdin;
  size_t flag_counter;
  char count_flags[4];
  char* filename;
} Arguments;

/**
 * Updates the count_flags array in provided Arguments struct according to the given input key.
 * 
 * - To be used when parsing the CLI arguments along parse_opt function.
 * 
 * - The input key represents the code of an entered keyboard key.
 * 
 * - If the key is not recognized, the function does nothing and returns false.
 * 
 * @param args the Arguments struct to be updated
 * @param key the input key to be processed
 * @return true if the key has been recognized and processed, false otherwise.
 */
bool count_flag_setter(Arguments* args, int key);

/**
 * Parses the given input key and updates the Arguments struct accordingly.
 * 
 * - To be used along the parse_args function (from argp library).
 * 
 * - The input key represents the code of an entered keyboard key.
 * 
 * - If the key is not recognized, the function returns an error code (ARGP_ERR_UNKNOWN).
 * 
 * - If more than one positional argument is given, the function returns an error code (EX_USAGE).
 * 
 * - If no positional argument is given, the function sets the is_from_stdin field to true.
 * 
 * @param key the input key to be processed
 * @param arg the value associated to the input key to be processed
 * @param state the state struct of argp library
 * @return 0 if the key has been recognized and processed, an error code otherwise.
 */
error_t parse_opt(int key, char* arg, struct argp_state* state);

/**
 * Parses the given CLI arguments and updates the provided Arguments struct accordingly.
 * 
 * - This function relies on the argp_parse function from argp library.
 * 
 * @param argp the argp struct to be used for parsing
 * @param argc the number of CLI arguments
 * @param argv the array of CLI arguments
 * @param args the Arguments struct to be updated
 */
void parse_args(const struct argp*, int argc, char** argv, Arguments* args);

/**
 * Processes the given Arguments struct and returns the exit code of the program.
 * 
 * - To be used after argument parsing via parse_args.
 * 
 * @param args the Arguments struct to be processed
 * @return the exit code of the program (0 if everything went fine, 1 otherwise).
 */
int process_args(const Arguments* args);

#endif // PARSER_H
