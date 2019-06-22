#include "../include/Tests.h"
#include "../include/ProjectTest.h"
#include "../include/SubTests.h"
#include <iostream>
#include <typeinfo>
#include <fstream>
#include <math.h>
#include <sstream>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <vector>

using std::vector;
using std::streambuf;
using std::istringstream;
using std::to_string;
using std::cout;
using std::sprintf;
using std::ifstream;
using std::stringstream;

#define RED   "\e[38;5;196m"
#define GRN   "\e[38;5;082m"
#define YEL   "\e[38;5;226m"
#define MAG   "\e[38;5;201m"
#define RESET "\e[0m"

// Defining Global Variables
extern vector<string> testsInputs;
extern vector<string> testsExpected;
extern vector<vector<string>> testsInteractiveExpect;
extern vector<vector<string>> testsInteractiveSend;
extern vector<string> testsExecuteCommandArgs;
extern vector<vector<string>> testsUserPrograms;
extern vector<vector<string>> testsDefaultUserPrograms;
extern vector<string> testsHints;
extern vector<int> tesTimeLimits;

std::stringstream ss;
std::streambuf *old_buf;
extern int abortExecution;
extern int timeForSmallTest;
extern int testToExecute;

// Initializing before execution of tests
void Initialize()
{ 
  //change the underlying cout buffer and save the old buffer
  old_buf = std::cout.rdbuf(ss.rdbuf());

  // Catching signal
  signal(SIGINT,sigintHandler);
  signal(SIGQUIT,sigquitHandler);
}

// Finialize after execution of tests
void Finialize()
{   
    // Restoring cout buffer
    std::cout.rdbuf(old_buf);

    // Printing cout output
    std::string text_output = ss.str();
    std::cout << text_output;
}

// Initializing tests to be executed
void InitializingTests()
{
    /* ### Example of use ###

     testsFunctions.push_back();

    */

    // Initializing tests to be executed
    testsFunctions.push_back(Operating_System_Test);
}

/* ### Example of use ###

// Executing DEMO_TEST
void DEMO_TEST()
{
  // Initializing
  currentTestName = DEMO_TEST

  // Testing

  test(0,"got","expected");

  try
  {
    test(1,"maybe exception will be thrwon from here,"$$$ ASSERT_THROWN_EXCEPTIONS $$$");
  }
  catch (ExceptionType exp)
  {
    test("","$$$ DECLARE GOOD TEST $$$");
  }

}
*/

