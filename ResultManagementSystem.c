#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void StudentGrade();//function prototype
void ViewGrades();//function prototype
void FindMin(int a[],int n);//function prototype
void FindMax(int a[],int n);//function prototype
void FindMean(int a[],int n);//function prototype
void AddStudent();//function prototype
void DeleteStudent();//function prototype
void SortGrades(int a[],int size);//function prototype
void RewriteFile(char a[]);//function prototype

int main()
{
    char person[10];
    char answer;
    int choice;

    FILE *cfPtr;//file pointer

    puts("Letters are case sensitive.");

    //Start of do-while
    do
    {
        char sfirst[11];//student first name
        char slast[11];//student last name
        int grades[15];//student grade, holds 15 student grades
        int f=0;//used for grade array

        //opens file in reading mode and checks if it can be opened
        if((cfPtr=fopen("StudentAndGrades.txt","r"))==NULL)
        {
            puts("File could not be opened");
        }

        else
        {
            //All of this is just to get the grades of the students as integers,not strings
            fscanf(cfPtr,"%10s%10s%d", sfirst, slast, &grades[f]);//reads first line
            while(!feof(cfPtr))//continues until file ends
            {
                f++;//increases array for grades
                fscanf(cfPtr,"%10s%10s%d", sfirst, slast, &grades[f]);//reads line
            }

        }

        //Start of program
        printf("Enter if you are a Student or Teacher:");
        scanf("%s", person);

        //checks if input is Teacher
        if(strcmp(person,"Teacher")==0)
        {
            puts("1.View Students Grades 2.Find Min 3.Find Max 4.Find Mean 5.Add Student 6.Delete Student 7.Sort Grades ");
            printf("Enter the number of your choice:");
            scanf("%d",&choice);

            switch(choice)
            {
                //shows student names and their grades
                case 1:
                    ViewGrades();
                    break;

                //gets the min of the grades
                case 2:
                    FindMin(grades,f);
                    break;

                //gets the max of the grades
                case 3:
                    FindMax(grades,f);
                    break;

                //gets the mean of the grades
                case 4:
                    FindMean(grades,f);
                    break;

                //adds student
                case 5:
                    AddStudent();
                    break;

                //deletes student
                case 6:
                    DeleteStudent();
                    break;

                //sorts the grades
                case 7:
                    SortGrades(grades,f);
                    break;
            }
        }

        //checks if input is Student
        else if(strcmp(person,"Student")==0)
        {
            StudentGrade();//this lets student see there grade
        }

        //prints when input isn't "Student" or "Teacher"
        else
        {
            printf("That input isn't acceptable.\n");
        }

        printf("Do you want to continue with the program?(y/n):");

        scanf("%c", &answer);
        scanf("%c", &answer);//I need an extra scanf, otherwise program skips it when input is wrong

        while(answer!='y' && answer!='n')//checks if input is y or no(yes or no)
        {
            printf("That's not a valid answer.Try again.\n");
            printf("Do you want to continue with the program?(y/n):");

            scanf("%c", &answer);
            scanf("%c", &answer);//I need an extra scanf, otherwise program skips it when input is wrong
        }

        rewind(cfPtr);//resets file pointer
    //end of do-while
    }while(answer!='n');

    fclose(cfPtr);//closes file

    printf("End of program.");
}

//checks for student's grade in the file
void StudentGrade()
{
    FILE *sPtr;//file pointer

    char first[11];//user input
    char last[11];//user input
    char sfirst[11];//student first name
    char slast[11];//student last name
    char grade[3];//student grade

    printf("Enter your first name:");
    scanf("%s",first);
    printf("%s","Enter your last name:");
    scanf("%s",last);

    if((sPtr=fopen("StudentAndGrades.txt","r"))==NULL)
    {
        puts("File could not be opened");
    }

    else
    {
        while(!feof(sPtr))//continues until file ends
        {
            fscanf(sPtr,"%10s%10s%3s", sfirst, slast, grade);//reads another line

            //checks for student's first and last name
            if(strcmp(sfirst,first)==0 && strcmp(slast,last)==0)
            {
                printf("Your grade is %s.\n", grade);
                break;//ends while loop, because no need to continue
            }

            //Reached end of the file,so the student's name wasn't in the file
            if(feof(sPtr))
            {
                printf("Your name wasn't in the file.\n");
            }

        }
        fclose(sPtr);//closes file
    }
}

