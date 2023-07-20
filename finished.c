#include <stdio.h>
#include <string.h>
#include <math.h>


typedef struct Students{
  
  int id;
  char fname[200];
  char lname[200];
  int day;
  int month;
  int year;
  
}Students;


typedef struct Courses{
  
  char cid[200];
  char cname[200];
  float credit;
  
}Courses;

typedef struct Enrollments{
  
  int id;
  char cid[200];
  char semester[200];
  float score;
  
}Enrollments;



void loadStudents(Students st[], int *numStudents);
int loadEnrollment(Enrollments en[]);
int loadCourses(Courses course[]);


void menu(Students ArrayOfStudents[], int amountStudents, Courses ArrayOfCourses[], int amountCourses, Enrollments ArrayOfEnrollments[], int amountEnrolls);

void count(Students st[], int numStudents, Courses course[], int numcourses, Enrollments en[], int numenroll, char option[]);

void sort(Students st[], int amountStudents);

void search_course(Students st[], int numStudents, Courses course[], int numcourses, Enrollments en[], int numenroll, char option[]);


int main(void){
 
 
  int numStudents, numenroll, numcourses;
  
  Students st[2000];
  Courses course[100];
  Enrollments en[5000];
  
  loadStudents(st, &numStudents);
  numenroll=loadEnrollment(en);
  numcourses=loadCourses(course);
  
  printf("==================\n");

  menu( st,  numStudents, course, numcourses, en,  numenroll);
 
  return 0;
    
}

void loadStudents(struct Students st[], int *numStudents){
  
  FILE*stu;
  stu=fopen("students.txt", "r");
  
  int i=0;
  *numStudents=0;
  
  while(!feof(stu)){
    
    fscanf(stu, "%d %s %s %d %d %d", &st[i].id, st[i].fname, st[i].lname, &st[i].day, &st[i].month, &st[i].year);
    
    *numStudents=*numStudents+1;
    
    i++;
    
  }
  
}

int loadEnrollment(struct Enrollments en[]){
  
  FILE*enr;
  enr=fopen("enrollment.txt", "r");
  
  int i=0;
  
  while(!feof(enr)){
    
    fscanf(enr, "%d %s %s %f", &en[i].id, en[i].cid, en[i].semester, &en[i].score);
    
    i++;
    
  }
  
  return i;
  
}

int loadCourses(struct Courses course[]){
  
  FILE*cou;
  cou=fopen("courses.txt", "r");
  
  int i=0;
  
  while(!feof(cou)){
    
    fscanf(cou, "%s %s %f", course[i].cid, course[i].cname, &course[i].credit);
    
    i++;
    
  }
  
  return i;
  
}