// Processing test
bool procceseTest(string testName,unsigned int testNumber){
    // Initializing 
    string testBaseFolder = "Tests/" + testName;
    string testFolder = "./Project_Test/" + testBaseFolder;
    string testInputFileName = "/testInput.txt";
    string testOutputFileName = "/testOutput.txt";
    string testMakefileErrorFileName = "/makefileError.txt";
    string testExecuteTestFileName = "/executeTest.sh";
    string testExecuteTestGDBFileName = "/executeTestGDB.sh";
    string testMakefileCommandFileName = "/makefileCommandForDebug.txt";
    string testsExpectedFileName = "/testExpected.txt";
    int testCompletedFlag;
    string test_command;
    string got_test;

    // Setting test time limist 
    timeForSmallTest = tesTimeLimits.at(testNumber);
    
    // Creating XV6 Tests Folder
    createXV6_TestMakefile(testBaseFolder + "/Makefile",testsUserPrograms.at(testNumber),testsDefaultUserPrograms.at(testNumber));

    // Creating test make command
    string test_makefileCommand = "make --makefile=" + testFolder +  "/Makefile clean qemu " + testsExecuteCommandArgs.at(testNumber);

    // Executing test
    if(testsInteractiveExpect.at(testNumber).size() == 0){
      test_command = "cd .. && " + test_makefileCommand + " -s < " + testFolder + testInputFileName;
      got_test = GetStdoutFromCommandAsync(test_command,"Finished Yehonatan Peleg Test, quiting...",timeForSmallTest,testCompletedFlag);  
    }
    else{
      test_command = "cd .. && " + test_makefileCommand;
      got_test = GetStdoutFromCommandInteractive(test_command,testsInteractiveExpect.at(testNumber), testsInteractiveSend.at(testNumber),
                 timeForSmallTest,testCompletedFlag);  
    }
    
    // Cleaning after test
    string clean_makefileCommand = "make --makefile=" + testFolder +  "/Makefile clean";
    string clean_command = "cd .. && " + clean_makefileCommand;
    GetStdoutFromCommand(clean_command);

    // Creating Test Makefile command
    std::ofstream outTestMakefileCommand(testBaseFolder + testMakefileCommandFileName);
    outTestMakefileCommand << test_makefileCommand;
    outTestMakefileCommand.close();

    // Creating test execute file
    std::ofstream outTestExecuteCommand(testBaseFolder + testExecuteTestFileName);
    outTestExecuteCommand << test_makefileCommand;
    outTestExecuteCommand.close();

    // Creating test execute GDB file
    std::ofstream outTestExecuteGDBCommand(testBaseFolder + testExecuteTestGDBFileName);
    outTestExecuteGDBCommand << test_makefileCommand + "-gdb";
    outTestExecuteGDBCommand.close();

    // Authorizing executing test execute file
    string authorizeExecuteTestFile_command = "chmod +x " + testBaseFolder + testExecuteTestFileName;
    GetStdoutFromCommand(authorizeExecuteTestFile_command);

    // Authorizing executing test execute GDB file
    string authorizeExecuteTestGDBFile_command = "chmod +x " + testBaseFolder + testExecuteTestGDBFileName;
    GetStdoutFromCommand(authorizeExecuteTestGDBFile_command);
    
    // Processing test output
    got_test = processTestOutput(got_test);

    // Writing test output to file
    std::ofstream out(testBaseFolder + testOutputFileName);
    out << got_test;
    out.close();

    // Retrieving test hint 
    string test_hint = testsHints.at(testNumber);

    // Asserting test completed
    if(testCompletedFlag == 1){
      // Retrieving test expected
      string expected_test = processCompareString(testsExpected.at(testNumber));

      if(expected_test.at(0) == '#'){
        if(got_test.find(expected_test.substr(1)) != std::string::npos){
          test(testNumber,"","$$$ DECLARE GOOD TEST $$$");
        }
        else{
          expected_test = "Output should have contain this: \n" + expected_test.substr(1);
          test(testNumber,got_test,expected_test,vector<string>{"String value with /n",test_hint});
        }
        
      }
      else if(expected_test.at(0) == '+'){
        if(countSubStr(got_test,expected_test.substr(2)) == (expected_test.at(1) - '0')){
          test(testNumber,"","$$$ DECLARE GOOD TEST $$$");
        }
        else{
          expected_test = "Output should have contain this: \n" + expected_test.substr(2) + "\n" + 
                          expected_test.at(1) + " times";
          test(testNumber,got_test,expected_test,vector<string>{"String value with /n",test_hint});
        }
      }
      else if(expected_test.at(0) == '@'){
        vector<string> expectedSearchedTokens = splitString(expected_test.substr(2), "\n");

        if(expectedSearchedTokens.size() > 0 && expectedSearchedTokens.size() % 2 != 0){
          printf("Error in test implementation in @ case!!!\n");
        }
        else{
          int expectedTimes;
          string timesString;
          int gotTimes;
          string result = "";

          for(unsigned int i = 0;i < expectedSearchedTokens.size();i = i + 2){
            expectedTimes = std::stoi(expectedSearchedTokens.at(i));
            string timesString = expectedSearchedTokens.at(i + 1);
            gotTimes = countSubStr(got_test,timesString);

            if(gotTimes != expectedTimes){
              result += "Output should have contain this: \n" + timesString + "\n" + 
                std::to_string(expectedTimes) + " times but contained it " + std::to_string(gotTimes) + 
                " times\n";
            }
          }

          if(result == ""){
            test(testNumber,"","$$$ DECLARE GOOD TEST $$$");
          }
          else{
            expected_test = result.substr(0,result.size() - 1);
            test(testNumber,got_test,expected_test,vector<string>{"String value with /n",test_hint});
          }
        }
      }
      else{
          test(testNumber,got_test,expected_test,vector<string>{"String value with /n",test_hint});
      }

      // Writing test expected to file
      std::ofstream expected(testBaseFolder + testsExpectedFileName);
      expected << expected_test;
      expected.close();
    }
    else if(testCompletedFlag == 0){
      // Creating Test Expected
      std::ofstream outError(testBaseFolder + testMakefileErrorFileName);
      outError << got_test;
      outError.close();

      // Declaring Test Execution Ended With Timeout
      test(testNumber,"$$$ SMALL TEST EXECUTION TIMED OUT $$$","",vector<string>{"",test_hint});
    }
    else if(testCompletedFlag == 2){
      // Declaring Test Execution Was Terminated By User
      test(testNumber,"$$$ USER TERMINATED TEST $$$","",vector<string>{"",test_hint});
    }
    else{
      // Declaring Test Execution Ended With Error
      test(testNumber,"$$$ TEST EXECUTION ERROR $$$","",vector<string>{"",test_hint});
    }

    return 0;
}