//Shows teacher all the student's names and grades
void ViewGrades()
{
    FILE *vPtr;// file pointer

    char sfirst[11];//student first name
    char slast[11];//student last name
    char grade[3];//student grade

    if((vPtr=fopen("StudentAndGrades.txt","r"))==NULL)
    {
        puts("File could not be opened");
    }

    else
    {
        //I print out the file like this so it's nicer to read
        printf("%12s %14s\n", "Students", "Grades");//title of the table
        fscanf(vPtr,"%10s%10s%2s", sfirst, slast, grade);//reads first line

        while(!feof(vPtr))//continues until file ends
        {
            printf("%-10s %-10s %4s\n", sfirst, slast, grade);//prints out the line
            fscanf(vPtr,"%10s%10s%2s", sfirst, slast, grade);//reads another line
        }

        fclose(vPtr);//closes file
    }

}

//finds the max of the grades
void FindMax(int a[],int n)
{
    int max, i;
    max = a[0];

    //looks through the array to find the highest number
    for(i=1; i<n; i++)
    {
        if(max<a[i])
            max=a[i];
    }

    printf("The max of all the grades is %d\n",max);
}

//finds the min of the grades
void FindMin(int a[],int b)
{
    int min,i;
 	min = a[0];

 	//looks through the array to find the lowest number
    for(i=1; i<b; i++)
    {
         if(min>a[i])
		  min=a[i];
    }

    printf("The min of all the grades is %d\n",min);
}

//finds the mean of the grades
void FindMean(int a[],int n)
{
    int i;
    int sum = 0;

    //adds all the numbers from array
    for(i = 0; i < n; i++) {
      sum+=a[i];
    }

    printf("The average of the grades is %.2f\n", sum/(float)n);
}

//adds student to the file
void AddStudent()
{
    char addstudent[25];//used to add the string of student's first name, last name, and grade
    char addlast[11];//user input
    char addgrade[3];//user grade

    char character;
    char file[300];//array to add strings, used later to rewrite the file
    int f=0;

    //gets student's first name and its written addstudent array
    printf("Enter new student's first name:");
    scanf("%10s",addstudent);
    strcat(addstudent," ");//adds space

    //gets last name and adds it to the newstudent array
    printf("%s","Enter new student's last name:");
    scanf("%10s",addlast);
    strcat(addstudent,addlast);//adds last name
    strcat(addstudent," ");//adds space

    //gets student's grade and adds it to the newstudent array
    printf("%s","Enter new student's grade name:");
    scanf("%2s",addgrade);
    strcat(addstudent,addgrade);//adds grade
    strcat(addstudent,"\n");//adds space

    FILE *aPtr;//file pointer
    //In the file, there needs to be a newline space under last student's name so the added student will appear underneath

    //opens file in reading mode and checks if it can be opened
    if((aPtr=fopen("StudentAndGrades.txt","r"))==NULL)
    {
        puts("File could not be opened");
    }

    else
    {
        //reads the file character by character until it reaches the end
        while(!feof(aPtr))//continues until file ends
        {
            character=fgetc(aPtr);//reads one character in the file

            //file pointer has reached the end of the file
            if(feof(aPtr))
            {
                file[f]='\0';//adds terminate character to close string
                break;//ends the loop because no need to continue
            }

            file[f]=character;//adds character to file string
            f++;
        }

        fclose(aPtr);//closes file
    }

    strcat(file,addstudent);//adds new student at the end of the file

    RewriteFile(file);//rewrite the file with the file string

    puts("The student has been added to file.");

}

