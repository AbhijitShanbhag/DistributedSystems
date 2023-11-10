//
//  main.c
//  Distributed Task Scheduler
//
//  Created by Abhijit Shanbhag on 09/11/23.
//
#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"
#include "string.h"

/*
 void generateSalt(char* saltArray, int size){
     //Initialising a random seed, which is current value of time. Since it returns a time_t guys, I have used conversion to unsigned int conversion
     //Akshat also used this to initialise value with random value
     srand((unsigned int)time(NULL));
     for (int i=0; i<size; i++) {
         saltArray[i]=rand()%256;
     }
 }
 
 
  Two Types Exist Guys: So I have choosen SHA(SecureHashAlgorithm)256 than MD5, cause it's limited to 128bits, than 256 bits
  Now, inputPassword is stored to
  */

/*
 Generation of Salt with Seed Value Set to Current Time, This thing to be done later. @AkshatSingh and @Kothari, guys we can do this later, after everything is done. It is a complex Library
 //Salt Part is completely done right now guys
 
 
 
 
 Another block of code is

 */

// Later: #include "time.h"
// Later: #include "/opt/homebrew/Cellar/openssl@3/3.1.4/include/openssl/sha.h"

//Structure to Store Username, Salt, and Password
typedef struct userData {
    char username[20];
    char randomSalt[64];
    char hashedPassword[64];
    
}userInfo;

#define SYSTEMSIZE  3
#define TASKSIZE    5








struct task {
    int id;
    struct task* nextTask;
};

struct system {
    userInfo systemInformation;
    struct task* firstTask;
    int systemID;
    
};

typedef struct task TASK;
typedef struct system SYSTEM;




void sha256BasedAuthentication(char* inputPassword, char* hashingDestination){
    //Later
}

TASK* createTask(int id){
    TASK* newTask=(TASK*)malloc(sizeof(TASK));
    newTask->id=id;
    newTask->nextTask=NULL;
    return newTask;
}

SYSTEM* addTask(SYSTEM* currentSystem, int taskID){
    if (currentSystem==NULL) {
        printf("System Does Not Exist, SystemError");
        return NULL;
    }
    else{
        TASK* currentFirst=currentSystem->firstTask;
        TASK* newTask=createTask(taskID);
        
        if (currentFirst==NULL) {
            //No task scheduled, create a new task and allocate it to the System
            currentSystem->firstTask=newTask;
            return currentSystem;
        }
        
        else{
            TASK* lastTask=currentFirst;
            while (lastTask->nextTask!=NULL) {
                lastTask=lastTask->nextTask;
            }
            lastTask->nextTask=newTask;
            return currentSystem;
        }
    }
}

void systemTaskAddition(int systemValue, int taskValue, SYSTEM* systemArray[SYSTEMSIZE]){
    if (systemValue>-1 && systemValue<SYSTEMSIZE) {
        if (systemArray[systemValue]==NULL) {
            systemArray[systemValue]=(SYSTEM*)malloc(sizeof(SYSTEM));
            systemArray[systemValue]->systemID=systemValue;
            systemArray[systemValue]->firstTask=NULL;
        }
        systemArray[systemValue]=addTask(systemArray[systemValue], taskValue);
    }else{
        printf("Invalid System Value %d\n", systemValue);
    }
}

void displaySystemInformation(SYSTEM* systemArray[SYSTEMSIZE]){
    for (int i=0; i<SYSTEMSIZE; i++) {
        if (systemArray[i]) {
            printf("System is %d\n", systemArray[i]->systemID);
            TASK* temp=systemArray[i]->firstTask;
            int taskCount=1;
            while (temp!=NULL) {
                printf("\tTask Number %d is with ID%d\n", taskCount, temp->id);
                taskCount++;
                temp=temp->nextTask;
            }
        }
        else{
            printf("No Task Assigned for the System %d", i);
        }
        
    }
}

int main(void){
    FILE* systemTaskFile;
    char currentReadST[6]; //Character Temporary Buffer
    systemTaskFile=fopen("/Users/abhijitshanbhag/Desktop/Abhijit's C Files/Distributed Task Scheduler/TaskSystemCollection.txt", "r");
    
    
    if (!systemTaskFile) {
        perror("Error Opening the File\n");
        exit(-1);
    }
    
    SYSTEM* systemArray[SYSTEMSIZE]={NULL};
    
    int taskValue, systemValue;
    while (fgets(currentReadST, sizeof(currentReadST), systemTaskFile)) {
        currentReadST[strcspn(currentReadST, "\n")]='\0';
        if (sscanf(currentReadST,"%d %d", &taskValue, &systemValue)==2) {
            systemTaskAddition(systemValue, taskValue, systemArray);
        }
    }
    fclose(systemTaskFile);
    displaySystemInformation(systemArray);
    
    
}