// Running specific test
void runSpecificTest(int testToExecute){
    // Initializing
    string test_name = "test_" + std::to_string(testToExecute);
  
    // Declaring specific test is running
    printf("Running ");
    printf("test_");
    printf("%d for specific test request\n\n",testToExecute);

    // Runnig specific test
    procceseTest(test_name,testToExecute);
}

// Creating Tests
unsigned int CreateTests()
{
  // Creating Tests Folder
  string createTestFolderCommand = "rm -rf Tests && mkdir Tests";
  string got_createTestFolder = GetStdoutFromCommand(createTestFolderCommand);

   // Creating Tests
  for(unsigned int i = 0;i < testsInputs.size();i++)
  { 
    // Retrieving current test to create
    string currentTestInput = testsInputs.at(i);
    string currentTestExpected = testsExpected.at(i);

    // Defining Test Folder
    string testFolder = "./Tests/test_" + std::to_string(i);
    string testFile = testFolder + "/" + "testInput" + ".txt";
    string testExpectedFile = testFolder + "/" + "testExpected" + ".txt";

    // Creating Current Test Files  
    string createTestsFilesCommand = "mkdir " + testFolder + " && touch " + testFile;
    string got_createTestsFilesCommand  = GetStdoutFromCommand(createTestsFilesCommand );

    // Creating Test Input
    std::ofstream outInput(testFile);
    outInput << currentTestInput + "\nquitXV6\n";
    outInput.close();

    // Creating Test Expected
    std::ofstream outExpected(testExpectedFile);
    outExpected << processCompareString(currentTestExpected);
    outExpected.close();
  }

  return testsInputs.size();
}

// Signal handler for SIGINT
void sigintHandler(int num){
    // Declaring execution should be aborted
    abortExecution = 1;
    
    // Catching signal
    signal(SIGINT,sigintHandler);
}

// Signal handler for SIGQUIT
void sigquitHandler(int num){
    // Catching signal
    signal(SIGQUIT,sigquitHandler);
}

// Processing test output
string processTestOutput(string output){
  // Serching for start of test code
  unsigned int inputStartPos = output.find("init: starting sh",0);

  // Returning test code
  if(inputStartPos < output.length() && inputStartPos >= 0){
      return processCompareString(output.substr(inputStartPos,output.length())); 
  }
  else{
      return output;
  }
}