//rewrites the file
void RewriteFile(char a[])
{
    FILE *wPtr;

    int p=0;

    //opens file in writing mode and checks if it can be opened
    if((wPtr=fopen("StudentAndGrades.txt","w"))==NULL)
    {
        puts("File could not be opened");
    }

    else
    {
        //rewrites the file character by character
        while(a[p]!='\0')//continues until file ends
        {
            fputc(a[p],wPtr);//write character to the file
            p++;//used to go to next character
        }

        fclose(wPtr);//closes file
    }

}

//deletes student from the file
void DeleteStudent()
{
    FILE *dPtr;

    char deletefirst[11];//student first name
    char deletelast[11];//student last name
    char sfirst[11];//student first name in file
    char slast[11];//student last name in file
    char grade[3];//student grade in file

    char file[300];//array to add strings, used later to rewrite into file
    file[0]='\0';//sets ups the file string
    int found=0;//used to determine if student is in the file or not

    //gets student first name
    printf("Enter student's first name:");
    scanf("%10s",deletefirst);

    //gets student last name
    printf("%s","Enter student's last name:");
    scanf("%10s",deletelast);

    if((dPtr=fopen("StudentAndGrades.txt","r"))==NULL)
    {
        puts("File could not be opened");
    }

    else
    {
        fscanf(dPtr,"%10s%10s%2s", sfirst, slast, grade);//reads first line

        //the strings get added again to the string, but won't add the deleted student's name
        while(!feof(dPtr) )
        {
            //it won't add the deleted student's name, technically "deleting it from the file"
            if(strcmp(sfirst,deletefirst)==0 && strcmp(slast,deletelast)==0)
            {
                puts("The student has been deleted from the file.");
                found=1;//means the student name was in the file and is deleted
            }

           else
            {
                strcat(file,sfirst);//adds first name
                strcat(file," ");//adds space
                strcat(file,slast);//adds last name
                strcat(file," ");//adds space
                strcat(file,grade);//adds grade
                strcat(file,"\n");//adds newline
            }

            fscanf(dPtr,"%10s%10s%2s", sfirst, slast, grade);//reads first line
        }

        //means student wasn't in the file
        if(found==0)
            printf("That student isn't in the file.\n");
    }

    fclose(dPtr);//closes file
    RewriteFile(file);//rewrite the file with the file string

}

//sorts the grades in the file
void SortGrades(int a[],int size)
{
    FILE *gPtr;

    char sfirst[11];//student first name in file
    char slast[11];//student last name in file
    char grade[3];//student grade in file
    double number;//used to hold grade as double
    char *stringPtr;//char pointer
    char file[300];//array to add strings, used later to rewrite into file
    file[0]='\0';//sets ups the file string

    int i=0;
    int temp;

    //this sorts the grades
    for(int k=1;k<size;k++)
    {
        for(int n=0;n<size-1;n++)
        {
            //swaps the elements
            if(a[n]>a[n+1])
            {
                temp=a[n];
                a[n]=a[n+1];
                a[n+1]=temp;
            }
        }
    }

    //opens file in reading mode
     if((gPtr=fopen("StudentAndGrades.txt","r"))==NULL)
    {
        puts("File could not be opened");
    }

    else
    {
        //runs until it reaches end of grade array
        while(i<size)
        {
            fscanf(gPtr,"%10s%10s%2s", sfirst, slast, grade);//reads first line

            //the strings get added to the file string
            while(!feof(gPtr) )//continues until file ends
            {
                number=strtod(grade,&stringPtr);//converts grade from file into a double

               if(number==a[i])
                {
                    strcat(file,sfirst);//adds first name
                    strcat(file," ");//adds space
                    strcat(file,slast);//adds last name
                    strcat(file," ");//adds space
                    strcat(file,grade);//adds grade
                    strcat(file,"\n");//adds newline
                    i++;//used to go to next grade in grade array
                }
                fscanf(gPtr,"%10s%10s%2s", sfirst, slast, grade);//reads next line

            }
            rewind(gPtr);//resets file pointer, to go over file again
        }
    }
    fclose(gPtr);//closes file
    RewriteFile(file);//rewrite the file with the file string

    puts("The grades in the file have been sorted.");
}