void menu(Students ArrayOfStudents[], int amountStudents, Courses ArrayOfCourses[], int amountCourses, Enrollments ArrayOfEnrollments[], int amountEnrolls){
  
  int i, j, z, k, numStudents, numenroll, numcourses, found;

  Students st[2000];
  Courses course[100];
  Enrollments en[5000];
  
  char command[120], option[120], lname[120], fname[120], ch;
  int id, byear, inputn;
  char input[120], cid[120], semester[120], newcid[120], newcname[120], cname[120];
  float newccredit;
  int studentcount;


  numStudents=amountStudents;
  numcourses=amountCourses;
  numenroll=amountEnrolls;
  
  for(i=0; i<amountStudents; i++){
    st[i].id=ArrayOfStudents[i].id;
    strcpy(st[i].fname, ArrayOfStudents[i].fname);
    strcpy(st[i].lname, ArrayOfStudents[i].lname);
    st[i].day=ArrayOfStudents[i].day;
    st[i].month=ArrayOfStudents[i].month;
    st[i].year=ArrayOfStudents[i].year;
  }

  for(i=0; i<amountEnrolls; i++){
    en[i].id=ArrayOfEnrollments[i].id;
    strcpy(en[i].cid, ArrayOfEnrollments[i].cid);
    strcpy(en[i].semester, ArrayOfEnrollments[i].semester);
    en[i].score=ArrayOfEnrollments[i].score;
  }
  
  for(i=0; i<amountCourses; i++){
    strcpy(course[i].cid, ArrayOfCourses[i].cid);
    strcpy(course[i].cname, ArrayOfCourses[i].cname);
    course[i].credit=ArrayOfCourses[i].credit;
  }
  
  
  while(1){
    
    scanf("%s", command);
    
    if(strcmp(command, "exit")==0){
      printf("------------------\n");
      printf("Bye!");
      break;
    }
    
    if(strcmp(command, "sort")==0){
      sort(st, amountStudents);
      continue;
    }
    
    scanf("%s", option);
      
    if(strcmp(option, "id")==0 ||strcmp(option, "byear")==0 )
      scanf("%d", &inputn);

    found=0;
    
    printf("------------------\n");

    if(strcmp(command, "search_students")==0){
      
      if(strcmp(option, "lname")==0){
        
        scanf("%s", input);
      
        strcpy(lname, input);
        
        for(i=0; i<numStudents; i++){
          
          if(strcmp(lname, st[i].lname)==0){
            
            found=1;
            printf("%d %s %s %d/%d/%d\n", st[i].id, st[i].fname, st[i].lname, st[i].month, st[i].day, st[i].year);
            
            for(j=0; j<numenroll; j++){
              
              if(st[i].id==en[j].id){
                
                printf("%s ", en[j].cid);
                
                for(z=0; z<numcourses; z++)
                  if(strcmp(en[j].cid, course[z].cid)==0)
                    printf("%s ", course[z].cname);
                  
                printf("%s %.f ", en[j].semester, en[j].score);
                
                if(en[j].score>=90)
                  printf("A");
                else if(en[j].score<90 && en[j].score>=80)                
                  printf("B");
                else if(en[j].score<80 && en[j].score>=70)
                  printf("C");
                else if(en[j].score<70 && en[j].score>=60)
                  printf("D");
                else if(en[j].score<60)                  
                  printf("F");
                  
                printf("\n");

              }
              
            }
            
            printf("------------------\n");

          }
          
        }
        
        if(found==0){
          printf("not found\n");
          printf("------------------\n");
        }
        
      }
      
      if(strcmp(option, "fname")==0){
        
        scanf("%s", input);
      
        while((ch = getchar()) !='\n' && ch !=EOF);

        strcpy(fname,input);

        for(i=0; i<numStudents; i++){
          
          if(strcmp(fname, st[i].fname)==0){
            
            found=1;
            printf("%d %s %s %d/%d/%d\n", st[i].id, st[i].fname, st[i].lname, st[i].month, st[i].day, st[i].year);
            
            for(j=0; j<numenroll; j++){
              
              if(st[i].id==en[j].id){
                
                printf("%s ", en[j].cid);
                
                for(z=0; z<numcourses; z++)
                  if(strcmp(en[j].cid, course[z].cid)==0)
                    printf("%s ", course[z].cname);
                  
                printf("%s %.f ", en[j].semester, en[j].score);
                
                if(en[j].score>=90)
                  printf("A");
                else if(en[j].score<90 && en[j].score>=80)             
                  printf("B");
                else if(en[j].score<80 && en[j].score>=70)
                  printf("C");
                else if(en[j].score<70 && en[j].score>=60)
                  printf("D");
                else if(en[j].score<60)                  
                  printf("F");
                  
                printf("\n");

              }
              
            }
            
            printf("------------------\n");

          }
          
        }
        
        if(!found){
          printf("not found\n");
          printf("------------------\n");

        }
      }
      
      if(strcmp(option, "id")==0){
        
        id=inputn;
      
        for(i=0; i<numStudents; i++){
          
          if(id==st[i].id){
            
            found=1;
            printf("%d %s %s %d/%d/%d\n", st[i].id, st[i].fname, st[i].lname, st[i].month, st[i].day, st[i].year);
            
            for(j=0; j<numenroll; j++){
              
              if(st[i].id==en[j].id){
                
                printf("%s ", en[j].cid);
                
                for(z=0; z<numcourses; z++)
                  if(strcmp(en[j].cid, course[z].cid)==0)
                    printf("%s ", course[z].cname);
                  
                printf("%s %.f ", en[j].semester, en[j].score);
                
                if(en[j].score>=90)
                  printf("A");
                else if(en[j].score<90 && en[j].score>=80)             
                  printf("B");
                else if(en[j].score<80 && en[j].score>=70)
                  printf("C");
                else if(en[j].score<70 && en[j].score>=60)
                  printf("D");
                else if(en[j].score<60)                  
                  printf("F");
                  
                printf("\n");

              }
              
            }
            
            printf("------------------\n");

          }
          
        }
        
        if(!found){
          printf("not found\n");
          printf("------------------\n");

        }
      }

      if(strcmp(option, "byear")==0){
        
        byear=inputn;

        while((ch = getchar()) !='\n' && ch !=EOF);

        for(i=0; i<numStudents; i++){
          
          if(byear==st[i].year){
            
            found=1;
            printf("%d %s %s %d/%d/%d\n", st[i].id, st[i].fname, st[i].lname, st[i].month, st[i].day, st[i].year);
            
            for(j=0; j<numenroll; j++){
              
              if(st[i].id==en[j].id){
                
                printf("%s ", en[j].cid);
                
                for(z=0; z<numcourses; z++)
                  if(strcmp(en[j].cid, course[z].cid)==0)
                    printf("%s ", course[z].cname);
                  
                printf("%s %.f ", en[j].semester, en[j].score);
                
                if(en[j].score>=90)
                  printf("A");
                else if(en[j].score<90 && en[j].score>=80)                
                  printf("B");
                else if(en[j].score<80 && en[j].score>=70)
                  printf("C");
                else if(en[j].score<70 && en[j].score>=60)
                  printf("D");
                else if(en[j].score<60)                  
                  printf("F");
                  
                printf("\n");

              }
              
            }
            
            printf("------------------\n");

          }
          
        }
        
        if(!found){
          printf("not found\n");
          printf("------------------\n");

        }
      }

    }
    
    if(strcmp(command, "search_course")==0)
      search_course( st, numStudents, course, numcourses, en, numenroll,option);
      
    
    if(strcmp(command, "add_course")==0){
      
      scanf("%s", newcname);

      scanf("%f", &newccredit);
      
      for(i=0; i<numcourses; i++){
        
        if(strcmp(course[i].cid, option)==0){
          printf("violation of course id uniqueness. Cannot add the record.\n");
          printf("------------------\n");
          break;
        }
      
      }
      
      if(numcourses==i){
        
        FILE*fp=fopen("courses.txt", "r+");
        fseek(fp,0,SEEK_END);
        
        fprintf(fp,"\n%s %s %.f", option, newcname, newccredit);
        printf("record added\n");
        printf("------------------\n");
        
        fclose(fp);
        
        strcpy(course[numcourses].cid, option);
        strcpy(course[numcourses].cname, newcname);
        course[numcourses].credit=newccredit;

        numcourses++;
        
      }
      
    }
    
    if(strcmp(command, "count")==0)
      count(st,numStudents,course, numcourses, en, numenroll, option);
    
    printf("==================\n");
      
  }
  
}