// Processing compare string, i.e removing spaces from edges
string processCompareString(string str){
    // Initializing
    int start = -1;
    int end = -1;

    // Retrieving location of first space from start
    for(unsigned int i = 0;i < str.length();i++){
      if(str.at(i) > 32){
        start = i;
        break;
      }
    }

    // Retrieving location of first space from end
    for(unsigned int i = str.length() - 1;i >= 0;i--){
      if(str.at(i) > 32){
        end = i;
        break;
      }
    }

    // Asserting there are spaces at the edegs and if so removing them
    if(start == -1 || end == -1){
      return str;
    }
    else{
      return str.substr(start,end - start + 1);
    }

}

// Creating XV6 Tests Makefile
void createXV6_TestMakefile(string makefilePath,vector<string> userspacePrograms,vector<string> defaultUserspacePrograms){
    // Initializing
    string data;
    FILE * stream = fopen("../Makefile","r");
    const int max_buffer = 4000;
    char buffer[max_buffer];
    string xv6TestsBaseFolder = "XV6_Tests/";
    string xv6TestsQEMUFolder = "./Project_Test/" + xv6TestsBaseFolder;

    // Reading project makefile and adding tests user space programs
    // while code is for telling the makefile to include these user space programs
    while (!feof(stream))
    { 
      // Reading line of test output
      if (fgets(buffer, max_buffer, stream) != NULL){
            if(strstr(buffer,"UPROGS=\\")){
              data.append(buffer);
              eraseUserPrograms(data, stream);
              data.append(processAppendMakefileUPROGS(userspacePrograms));
              data.append(processAppendMakefileUPROGS(defaultUserspacePrograms));
              data.append("\n");
            }
            else{
              data.append(buffer);
            }
      }
     
    }

    // Adding build commands for each user space program
    addUserProgramsBuildCommands(data, userspacePrograms, xv6TestsQEMUFolder);
    addUserProgramsBuildCommands(data, defaultUserspacePrograms, "");
    
    // Creating Tests Makefile
    std::ofstream outMakefile(makefilePath);
    outMakefile << data;
    outMakefile.close();
}

// Processing user space programs and creating an entry for each one 
// inorder to take the makefile of the xv6 to include them
string processAppendMakefileUPROGS(vector<string> append){
    // Initializinh
    string result;

    // Creating entries
    for (vector<string>::iterator it = append.begin() ; it != append.end(); ++it){
      result.append("\t_" + *it + "\\\n");
    }

    return result;
}

// Erasing user space programs
void eraseUserPrograms(string &data, FILE * stream){
    // Initializing
    const int max_buffer = 4000;
    char buffer[max_buffer];

     // Erasing user space programs
     while (!feof(stream))
    {  
        // Reading line from stream and asserting if its a user program
      if (fgets(buffer, max_buffer, stream) != NULL){
            // If its not a user program, appending to buffer and exiting
            if(!(strstr(buffer,"\\") && strstr(buffer,"\n"))){
                break;
            }
      }
    }
}

// Adding build command for user programs
void addUserProgramsBuildCommands(string &data, vector<string> &userspacePrograms, string folder){
    // Initializing
    string userSpaceProgramMakeCode =  
    "_%: $(ULIB)\n" 
        "\tgcc -Werror -fno-pic -static -fno-builtin -fno-strict-aliasing -O2 -Wall -MD -ggdb -m32 -fno-omit-frame-pointer -fno-stack-protector -fno-pie -no-pie -c -o %.o #.c\n"
        "\tld -m elf_i386 -N -e main -Ttext 0 -o _% %.o $(ULIB)\n" 
        "\tobjdump -S _% > %.asm\n" 
        "\t$(OBJDUMP) -t _% | sed '1,/SYMBOL TABLE/d; s/ .* / /; /^$$/d' > %.sym\n";

    // Adding build command for user programs
    for (vector<string>::iterator it = userspacePrograms.begin() ; it != userspacePrograms.end(); ++it){
      string temp = replaceInString(userSpaceProgramMakeCode,'%',*it) + "\n";
      string temp2 = replaceInString(temp,'#',folder + *it);
      data.append(temp2);
    }
}

