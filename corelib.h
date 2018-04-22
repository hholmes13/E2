/* 
 * File: coreib.h
 * Copy: Copyright (c) 2018 Gregory C. Myers
 * BlazerID: gmyers
 * Vers: 2.0.0 04/11/2018 GCM - Presented Spring 2018
 * Vers: 1.0.0 04/11/2018 GCM - Original Coding
 * Desc: Header file for aggregating core functions 
 */

#if !defined corelib_defined

#define char_count_max 20
#define chunk_count_max 20
#define chunk_length 1000
#define line_length 1000

typedef enum 
    { ascending, descending }
order_type;

typedef enum
    { case_sensitive, case_insensitive }
case_sensitivity_type;

int file_read( char file_name[], char contents[] );
int read_line( FILE *input, char line[] );
int char_find( char contents[], int contents_length, char search, int locations[]);
int string_find( char contents[], char search[], int locations[]);
int string_split( char contents[], char delimiter, char chunks[][chunk_length]);

int string_compare( char const first[], char const second[], case_sensitivity_type sensitivity );

int sort_char(char words[][char_count_max], case_sensitivity_type sensitivity, order_type order, int new_order[] );
int sort_double(double numbers[], order_type order, int new_order[] );
int sort_int(int numbers[], order_type order, int new_order[] );

#define corelib_defined

#endif