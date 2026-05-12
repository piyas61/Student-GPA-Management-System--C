#include<stdio.h>
#include<stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100
#define MAX_SUBJECTS 50


// ================= STRUCT =================
struct Student {
    int id;
    char name[50];
    int subjectCount;
    float marks[MAX_SUBJECTS];
    int credits[MAX_SUBJECTS];
    float gpa;
};

//====================GLOBAL VARIABLES====================
struct Student students [MAX_STUDENTS];
int count =0;


// ================= FUNCTION DECLARATIONS =================
int showMenu();
float inputSubjects(struct Student *s);
float calculateGradePoint(float marks);
float calculateGPA(float totalPoints, int totalCredits);
int validateMarks(float marks);

void addStudent();
void viewStudent();
void searchStudent();
void updateStudent();
void deleteStudent();
void recalculateGPA();

void saveStudent();
void loadStudent();

void exitProgram();


//==================MAIN FUNCTION==================

int  main (){
    int choice;

loadStudent();// load file data first

     while(1){
      choice = showMenu();


        switch (choice){
            case 1: addStudent();
            break;
            case 2: viewStudent();
            break;
            case 3: searchStudent();
            break;
            case 4: updateStudent();
            break;
            case 5: deleteStudent();
            break;
            case 6: recalculateGPA();
            break;
            case 7: exitProgram(); 
            break;
            

            
            default: printf("invalid choice! try again\n");
            
        }
     }
     
}

// ================= SHOWMENU =================
// Displays the main menu and returns the user's choice


int showMenu(){
    int choice;

     printf("\n===== GradeTrack System =====\n");
    printf("1. Add New Record\n");
    printf("2. View All Record\n");
    printf("3. Search Record\n");
    printf("4. Update Existing Record\n");
    printf("5. Delete Record\n");
    printf("6. perform Recalculation\n");
    printf("7. Exit Program\n");
   
   
    printf("Enter your choice:");

     if(scanf("%d", &choice) != 1){
       
        while(getchar() != '\n');   // clear buffer
        return 0;
    }

  
    return choice;
}


// ================= FUNCTION DEFINITIONS =================



//==================== ADD STUDENT====================
// Adds a new student record, calculates GPA, and saves to file


void addStudent() {
    struct Student s;


    printf("Enter ID: ");
    while (scanf("%d", &s.id) != 1 || s.id <= 0) {
        printf("Invalid input! Enter a positive integer: ");
        // clear invalid characters from input buffer
        while (getchar() != '\n');
    }
    
   
printf("Enter Name: ");
while (1) {
    scanf(" %[^\n]", s.name);

    if (strlen(s.name) == 0) {
        printf("Name cannot be empty. Enter again: ");
    } else {
        break;
    }
}


    s.gpa = inputSubjects(&s);

    if (count < MAX_STUDENTS) {
    students[count++] = s;
} else {
    printf("Storage full!\n");
}

      saveStudent();
    printf("Student added successfully!\n");
}


/*====================INPUT SUBJECTS====================

 Collects marks and credits for subjects, validates input, and calculates GPA*/


float inputSubjects(struct Student *s) {
    
    float totalPoints = 0;
int totalCredits = 0;

    printf("Number of subjects: ");
while (scanf("%d", &s->subjectCount) != 1 ||
       s->subjectCount <= 0 ||
       s->subjectCount > MAX_SUBJECTS) {

    printf("Invalid! Enter 1 to %d subjects: ", MAX_SUBJECTS);
    while (getchar() != '\n');
}

    //  Zero subject 
if (s->subjectCount <= 0) {
    printf("Error: Must have at least one subject!\n");
    return 0;  //  stop input
}

    for(int i = 0; i < s->subjectCount; i++) {
        printf("Marks for subject %d: ", i+1);
        scanf("%f", &s->marks[i]);

        while (!validateMarks(s->marks[i])){

            printf("Re - enter marks:");
            scanf("%f",&s->marks[i]);
                    }

        printf("Credits (1-4): ");
while (scanf("%d", &s->credits[i]) != 1 ||
       s->credits[i] <= 0 ||
       s->credits[i] > 4) {

    printf("Invalid credit! Enter 1-4: ");
    while (getchar() != '\n');
}

// Multiply grade point by credits to get weighted points
        totalPoints += calculateGradePoint(s->marks[i])*s->credits[i];
        totalCredits+= s->credits[i];
    }

    return calculateGPA(totalPoints,totalCredits);
}

//====================VALID MARKS====================

int validateMarks(float marks) {
    if (marks < 0 || marks > 100) {
        printf("Invalid marks! Please enter marks between 0 and 100.\n");
        return 0;
    }
    return 1;
}

//==================== GRADE POINT====================


float calculateGradePoint(float marks) {
    if(marks >= 80) return 4.0;
    else if(marks >= 70) return 3.5;
    else if(marks >= 60) return 3.0;
    else if(marks >= 50) return 2.5;
    else if(marks >= 40) return 2.0;
    else return 0.0;
}


