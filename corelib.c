/* 
 * File: corelib.c
 * Copy: Copyright (c) 2018 Gregory C. Myers
 * BlazerID: gmyers
 * Vers: 2.0.0 04/11/2018 GCM - Presented Spring 2018
 * Vers: 1.0.0 04/11/2018 GCM - Original Coding
 * Desc: Code file for implementing corelib.h
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "corelib.h"
#include "dataplib.h"


int file_read( char file_name[], char contents[] ) {
    // consider using a different function signature
    // include a status
    // int file_read( char file_name[], char contents, int *count, int *status)
    char current;
    int count;
    FILE *input;
    
    count = 0;
    
    input = fopen( file_name, "r");
    // check for a NULL file pointer
    if (input != NULL) {
        // this checks to see if the file actually exist
        while (fscanf( input, "%c", &current ) != EOF ) {
            contents[ count ] = current;
            count++;        
        }
        contents[ count ] = '\0';
        count++;                            
    }    
    fclose( input );
    
    // could consider returning the length of contents
    return( count );    
}

int read_line( FILE *input, char line[] ) {
    char current;
    int end_of_file;
    int end_of_line;    
    int count;
    
    end_of_line = 0;
    end_of_file = 0;
    count = 0;
    
    do {
        if (fscanf( input, "%c", &current ) == EOF) {
            line[ count ] = '\0';
            end_of_line = 1;
            end_of_file = 1;            
        } else if (current == '\n') {                      
            line[ count ] = '\0';
            end_of_line = 1;
        } else {
            line[ count ] = current;
        }
        count++;        
    } while (end_of_line == 0);
    
    return( end_of_file );
}

int char_find( char contents[], int contents_length, char search, int locations[]) {
    // zero based indexing...
    // location of the starting point for each substring...
    int index;
    int count;
    
    index = 0; // technically redundant
    count = 0;
    
    // increment through our contents looking for matches...
    for (index = 0; index < contents_length; index++ ) {
        if (contents[ index ] == search) {
            locations[ count ] = index; // location of each match...
            count++;
        } else {
            // keep on looking...
        }
    }
    return( count ); /// return the number of matches (or in the function sig as a pointer);
}

int string_find( char contents[], char search[], int locations[]) {
    int contents_index;
    int search_index;
    int count;
    int found;
    
    count = 0;
    contents_index = 0;
    search_index = 0;
    
    while (contents[ contents_index ] != '\0') {
        found = 1;
        search_index = 0;
        while ((search[ search_index ] != '\0') && (found == 1)) {
            // printf("%c %c\n", contents[ contents_index ], search[ search_index ] );
            if ((contents[ contents_index + search_index ] == '\0') || (contents[ contents_index + search_index ] != search[ search_index ])) {
                found = 0;                
            } else {
                // keep looking...
                search_index++;
            }
        }
        if (found == 0) {
            contents_index = contents_index + 1;
        } else {
            locations[ count ] = contents_index;
            // if you wanted to allow duplicate substring matches, change the 
            // contents_index = contents_index + 1;
            // no need to skip characters
            contents_index = contents_index + search_index;
            count++;
        }            
    }
    return( count );
}

int string_split( char contents[], char delimiter, char chunks[][chunk_length]) {
    // assume that the user is passing us a string and not a char array
    // delimiter is a single character
    int contents_index;
    int chunks_index;
    int chunks_counter;
    
    contents_index = 0;
    chunks_index = 0;
    chunks_counter = 0;
    
    while ( contents[ contents_index ] != '\0' ) {
        // we are going to collect characters...
        // when are we going to collect characters? 
        //      when ed don't see a delimiter...
        // what happens when we see a delimiter?
        //      start a new chunk...
        if ( contents[ contents_index ] == delimiter ) {
            // we have found the delimiter... 
            // we skip it and start a new chunk
            chunks[ chunks_counter][ chunks_index ] = '\0';
            chunks_counter++;            
            contents_index++;            
            chunks_index = 0;
        } else {        
            // the current character we are looking at that does not match our delimiter
            chunks[ chunks_counter ][ chunks_index ] = contents[ contents_index ];
            contents_index++;
            chunks_index++;
        }
    }
    chunks[ chunks_counter][ chunks_index ] = '\0';
    // return number of chunks
    return( chunks_counter + 1 );
}

int string_compare( char const first[], char const second[], case_sensitivity_type sensitivity ) {
    int ReturnValue;
    int LettersMax;
    int LettersIndex;
    
    ReturnValue = 0; //  equal - no differences
    LettersIndex = 0; // start of at the lowest index   
    
    /* Upper case: (A-Z) --> (65-90)
     * Lower case: (a-z) --> (97-122)
     */
    
    /* check to see if a char falls within the range alphabetic characters
     * 
     * comparing two words....
     *  need to get the length of both words (for loop)
     *  use the end of string character --> use a while loop...
     * character by character comparison...
     * char1 is part of string1
     * char2 is part of string2
     *  if char1 < char2 --> string1 < string2
     *  if char1 > char2 --> string1 > string2
     *  if char1 == char2 --> string1 == string2 (if this is true for all char and
     *      they are the same length...
     */
    
    printf("Length of %s is %d\n", first, strlen(first));
    printf("Length of %s is %d\n", second, strlen(second));
    

    if ((strlen(first) == 0) & (strlen(second) == 0)) {
        ReturnValue = 0;
        // Multiple return statements in a single function can be done but is 
        // considered bad programming...
        // return( ReturnValue );
    } else if (strlen(first) == 0) {
        ReturnValue = -1;
    } else if (strlen(second) == 0) {
        ReturnValue = 1;
    } else {
        if (strlen(first) < strlen(second)) {
            LettersMax = strlen(second);
        } else {
            LettersMax = strlen(first);
        }
        
        // here is where we handle the case sensitivity...
        if (sensitivity == case_sensitive) {            
            while ((ReturnValue == 0) & (LettersIndex < LettersMax)) {
                if (first[LettersIndex] < second[LettersIndex] ) {
                    ReturnValue = -1;
                } else if (first[LettersIndex] > second[LettersIndex] ) {
                    ReturnValue = 1;
                } else {
                    LettersIndex++;
                }     
            }            
        } else if (sensitivity == case_insensitive) {
            while ((ReturnValue == 0) & (LettersIndex < LettersMax)) {
                /* Upper case: (A-Z) --> (65-90)
                 * Lower case: (a-z) --> (97-122)
                 */
                    
                // we now need to check the case of our letters...
                // first lower, second lower            
                // first upper, second lower
                // first lower, second upper
                // first upper, second upper                
                if (((first[LettersIndex] >= 65) & (first[LettersIndex] <=90)) & 
                        ((second[LettersIndex] >= 65) & (second[LettersIndex] <= 90))) {
                    if (first[LettersIndex] < second[LettersIndex] ) {
                        ReturnValue = -1;
                    } else if (first[LettersIndex] > second[LettersIndex] ) {
                        ReturnValue = 1;
                    } else {
                        LettersIndex++;
                    }                    
                } else if ((first[LettersIndex] >= 65) & (first[LettersIndex] <=90)) {
                    if ((first[LettersIndex] + 32) < second[LettersIndex] ) {
                        ReturnValue = -1;
                    } else if ((first[LettersIndex] + 32) > second[LettersIndex] ) {
                        ReturnValue = 1;
                    } else {
                        LettersIndex++;
                    }                                                            
                } else if ((second[LettersIndex] >= 65) & (second[LettersIndex] <= 90)) {
                    if (first[LettersIndex] < (second[LettersIndex] + 32) ) {
                        ReturnValue = -1;
                    } else if (first[LettersIndex] > (second[LettersIndex] + 32) ) {
                        ReturnValue = 1;
                    } else {
                        LettersIndex++;
                    }                                        
                } else {
                    if (first[LettersIndex] < second[LettersIndex] ) {
                        ReturnValue = -1;
                    } else if (first[LettersIndex] > second[LettersIndex] ) {
                        ReturnValue = 1;
                    } else {
                        LettersIndex++;
                    }                                                            
                }                        
            }            
        } else {
            // nothing to do here yet...
        }
                               
        // what does ReturnValue == 0 mean?  So far they are the same word...
        if ((ReturnValue == 0) & (strlen(first) > strlen(second))) {
            // words were identical up until the length...
            // first word is longer... therefore it comes after
            ReturnValue = 1;
        } else if ((ReturnValue == 0) & (strlen(first) < strlen(second))) {
            // the second word is longer...            
            ReturnValue = -1;
        } else if ((ReturnValue == 0) & (strlen(first) == strlen(second))) {
            // optional to check but encouraged.
        }        
    }    
    
    return( ReturnValue );   
}

int sort_char(char words[][char_count_max], case_sensitivity_type sensitivity, order_type order, int new_order[] ) {
    
}

int sort_double(double numbers[], order_type order, int new_order[] ) {
    
}

int sort_int(int numbers[], order_type order, int new_order[] ) {
    
}
