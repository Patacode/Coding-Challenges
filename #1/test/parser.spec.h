#ifndef PARSER_SPEC_H
#define PARSER_SPEC_H

// count_flag_setter()
void test_count_flag_setter_valid_key_l(void);
void test_count_flag_setter_valid_key_w(void);
void test_count_flag_setter_valid_key_m(void);
void test_count_flag_setter_valid_key_c(void);
void test_count_flag_setter_multiple_valid_keys(void);
void test_count_flag_setter_invalid_key(void);
void test_count_flag_setter_valid_key_with_flag_counter_at_1(void);

// parse_opt()
void test_parse_opt_valid_key(void);
void test_parse_opt_valid_key_with_one_positional_argument(void);
void test_parse_opt_valid_key_with_more_than_one_positional_argument(void);
void test_parse_opt_valid_key_with_no_positional_argument(void);
void test_parse_opt_invalid_key(void);

// parse_args()
void test_parse_args_valid_arguments_with_no_flag(void);

// process_args()
void test_process_args_valid_arguments_with_multiple_flags(void);
void test_process_args_valid_arguments_with_content_from_stdin(void);
void test_process_args_valid_arguments_with_content_from_file(void);
void test_process_args_valid_arguments_with_inexistent_file(void);

#endif // PARSER_SPEC_H