// Replacing all occurences of toReplace char with replaceWith string in str
string replaceInString(string str,char toReplace,string replaceWith){
    // Initializing
    string result;

    // Replacing
    for (string::iterator it=str.begin(); it!=str.end(); ++it){
        if(*it == toReplace){
          result.append(replaceWith);
        }
        else{
          result.append(1,*it);
        }
    }

    return result;
}

// Finding number of occurences of substr in string
int countSubStr(string str,string findSubStr){
    // Initializing
    int occurrences = 0;
    string::size_type pos = 0;

    // Counting
    while ((pos = str.find(findSubStr, pos)) != std::string::npos) {
          ++occurrences;
          pos += findSubStr.length();
    }
   
   return occurrences;
}

// Vincenzo Pii code
// Splitting a string 
vector<string> splitString(string theString, string delimiter){
  // Initializing
  size_t pos = 0;
  string token;
  vector<string> result;

  // Copying string to not corrupt original
  string s(theString);

  // Retrieving string tokens(substrings splitted by delimiters)
  while ((pos = s.find(delimiter)) != std::string::npos) {
      // Retrieving string token
      token = s.substr(0, pos);

      // Adding token to result
      result.push_back(token);

      // Erasing token from string
      s.erase(0, pos + delimiter.length());
  }

  // Adding last token to result
  result.push_back(s);

  return result;
}

// Executing Operating_System_Test
void Operating_System_Test()
{
  // Initializing
  currentTestName = "Operating_System_Test";
  abortExecution = 0;
  char arr[50];
  memset(arr,' ',50);
  arr[50] = 0;
  int progress_index = 0;
  int progress;
  const char* no_error_progress = "\r\e[38;5;082m[%s]\e[38;5;226m%i%% %d/%d\r\e[0m";
  const char* yes_error_progress = "\r\e[38;5;082m[%s]\e[38;5;196m%i%% %d/%d\r\e[0m";


  // Initializing Sub Tests
  InitializeOperatingSystemTestSubTests();

  // Creating Tests
  unsigned int numberOfTests = CreateTests();
  
  // Running specific test if demanded
  if(0 <=  testToExecute && ((unsigned int)testToExecute) < numberOfTests){
      runSpecificTest(testToExecute);
      return;
  }
  else if(testToExecute != -1){
      printf("Specific test request was out of bounds(%d)\n\n",testToExecute);
  }

  // Printing initial progress
  printf(no_error_progress,arr,0,0,numberOfTests);
  fflush(stdout);

  // Testing
  for(unsigned int i = 0;i < numberOfTests;i++)
  { 
    // Testing
    if(abortExecution == 0){
      procceseTest("test_" + std::to_string(i),i);
    }
    else{
      // Declaring test was aborted
      cout << RED << std::endl << "Operating System Test Was Aborted With " << i << " Tests Executed Out Of " << numberOfTests << " !!!" << RESET << std::endl;
      red = red + (numberOfTests - i);
      break;
    }

    float float_index = (float)(i + 1);
    progress = (float_index/numberOfTests) * 100;

    // Updating progress 
    if(progress > progress_index)
    { 
      progress_index += 1;
      memset(arr,'#',(int)((float_index/numberOfTests) * 50));
    }
    
    if(red == 0){
      printf(no_error_progress,arr,progress,i+1,numberOfTests);
    }
    else{
      printf(yes_error_progress,arr,progress,i+1,numberOfTests);
    }
    fflush(stdout);
  }
  
  // Cleaning after progress bar
  printf("\r                                                                                   \r");

  // Cleaning after test
  string clean_command = "cd .. && make clean";
  string got_clean_command = GetStdoutFromCommand(clean_command);  
}