void sort(struct Students st[], int amountStudents){
  
  int i,j, temp, indexi, indexj;
  char tempa[50];
  
  for(i=0; i<amountStudents; i++){
    
    for(j=i+1; j<amountStudents ; j++){
      
      if(st[i].id>st[j].id){
        
        temp=st[i].id;
        st[i].id=st[j].id;
        st[j].id=temp;
        
        strcpy(tempa, st[i].fname);
        strcpy(st[i].fname, st[j].fname);
        strcpy(st[j].fname, tempa);
        
        strcpy(tempa, st[i].lname);
        strcpy(st[i].lname, st[j].lname);
        strcpy(st[j].lname, tempa);
        
        temp=st[i].month;
        st[i].month=st[j].month;
        st[j].month=temp;
        
        temp=st[i].day;
        st[i].day=st[j].day;
        st[j].day=temp;
        
        temp=st[i].year;
        st[i].year=st[j].year;
        st[j].year=temp;
        
      }
    }
    
    printf("%d %s %s %d %d %d\n", st[i].id, st[i].fname, st[i].lname, st[i].month, st[i].day, st[i].year);
    
  }
  
}
  
  
void count(Students st[], int numStudents, Courses course[], int numcourses, Enrollments en[], int numenroll, char option[]){
  
  int i,j, z, semarrsize, studentcount, coursecount, countArr[50];
  char semesterArr[50][50];
      
  if(strcmp(option, "students")==0){
        
    for(i=0; i<numStudents; i++)
    ;
      studentcount=i;
          
      printf("total students %d\n", studentcount);
      printf("------------------\n");

  }
      
  if(strcmp(option, "students_course")==0){
        
    for(i=0; i<numcourses; i++){
          
      coursecount=0;
          
      for(j=0; j<numenroll; j++){
            
        if(strcmp(course[i].cid, en[j].cid)==0)
          coursecount++;
            
      }
          
      printf("%s %d \n", course[i].cid, coursecount);
          
    }
        
  }
      
  if(strcmp(option,"students_semester")==0){
    
    int countArr[50], num_semesters=0, found;
        
    strcpy(semesterArr[0], en[0].semester);
        
      for(i=0,z=0; i<numenroll; i++){
        
        found=0;
        
        for(j=0; j<num_semesters; j++){
          
          if(strcmp(en[i].semester, semesterArr[j])==0){
            countArr[j]++;
            found=1;
          }
        }
        
        if(!found){
          strcpy(semesterArr[j], en[i].semester);
          num_semesters++;
        }
      }

      for(i=0; i<num_semesters; i++)
        printf("%s %d\n", semesterArr[i], countArr[i]+1);
        
  }
  
}