/* ====================GPA CALCULATION====================
 Calculates weighted GPA using grade points and credits*/

float calculateGPA(float totalPoints, int totalCredits) {
    if (totalCredits == 0)
    return 0;
    return totalPoints / totalCredits;
}



/*====================recalculation====================
Allows user to re-enter subjects for an existing student and updates GPA*/

void recalculateGPA(){
    int id,found = 0;
    printf("Enter student Id to recalculate GPA:");
    scanf("%d",&id);

    for(int i = 0; i< count;i++){
       if(students[i].id == id){
          printf("Re-enter subjects and marks for %s:\n",students[i].name);
          students[i].gpa = inputSubjects(&students[i]);
          saveStudent();
          printf("GPA recalculation successfully!\n");
         found =1;
    break;
}
    }
    if(!found){
        printf("student not found!\n");
    }
}


//=============VIEW STUDENT===============

void viewStudent(){
    if (count == 0){
        printf("\nNo records found!\n"); 
        return;
    }

    printf("\n-----Students List-----\n");

    for (int i = 0; i<count ; i++){
        printf("\nID   : %d", students[i].id);
        printf("\nName : %s", students[i].name);
        printf("\nGPA  : %.2f\n", students[i].gpa);
    }
}

//====================SEARCH STUDENET====================

void searchStudent(){
    int id = 0; 
    int found = 0; 

    printf("\nEnter students ID for Search: "); 
    scanf("%d", &id);

    for (int i = 0; i<count; i++){
        if (students[i].id == id ){
            printf("\nStudent found!\n");
            printf("ID   : %d\n", students[i].id);
            printf("Name : %s\n", students[i].name);
            printf("GPA  : %.2f\n",students[i].gpa);
            found = 1;
            break ; 
            
            
        }
    }
    if(!found){
        printf("Student not found!\n"); 
    }
} 


//====================UPDATE STUDENT ====================

void updateStudent(){

    int id ; 
    int found = 0; 
    printf("\nEnter students id for Update : "); 
    scanf("%d", &id);


    for (int i = 0; i<count ; i++){
        if (students[i].id == id){
            printf("\nEnter new Name :");
            scanf(" %[^\n]", students[i].name);

            students[i].gpa = inputSubjects(&students[i]);
            
          
        saveStudent();

            printf("Student updated successfully!\n"); 
            found = 1 ; 
            break; 
            
        }
    }
    if (!found){
        printf("Student not found!\n"); 
    }
    
} 


//====================Delete Student====================

void deleteStudent() {

    int id, found = 0;

    printf("Enter Student ID to delete: ");
    scanf("%d", &id);

    for (int i = 0; i < count; i++) {
        if (students[i].id == id) {

            for (int j = i; j < count - 1; j++) {
                students[j] = students[j + 1];
            }

            count--;
            saveStudent();

            printf("student delete successfully!\n");

            found = 1;
            break;
        }
    }

    if (!found) {
       
        printf("Student not found!\n");
    }
}



/*====================Save Student====================
 Saves all student records to students.txt in CSV format*/

void saveStudent() {
    FILE *fp = fopen("students.txt", "w");

    if (fp == NULL) {
        printf("Error opening file for saving!\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        // save id, name, subjectCount
        fprintf(fp,"%d,%s,%d,",
            students[i].id,
            students[i].name,
            students[i].subjectCount);

       //save marks and credits
        for (int j = 0; j < students[i].subjectCount; j++) {

            fprintf(fp,"%.2f,%d,",
                students[i].marks[j],
                students[i].credits[j]);
        }

        fprintf(fp, "%.2f\n", students[i].gpa);
    }

    if(fclose(fp) !=0){
        printf("error closing file after saving");
    } else {
        printf("Data saved successfully\n");
    }
}


//==================LOAD STUDENT====================
// Loads student records from students.txt into memory

void loadStudent() {
    FILE *fp = fopen("students.txt", "r");

    if (fp == NULL) {
        printf("No existing data found.\n");
        return;
    }

    count = 0;

    while (!feof(fp)) {
        struct Student s;

        // Read ID, Name, SubjectCount
        if (fscanf(fp,"%d,%49[^,],%d,", &s.id, s.name, &s.subjectCount) != 3) {
            break;  // stop if format is wrong
        }

        // Read marks and credits
        for (int j = 0; j < s.subjectCount; j++) {
            if (fscanf(fp, "%f,%d,", &s.marks[j], &s.credits[j]) != 2) {
                printf("Error reading subject data. Skipping...\n");
                break;
            }
        }

       if( fscanf(fp, "%f\n", &s.gpa)!=1 ) {
       printf("Error reading GPA. Skipping record...\n");
       continue;}

        if (count < MAX_STUDENTS) {
            students[count++] = s;
        }
    }

   if (fclose(fp) != 0) {
        perror("Error closing file after loading");
    } else {
        printf("Data loaded successfully!\n");
    }
}


void exitProgram(){ 
    printf("Exiting...\n"); 
    exit(0); 
}

// End of Student Management Functions