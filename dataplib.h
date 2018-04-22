/* 
 * File: dataplib.h
 * Copy: Copyright (c) 2018 Gregory C. Myers
 * BlazerID: gmyers
 * Vers: 2.0.0 04/11/2018 GCM - Presented Spring 2018
 * Vers: 1.0.0 04/11/2018 GCM - Original Coding
 * Desc: Header file for aggregating data functions using pointers
 */

typedef struct student_node {
    char first_name[10];
    char middle_initial[2];
    char last_name[10];
    char blazer_id[10];
    struct student_node *next_student_node;
} student_node_type; 

typedef struct course_node {
    char crn[6]; // 54321
    char department[4]; // EE
    char number[5]; // 361L
    char title[50];
    int hours;
    struct course_node *next_course_node;
} course_node_type; 

typedef struct course_student_node {
    char crn[6]; // 54321
    char blazer_id[10];
    struct course_student_node *next_course_student_node;
} course_student_node_type; 

// ## student ##
int import_students_node(char const filename[], student_node_type *head_node);
int display_students_node(student_node_type *head_node);
int examine_students_node(student_node_type *head_node );
int display_student_node(student_node_type *student_node );
int export_students_node(char const filename[], student_node_type const *head_node);

int add_student_node(student_node_type *head_node,  student_node_type *student_node);
int remove_student_node(student_node_type *head_node, student_node_type *student_node);

int isa_student_all_fields_node(student_node_type *head_node, student_node_type *student_node);
int isa_student_node(student_node_type *head_node, char blazer_id[]);

int get_student_all_fields_node(student_node_type *head_node, student_node_type *student_node);
int get_student_node(student_node_type *head_node, char blazer_id[], student_node_type *student_node);

int compare_student_node(student_node_type *first_student_node, student_node_type *second_student_node);
int copy_student_node(student_node_type *destination_node, student_node_type *source_node);

// ## course ##
int import_courses_node(char const filename[], course_node_type *head_node);
int display_courses_node(course_node_type *head_node);
int examine_courses_node(course_node_type *head_node );
int display_course_node(course_node_type *course_node );
int export_courses_node(char const filename[], course_node_type const *head_node);

int add_course_node(course_node_type *head_node,  course_node_type *course_node);
int remove_course_node(course_node_type *head_node, course_node_type *course_node);

int isa_course_all_fields_node(course_node_type *head_node, course_node_type *course_node);
int isa_course_node(course_node_type *head_node, char crn[]);

int get_course_all_fields_node(course_node_type *head_node, course_node_type *course_node);
int get_course_node(course_node_type *head_node, char crn[], course_node_type *course_node);

int compare_course_node(course_node_type *first_course_node, course_node_type *second_course_node);
int copy_course_node(course_node_type *destination_node, course_node_type *source_node);

// ## course_student

int import_courses_students_node(char const filename[], course_student_node_type *head_node);
int display_courses_students_node(course_student_node_type *head_node);
int examine_courses_students_node(course_student_node_type *head_node );
int display_course_student_node(course_student_node_type *course_student_node );
int export_courses_students_node(char const filename[], course_student_node_type const *head_node);

int add_course_student_node(course_student_node_type *head_node,  course_student_node_type *course_student_node);
int remove_course_student_node(course_student_node_type *head_node, course_student_node_type *course_student_node);

int isa_course_student_all_fields_node(course_student_node_type *head_node, course_student_node_type *course_student_node);
int isa_course_student_node(course_student_node_type *head_node, char crn[], char blazer_id[]);

int get_course_student_all_fields_node(course_student_node_type *head_node, course_student_node_type *course_student_node); // redundant in this case...
int get_course_student_node(course_student_node_type *head_node, char crn[], char blazer_id[], course_student_node_type *course_student_node);

int compare_course_student_node(course_student_node_type *first_course_student_node, course_student_node_type *second_course_student_node);
int copy_course_student_node(course_student_node_type *destination_node, course_student_node_type *source_node);