void search_course(Students st[], int numStudents, Courses course[], int numcourses, Enrollments en[], int numenroll, char option[]){
  
  char cid[50], semester[50];
  int i,j,z, found=0; 
      
  if(strcmp(option, "cid")==0){
      
    scanf("%s", cid);
        
    for(i=0; i<numcourses; i++){
          
      if(strcmp(cid, course[i].cid)==0){
            
        found=1;
        printf("%s %.f\n", course[i].cname, course[i].credit);
            
        for(j=0; j<numenroll; j++){
              
          if(strcmp(course[i].cid, en[j].cid)==0){
                
            for(z=0; z<numStudents; z++)
              if(en[j].id==st[z].id)
               printf("%s %s ", st[z].fname, st[z].lname);
                  
            printf("%s %.f ", en[j].semester, en[j].score);
                
            if(en[j].score>=90)
              printf("A");
            else if(en[j].score<90 && en[j].score>=80)                
              printf("B");
            else if(en[j].score<80 && en[j].score>=70)
              printf("C");
            else if(en[j].score<70 && en[j].score>=60)
              printf("D");
            else if(en[j].score<60)                  
              printf("F");
                  
            printf("\n");

          }
              
        }
            
        printf("------------------\n");

      }
          
    }
        
    if(found==0){
      printf("not found\n");
      printf("------------------\n");
    }
        
  }
      
  if(strcmp(option, "cid_semester")==0){
        
    scanf("%s", cid);
        
    scanf("%s", semester);

    for(i=0; i<numcourses; i++){
          
      if(strcmp(cid, course[i].cid)==0){
            
        printf("%s %.f\n", course[i].cname, course[i].credit);
            
        for(j=0; j<numenroll; j++){
              
          if(strcmp(course[i].cid, en[j].cid)==0){
                
            for(z=0; z<numStudents; z++)
              if(en[j].id==st[z].id && strcmp(en[j].semester,semester)==0){
                    
                found=1;
                printf("%s %s ", st[z].fname, st[z].lname);
                  
                printf("%s %.f ", en[j].semester, en[j].score);
                
                if(en[j].score>=90)
                  printf("A");
                else if(en[j].score<90 && en[j].score>=80)               
                  printf("B");
                else if(en[j].score<80 && en[j].score>=70)
                  printf("C");
                else if(en[j].score<70 && en[j].score>=60)
                  printf("D");
                else if(en[j].score<60)                  
                  printf("F");
                  
              printf("\n");
                
              }
          }
              
        }
            
        printf("------------------\n");

      }
          
    }
        
    if(found==0){
      printf("not found\n");
      printf("------------------\n");
    }
        
  }
      
}

