/* 
 * File: Class_26_Driver.c
 * Copy: Copyright (c) 2018 Gregory C. Myers
 * BlazerID: gmyers
 * Vers: 2.0.0 04/16/2018 GCM - Presented Spring 2018
 * Vers: 1.0.0 04/16/2018 GCM - Original Coding
 * Desc: Driver for testing concepts in Class_26_Outline.c 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "corelib.h"
#include "dataplib.h"



/* Function Prototypes */
int help();


/* Name: int main(int argc, char** argv)
 * Desc: Driver for testing functions.
 */
int main(int argc, char** argv) {
    


    int i;
    
    char blazer_id_input[20];
    char first_name_input[20];
    char middle_initial_input[20];
    char last_name_input[20];
    
    char crn_input[10];
    char department_input[5];
    char number_input[10];
    char title_input[50];
    int hours_input;
    
    student_node_type students_head_node;

    course_node_type courses_head_node;
    
    course_student_node_type courses_students_head_node;
   
    
    import_students_node("Students.csv", &students_head_node);
    import_courses_node("Courses.csv", &courses_head_node);
    import_courses_students_node("Courses_Students.csv", &courses_students_head_node);



    

    for (i = 0; i < argc; i++) {
        printf("\t%d: %s\n", i, argv[i]);        
    } 
    

    if (argc < 21) {
        // help implicitly called.
        help();
    } else {
        
        if(strcmp(argv[1],"/h") == 0 ){
            help();
            
        } else if(strcmp(argv[1], "/students") == 0) {
            //student mode
            
            if((strcmp(argv[2],"/display") == 0) && (argc == 4) ){
               strncpy(blazer_id_input,argv[3],strlen(argv[3]));
               printf("%s\n", blazer_id_input);
               printf("%s\n", argv[3]);
                //blazer_id_input = argv[3];
                // display a particular student
                // need to search through all students to see if the studet->blazer_id matches the input blazer id
               
               
            } else if((strcmp(argv[2],"/display_all") == 0) && (argc == 3) ){
                // display all students
               display_students_node(&students_head_node);
               
            } else if((strcmp(argv[2],"/isa") == 0) && (argc == 4) ){
                strcpy(blazer_id_input, argv[3]);
                // check to see if student is in student list
                // if yes return "true"
                // if no return "false"
               
            } else if((strcmp(argv[2],"/add") == 0) && (argc == 7) ){
                strcpy( first_name_input, argv[3]);
                strcpy( middle_initial_input, argv[4]);
                strcpy( last_name_input, argv[5]);
                strcpy(blazer_id_input, argv[6]);
              
                // check to see if student is in student list
                // if yes return error that says they are on the list
                // if no add them to the list
               
            } else if((strcmp(argv[2],"/remove") == 0) && (argc == 4) ){\
                strcpy(blazer_id_input, argv[3]);
                // check to see if student is in student list
                // if yes return remove them
                // if no, send error that theyr not on the list
               
            } else {
                help();
            }
            
        } else if(strcmp(argv[1], "/courses") == 0) {
            //course mode
            
            if((strcmp(argv[2],"/display") == 0) && (argc == 4) ){
                strcpy(crn_input, argv[3]);
                // display a particular student
                // need to search through all students to see if the studet->blazer_id matches the input blazer id
                
            } else if((strcmp(argv[2],"/display_all") == 0) && (argc == 3) ){
                // display all students
                display_courses_node(&courses_head_node);
               
            } else if((strcmp(argv[2],"/isa") == 0) && (argc == 4) ){
                strcpy(crn_input, argv[3]);
                // check to see if student is in student list
                // if yes return "true"
                // if no return "false"
               
            } else if((strcmp(argv[2],"/add") == 0) && (argc == 7 )){
                strcpy(crn_input, argv[3]);
                strcpy(department_input, argv[4]);
                strcpy(number_input, argv[5]);
                strcpy(title_input, argv[6]);
                strtod(argv[7],NULL);
                
                // check to see if student is in student list
                // if yes return error that says they are on the list
                // if no add them to the list
               
            } else if((strcmp(argv[2],"/remove") == 0) && (argc == 4) ){
                strcpy(crn_input, argv[3]);
                // check to see if student is in student list
                // if yes return remove them
                // if no, send error that theyr not on the list
               
            }else {
                help();
            } 
            
        } else if(strcmp(argv[1], "/course_student") == 0) {
            //course_student mode
            
            if((strcmp(argv[2],"/display") == 0) && (argc == 5) ){
                strcpy(crn_input, argv[3]);
                strcpy(blazer_id_input, argv[4]);
                // display a particular student
                // need to search through all students to see if the studet->blazer_id matches the input blazer id
                
            } else if((strcmp(argv[2],"/display_all") == 0) && (argc == 3) ){
                // display all students
               
            } else if((strcmp(argv[2],"/isa") == 0) && (argc == 5) ){
                strcpy(crn_input, argv[3]);
                strcpy(blazer_id_input, argv[4]);
                // check to see if student is in student list
                // if yes return "true"
                // if no return "false"
               
            } else if((strcmp(argv[2],"/add") == 0) && (argc == 5) ){
                strcpy(crn_input, argv[3]);
                strcpy(blazer_id_input, argv[4]);
                // check to see if student is in student list
                // if yes return error that says they are on the list
                // if no add them to the list
               
            } else if((strcmp(argv[1],"/remove") == 0) && (argc == 4) ){
                strcpy(crn_input, argv[2]);
                strcpy(blazer_id_input, argv[3]);
                // check to see if student is in student list
                // if yes return remove them
                // if no, send error that theyr not on the list
               
            }else {
                help();
            }  
        } 
        
    }
 
    return (EXIT_SUCCESS);
}

int help(void){
    printf("Please Enter a Valid Command\n");
    
    return(EXIT_SUCCESS);
}



