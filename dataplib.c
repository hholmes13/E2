/* 
 * File: dataplib.c
 * Copy: Copyright (c) 2018 Gregory C. Myers
 * BlazerID: gmyers
 * Vers: 2.0.0 04/11/2018 GCM - Presented Spring 2018
 * Vers: 1.0.0 04/11/2018 GCM - Original Coding
 * Desc: Code file for implementing dataplib.h
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dataplib.h"
#include "corelib.h"


//############################################################################
// STUDENT
//############################################################################

int import_students_node(char const filename[], student_node_type *head_node) {
    FILE *input;
    int Results;
    char line[line_length];
    char chunks[ chunk_count_max ][ chunk_length ];
    student_node_type *current_node;
    // student_node_type *new_node;
    int is_head_node;
    
    
    is_head_node = 1;
    //input = fopen("Students.csv", "r");
    input = fopen(filename, "r");    
    while (read_line( input, line) == 0) {
        // printf("%s\n", line);
        Results = string_split( line, ',', chunks );
        
        if (Results == 4) {
            if (is_head_node == 1) {
                strcpy(head_node->first_name, chunks[ 0 ]);
                strcpy(head_node->middle_initial, chunks[ 1 ]);
                strcpy(head_node->last_name, chunks[ 2 ]);
                strcpy(head_node->blazer_id, chunks[ 3 ]);                
                head_node->next_student_node = NULL;
                
                current_node = head_node;
                is_head_node = 0; // change from head_node
            } else {               
                current_node->next_student_node = (student_node_type *)malloc(sizeof( student_node_type));
                                                
                strcpy(current_node->next_student_node->first_name, chunks[ 0 ]);
                strcpy(current_node->next_student_node->middle_initial, chunks[ 1 ]);
                strcpy(current_node->next_student_node->last_name, chunks[ 2 ]);
                strcpy(current_node->next_student_node->blazer_id, chunks[ 3 ]);

                current_node->next_student_node->next_student_node = NULL;
                
                
                // current_node->next_student_node = new_node->first_name;
                current_node = current_node->next_student_node;                
            }
        }
    }
return( 0 );
}

int display_students_node(student_node_type *head_node) {
    // display all of the nodes in a linked list...
    // we have no idea how many we have...
    // continue to look/loop though out linked list until we have a NULL pointer
    // to  the next student...
    student_node_type *current_node;
    
    current_node = head_node;
    
    while (current_node != NULL) {
       
        display_student_node( current_node );
        current_node = current_node->next_student_node; // address of the next node...
    }        
    return( 0 );
}

int examine_students_node(student_node_type *head_node ) {
    student_node_type *current_node;

    current_node = head_node;
    
    printf("Description                                 Value\n");
    printf("===============================================================\n");
    printf("Address of head_node                            %p\n", head_node);    
    printf("head_node.first_name                            %s\n", head_node->first_name);
    printf("head_node.middle_initial                        %s\n", head_node->middle_initial);
    printf("head_node.last_name                             %s\n", head_node->last_name);
    printf("head_node.blazer_id                             %s\n", head_node->blazer_id);
    
    printf("Address of head_node.first_name                 %p\n", &(head_node->first_name));
    printf("Address of head_node.middle_initial             %p\n", &(head_node->middle_initial));
    printf("Address of head_node.last_name                  %p\n", &(head_node->last_name));
    printf("Address of head_node.blazer_id                  %p\n", &(head_node->blazer_id));
    printf("Address of head_node.next_student_node          %p\n", head_node->next_student_node);
    printf("===============================================================\n");
    
    while (current_node != NULL) {
        printf("Address of current_node                         %p\n", current_node);    
        printf("current_node.first_name                         %s\n", current_node->first_name);
        printf("current_node.middle_initial                     %s\n", current_node->middle_initial);
        printf("current_node.last_name                          %s\n", current_node->last_name);
        printf("current_node.blazer_id                          %s\n", current_node->blazer_id);        

        printf("Address of current_node.first_name              %p\n", &(current_node->first_name));
        printf("Address of current_node.middle_initial          %p\n", &(current_node->middle_initial));
        printf("Address of current_node.last_name               %p\n", &(current_node->last_name));
        printf("Address of current_node.blazer_id               %p\n", &(current_node->blazer_id));
        printf("Address of current_node.next_student_node       %p\n", current_node->next_student_node);
        
        current_node = current_node->next_student_node;
    }
    printf("===============================================================\n");
    return( 0 );
}

int display_student_node(student_node_type *student_node ) {
    printf( "First Name: %s\n", student_node->first_name );
    printf( "Middle Initial: %s\n", student_node->middle_initial );
    printf( "Last Name: %s\n", student_node->last_name );
    printf( "BlazerID: %s\n", student_node->blazer_id );
    printf( "Pointer to next student: %p\n", student_node->next_student_node ); // would remove this later...
}

int export_students_node(char const filename[], student_node_type const *head_node) {
    // linked list and send it to a file...
    student_node_type *current_node;
    FILE *output;
    
    output = fopen( filename, "w");
    
    current_node = head_node; 
    while (current_node != NULL) {
        // print each student to the file...
        fprintf( output, "%s,%s%,%s,%s\n", current_node->first_name, current_node->middle_initial, 
                current_node->last_name, current_node->blazer_id );
        
        current_node = current_node->next_student_node; // looks at the next student...
    }
    
    fclose( output );
    return ( 0 ); // should reconsider this...    
}

int add_student_node(student_node_type *head_node,  student_node_type *student_node) {
    // find the last node...
    student_node_type *current_node;
    // decide whether to use the student_node as it is... or
    //  make a copy of it to add to your list...
    
    if (head_node == NULL) {
        // malloc returns a void pointer than needs be cast to right pointer type...
        head_node = (student_node_type *)malloc(sizeof( student_node_type));        
        // create a copy student function...
        copy_student_node( head_node, student_node );
    } else {    
        current_node = head_node; // assume that the head_node is not null
        while ( current_node->next_student_node != NULL ) {        
            current_node = current_node->next_student_node;
        }
        current_node->next_student_node = (student_node_type *)malloc(sizeof( student_node_type));
        copy_student_node( current_node->next_student_node, student_node );
    }
    
    return( 0 ); // need to rethink... 
}

int remove_student_node(student_node_type *head_node, student_node_type *student_node) {
    
}

int isa_student_all_fields_node(student_node_type *head_node, student_node_type *student_node) {
    
}

int isa_student_node(student_node_type *head_node, char blazer_id[]) {
    
}

int get_student_all_fields_node(student_node_type *head_node, student_node_type *student_node) {
    
}

int get_student_node(student_node_type *head_node, char blazer_id[], student_node_type *student_node) {
    
}

int compare_student_node(student_node_type *first_student_node, student_node_type *second_student_node) {
    
}

int copy_student_node(student_node_type *destination_node, student_node_type *source_node) {
    strcpy( destination_node->first_name, source_node->first_name );
    strcpy( destination_node->middle_initial, source_node->middle_initial );
    strcpy( destination_node->last_name, source_node->last_name );
    strcpy( destination_node->blazer_id, source_node->blazer_id );
    
    destination_node->next_student_node = source_node->next_student_node;
}



//############################################################################
// COURSE
//############################################################################

int import_courses_node(char const filename[], course_node_type *head_node) {
    FILE *input;
    int Results;
    char line[0];
    char chunks[ chunk_count_max ][ chunk_length ];
    course_node_type *current_node;
    // course_node_type *new_node;
    int is_head_node;
    
    
    is_head_node = 1;
    
    input = fopen(filename, "r");    
    while (read_line( input, line) == 0) {
        // printf("%s\n", line);
        Results = string_split( line, ',', chunks );
        
        if (Results == 5) {
            if (is_head_node == 1) {
                strcpy(head_node->crn, chunks[ 0 ]);
                strcpy(head_node->department, chunks[ 1 ]);
                strcpy(head_node->number, chunks[ 2 ]);
                strcpy(head_node->title, chunks[ 3 ]);
                strcpy(head_node->hours, chunks[ 4 ]);
                head_node->next_course_node = NULL;
                
                current_node = head_node;
                is_head_node = 0; // change from head_node
            } else {               
                current_node->next_course_node = (course_node_type *)malloc(sizeof( course_node_type));
                                                
                strcpy(current_node->next_course_node->crn, chunks[ 0 ]);
                strcpy(current_node->next_course_node->department, chunks[ 1 ]);
                strcpy(current_node->next_course_node->number, chunks[ 2 ]);
                strcpy(current_node->next_course_node->title , chunks[ 3 ]);
                strcpy(current_node->next_course_node->hours , chunks[ 4 ]);
                
                current_node->next_course_node->next_course_node = NULL;
                
                
                current_node = current_node->next_course_node;                
            }
        }
    }
return( 0 );
}

int display_courses_node(course_node_type *head_node){
    // display all of the nodes in a linked list...
    // we have no idea how many we have...
    // continue to look/loop though out linked list until we have a NULL pointer
    // to  the next student...
    course_node_type *current_node;
    
    current_node = head_node;
    
    while (current_node != NULL) {
        // some code goes here to display a student...
        display_course_node( current_node );
        current_node = current_node->next_course_node; // address of the next node...
    }        
    return( 0 );
}

int display_course_node(course_node_type *course_node ){
    printf( "CRN: %s\n", course_node->crn );
    printf( "Department: %s\n", course_node->department );
    printf( "Course Number: %s\n", course_node->number);
    printf( "Title: %s\n", course_node->title );
    printf( "Hours: %d\n", course_node->hours );
}

int export_courses_node(char const filename[], course_node_type const *head_node){
    // linked list and send it to a file...
    course_node_type *current_node;
    FILE *output;
    
    output = fopen( filename, "w");
    
    current_node = head_node; 
    while (current_node != NULL) {
        // print each course to the file...
        fprintf( output, "%s,%s%,%s,%d\n", current_node->crn, current_node->department, 
                current_node->number, current_node->title, current_node->hours );
        
        current_node = current_node->next_course_node; // looks at the next student...
    }
    
    fclose( output );
    return ( 0 ); // should reconsider this...  
}

int add_course_node(course_node_type *head_node,  course_node_type *course_node){
    // find the last node...
    course_node_type *current_node;
    // decide whether to use the student_node as it is... or
    //  make a copy of it to add to your list...
    
    if (head_node == NULL) {
        // malloc returns a void pointer than needs be cast to right pointer type...
        head_node = (course_node_type *)malloc(sizeof( course_node_type));        
        // create a copy student function...
        copy_course_node( head_node, course_node );
    } else {    
        current_node = head_node; // assume that the head_node is not null
        while ( current_node->next_course_node != NULL ) {        
            current_node = current_node->next_course_node;
        }
        current_node->next_course_node = (course_node_type *)malloc(sizeof(course_node_type));
        copy_course_node( current_node->next_course_node, course_node );
    }
    
    return( 0 ); // need to rethink... 
}

int remove_course_node(course_node_type *head_node, course_node_type *course_node){
    
}

int isa_course_all_fields_node(course_node_type *head_node, course_node_type *course_node){
    
}

int isa_course_node(course_node_type *head_node, char crn[]){
    
}

int get_course_all_fields_node(course_node_type *head_node, course_node_type *course_node){
    
}

int get_course_node(course_node_type *head_node, char crn[], course_node_type *course_node){
    
}

int compare_course_node(course_node_type *first_course_node, course_node_type *second_course_node){
    
}

int copy_course_node(course_node_type *destination_node, course_node_type *source_node){
    strcpy( destination_node->crn, source_node->crn );
    strcpy( destination_node->department, source_node->department );
    strcpy( destination_node->number, source_node->number );
    strcpy( destination_node->title, source_node->title );
    destination_node->hours = source_node->hours;
    
    destination_node->next_course_node = source_node->next_course_node;
}



//############################################################################
// COURSE_STUDENT
//############################################################################

int import_courses_students_node(char const filename[], course_student_node_type *head_node){
     FILE *input;
    int Results;
    char line[0];
    char chunks[ chunk_count_max ][ chunk_length ];
    course_student_node_type *current_node;
    int is_head_node;
    
    
    is_head_node = 1;
    
    input = fopen(filename, "r");    
    while (read_line( input, line) == 0) {
        // printf("%s\n", line);
        Results = string_split( line, ',', chunks );
        
        if (Results == 2) {
            if (is_head_node == 1) {
                strcpy(head_node->crn, chunks[ 0 ]);
                strcpy(head_node->blazer_id, chunks[ 1 ]);
                
                head_node->next_course_student_node = NULL;
                
                current_node = head_node;
                is_head_node = 0; // change from head_node
            } else {               
                current_node->next_course_student_node = (course_student_node_type *)malloc(sizeof( course_student_node_type));
                                                
                strcpy(current_node->next_course_student_node->crn, chunks[ 0 ]);
                strcpy(current_node->next_course_student_node->blazer_id, chunks[ 1 ]);
                current_node->next_course_student_node->next_course_student_node = NULL;
                
                
                current_node = current_node->next_course_student_node;                
            }
        }
    }
}

int display_courses_students_node(course_student_node_type *head_node){
    // display all of the nodes in a linked list...
    // we have no idea how many we have...
    // continue to look/loop though out linked list until we have a NULL pointer
    // to  the next student...
    course_student_node_type *current_node;
    
    current_node = head_node;
    
    while (current_node != NULL) {
        // some code goes here to display a student...
        display_course_student_node( current_node );
        current_node = current_node->next_course_student_node; // address of the next node...
    }        
    return( 0 );
}

int examine_courses_students_node(course_student_node_type *head_node ){
    
}

int display_course_student_node(course_student_node_type *course_student_node ){
    printf( "CRN: %s\n", course_student_node->crn );
    printf( "BlazerID: %s\n", course_student_node->blazer_id );
}

int export_courses_students_node(char const filename[], course_student_node_type const *head_node){
     // linked list and send it to a file...
    course_student_node_type *current_node;
    FILE *output;
    
    output = fopen( filename, "w");
    
    current_node = head_node; 
    while (current_node != NULL) {
        // print each course to the file...
        fprintf( output, "%s,%s%\n", current_node->crn, current_node->blazer_id);
        
        current_node = current_node->next_course_student_node; // looks at the next student...
    }
    
    fclose( output );
    return ( 0 ); // should reconsider this... 
}

int add_course_student_node(course_student_node_type *head_node,  course_student_node_type *course_student_node){
    // find the last node...
    course_student_node_type *current_node;
    // decide whether to use the student_node as it is... or
    //  make a copy of it to add to your list...
    
    if (head_node == NULL) {
        // malloc returns a void pointer than needs be cast to right pointer type...
        head_node = (course_student_node_type *)malloc(sizeof( course_student_node_type));        
        // create a copy student function...
        copy_course_student_node( head_node, course_student_node );
    } else {    
        current_node = head_node; // assume that the head_node is not null
        while ( current_node->next_course_student_node != NULL ) {        
            current_node = current_node->next_course_student_node;
        }
        current_node->next_course_student_node = (course_student_node_type *)malloc(sizeof(course_student_node_type));
        copy_course_student_node( current_node->next_course_student_node, course_student_node );
    }
    
    return( 0 ); // need to rethink... 
}

int remove_course_student_node(course_student_node_type *head_node, course_student_node_type *course_student_node){
    
}

int isa_course_student_all_fields_node(course_student_node_type *head_node, course_student_node_type *course_student_node){
    
}

int isa_course_student_node(course_student_node_type *head_node, char crn[], char blazer_id[]){
    
}

int get_course_student_all_fields_node(course_student_node_type *head_node, course_student_node_type *course_student_node){ // redundant in this case.
    
}

int get_course_student_node(course_student_node_type *head_node, char crn[], char blazer_id[], course_student_node_type *course_student_node){
    
}

int compare_course_student_node(course_student_node_type *first_course_student_node, course_student_node_type *second_course_student_node){
    
}

int copy_course_student_node(course_student_node_type *destination_node, course_student_node_type *source_node){
    
}
