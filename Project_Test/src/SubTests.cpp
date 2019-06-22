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

using std::string;
using std::vector;
using std::streambuf;
using std::istringstream;
using std::to_string;
using std::cout;
using std::sprintf;
using std::ifstream;
using std::stringstream;

// Defining Global Variables
vector<string> testsInputs;
vector<string> testsExpected;
vector<vector<string>> testsInteractiveExpect;
vector<vector<string>> testsInteractiveSend;
vector<string> testsExecuteCommandArgs;
vector<vector<string>> testsUserPrograms;
vector<vector<string>> testsDefaultUserPrograms;
vector<string> testsHints;
vector<int> tesTimeLimits;

// Initializing sub tests for Operating System Test
void InitializeOperatingSystemTestSubTests(){
    // Defining tests
    string test_0_Input = R"V0G0N(
OforktestO
    )V0G0N";
    string test_0_Expected = R"V0G0N(
init: starting sh
$ fork test
fork test OK
$ $ Finished Yehonatan Peleg Test, quiting...
)V0G0N";
    vector<string> test_0_InteractiveExpect = {};
    vector<string> test_0_InteractiveSend = {};
    string test_0_ExecuteCommandArgs = "";
    vector<string> test_0_UserPrograms = {"quitXV6","OforktestO"};
    vector<string> test_0_DefaultUserPrograms = {"sh", "init","ls", "echo", "cat"};
    string test_0_Hint = "General problem with xv6 due to changes made to it.";
    int test_0_time_limit = 240000;

    string test_1_Input = R"V0G0N(
OusertestsO
)V0G0N";
    string test_1_Expected = "#ALL TESTS PASSED"; 
    vector<string> test_1_InteractiveExpect = {};
    vector<string> test_1_InteractiveSend = {};
    string test_1_ExecuteCommandArgs = "";
    vector<string> test_1_UserPrograms = {"quitXV6","OusertestsO"};
    vector<string> test_1_DefaultUserPrograms = {"sh", "init","ls", "echo", "cat"};
    string test_1_Hint = "General problem with xv6 due to changes made to it."; 
    int test_1_time_limit = 1800000;

    string test_2_Input = R"V0G0N(
generalcheck1
)V0G0N";
    string test_2_Expected = "@\n1\ngeneralcheck1 test starting...\n1\ngeneralcheck1 test exiting...\n1\nideinfo\n1\nfilestat\n1\ninodeinfo"
                             "\n0\nerror reading\n0\nerror writing"
                             "\n0\nls: cannot open\n0\nls: cannot stat\n0\nls: path too long\n0\nfork failed\n0\ncannot stat"
                             "\n0\nnot a device file"; 
    vector<string> test_2_InteractiveExpect = {};
    vector<string> test_2_InteractiveSend = {};
    string test_2_ExecuteCommandArgs = "";
    vector<string> test_2_UserPrograms = {"quitXV6","generalcheck1"};
    vector<string> test_2_DefaultUserPrograms = {"sh", "init","ls", "echo", "cat"};
    string test_2_Hint = "opening and reading /proc"; 
    int test_2_time_limit = 240000;

    string test_3_Input = R"V0G0N(
generalcheck2
)V0G0N";
    string test_3_Expected = "@\n1\ngeneralcheck2 test starting...\n1\ngeneralcheck2 test exiting...\n0\nerror reading\n0\nerror writing"
                             "\n0\nls: cannot open\n0\nls: cannot stat\n0\nls: path too long\n0\nfork failed\n0\ncannot stat"
                             "\n0\nnot a device file"; 
    vector<string> test_3_InteractiveExpect = {};
    vector<string> test_3_InteractiveSend = {};
    string test_3_ExecuteCommandArgs = "";
    vector<string> test_3_UserPrograms = {"quitXV6","generalcheck2"};
    vector<string> test_3_DefaultUserPrograms = {"sh", "init","ls", "echo", "cat"};
    string test_3_Hint = "opening and reading /proc/ideinfo"; 
    int test_3_time_limit = 240000;

    string test_4_Input = R"V0G0N(
generalcheck3
)V0G0N";
    string test_4_Expected = "@\n1\ngeneralcheck3 test starting...\n1\ngeneralcheck3 test exiting...\n0\nerror reading\n0\nerror writing"
                             "\n0\nls: cannot open\n0\nls: cannot stat\n0\nls: path too long\n0\nfork failed\n0\ncannot stat"
                             "\n0\nnot a device file";
    vector<string> test_4_InteractiveExpect = {};
    vector<string> test_4_InteractiveSend = {};
    string test_4_ExecuteCommandArgs = "";
    vector<string> test_4_UserPrograms = {"quitXV6","generalcheck3"};
    vector<string> test_4_DefaultUserPrograms = {"sh", "init","ls", "echo", "cat"};
    string test_4_Hint = "opening and reading /proc/ideinfo"; 
    int test_4_time_limit = 600000;

    string test_5_Input = R"V0G0N(
generalcheck4
)V0G0N";
    string test_5_Expected = "@\n1\ngeneralcheck4 test starting...\n1\ngeneralcheck4 test exiting...\n0\nerror reading\n0\nerror writing"
                             "\n0\nls: cannot open\n0\nls: cannot stat\n0\nls: path too long\n0\nfork failed\n0\ncannot stat"
                             "\n0\nnot a device file";
    vector<string> test_5_InteractiveExpect = {};
    vector<string> test_5_InteractiveSend = {};
    string test_5_ExecuteCommandArgs = "";
    vector<string> test_5_UserPrograms = {"quitXV6","generalcheck4"};
    vector<string> test_5_DefaultUserPrograms = {"sh", "init","ls", "echo", "cat"};
    string test_5_Hint = "opening and reading /proc/filestat"; 
    int test_5_time_limit = 240000;

    string test_6_Input = R"V0G0N(
generalcheck5
)V0G0N";
    string test_6_Expected = "@\n1\ngeneralcheck5 test starting...\n1\ngeneralcheck5 test exiting...\n0\nerror reading\n0\nerror writing" 
                             "\n0\nls: cannot open\n0\nls: cannot stat\n0\nls: path too long\n0\nfork failed\n0\ncannot stat"
                             "\n0\nnot a device file";
    vector<string> test_6_InteractiveExpect = {};
    vector<string> test_6_InteractiveSend = {};
    string test_6_ExecuteCommandArgs = "";
    vector<string> test_6_UserPrograms = {"quitXV6","generalcheck5"};
    vector<string> test_6_DefaultUserPrograms = {"sh", "init","ls", "echo", "cat"};
    string test_6_Hint = "opening and reading /proc/filestat"; 
    int test_6_time_limit = 600000;

    string test_7_Input = R"V0G0N(
generalcheck6
)V0G0N";
    string test_7_Expected = "@\n1\ngeneralcheck6 test starting...\n1\ngeneralcheck6 test exiting...\n0\nerror reading\n0\nerror writing" 
                             "\n0\nls: cannot open\n0\nls: cannot stat\n0\nls: path too long\n0\nfork failed\n0\ncannot stat"
                             "\n0\nnot a device file";
    vector<string> test_7_InteractiveExpect = {};
    vector<string> test_7_InteractiveSend = {};
    string test_7_ExecuteCommandArgs = "";
    vector<string> test_7_UserPrograms = {"quitXV6","generalcheck6"};
    vector<string> test_7_DefaultUserPrograms = {"sh", "init","ls", "echo", "cat"};
    string test_7_Hint = "opening and reading /proc/inodeinfo"; 
    int test_7_time_limit = 240000;

    string test_8_Input = R"V0G0N(
generalcheck7
)V0G0N";
    string test_8_Expected = "@\n1\ngeneralcheck7 test starting...\n1\ngeneralcheck7 test exiting...\n0\nerror reading\n0\nerror writing" 
                             "\n0\nls: cannot open\n0\nls: cannot stat\n0\nls: path too long\n0\nfork failed\n0\ncannot stat"
                             "\n0\nnot a device file";
    vector<string> test_8_InteractiveExpect = {};
    vector<string> test_8_InteractiveSend = {};
    string test_8_ExecuteCommandArgs = "";
    vector<string> test_8_UserPrograms = {"quitXV6","generalcheck7"};
    vector<string> test_8_DefaultUserPrograms = {"sh", "init","ls", "echo", "cat"};
    string test_8_Hint = "opening and reading /proc/inodeinfo"; 
    int test_8_time_limit = 600000;

    string test_9_Input = R"V0G0N(
generalcheck8
)V0G0N";
    string test_9_Expected = "@\n1\ngeneralcheck8 test starting...\n1\ngeneralcheck8 test exiting...\n0\nerror reading\n0\nerror writing" 
                             "\n0\nls: cannot open\n0\nls: cannot stat\n0\nls: path too long\n0\nfork failed\n0\ncannot stat"
                             "\n0\nnot a device file";
    vector<string> test_9_InteractiveExpect = {};
    vector<string> test_9_InteractiveSend = {};
    string test_9_ExecuteCommandArgs = "";
    vector<string> test_9_UserPrograms = {"quitXV6","generalcheck8"};
    vector<string> test_9_DefaultUserPrograms = {"sh", "init","ls", "echo", "cat"};
    string test_9_Hint = "opening and reading /proc/inodeinfo dir files"; 
    int test_9_time_limit = 240000;

    string test_10_Input = R"V0G0N(
generalcheck9
)V0G0N";
    string test_10_Expected = "@\n1\ngeneralcheck9 test starting...\n1\ngeneralcheck9 test exiting...\n0\nerror reading\n0\nerror writing" 
                              "\n0\nls: cannot open\n0\nls: cannot stat\n0\nls: path too long\n0\nfork failed\n0\ncannot stat"
                              "\n0\nnot a device file";
    vector<string> test_10_InteractiveExpect = {};
    vector<string> test_10_InteractiveSend = {};
    string test_10_ExecuteCommandArgs = "";
    vector<string> test_10_UserPrograms = {"quitXV6","generalcheck9"};
    vector<string> test_10_DefaultUserPrograms = {"sh", "init","ls", "echo", "cat"};
    string test_10_Hint = "opening and reading /proc/inodeinfo dir files"; 
    int test_10_time_limit = 600000;

    string test_11_Input = R"V0G0N(
generalcheck10
)V0G0N";
    string test_11_Expected = "@\n1\ngeneralcheck10 test starting...\n1\ngeneralcheck10 test exiting...\n0\nerror reading\n0\nerror writing" 
                              "\n0\nls: cannot open\n0\nls: cannot stat\n0\nls: path too long\n0\nfork failed\n0\ncannot stat"
                              "\n0\nnot a device file\n1\nname\n1\nstatus";
    vector<string> test_11_InteractiveExpect = {};
    vector<string> test_11_InteractiveSend = {};
    string test_11_ExecuteCommandArgs = "";
    vector<string> test_11_UserPrograms = {"quitXV6","generalcheck10"};
    vector<string> test_11_DefaultUserPrograms = {"sh", "init","ls", "echo", "cat"};
    string test_11_Hint = "opening and reading /proc/pid"; 
    int test_11_time_limit = 240000;

    string test_12_Input = R"V0G0N(
generalcheck11
)V0G0N";
    string test_12_Expected = "@\n1\ngeneralcheck11 test starting...\n1\ngeneralcheck11 test exiting...\n0\nerror reading\n0\nerror writing" 
                              "\n0\nls: cannot open\n0\nls: cannot stat\n0\nls: path too long\n0\nfork failed\n0\ncannot stat"
                              "\n0\nnot a device file";
    vector<string> test_12_InteractiveExpect = {};
    vector<string> test_12_InteractiveSend = {};
    string test_12_ExecuteCommandArgs = "";
    vector<string> test_12_UserPrograms = {"quitXV6","generalcheck11"};
    vector<string> test_12_DefaultUserPrograms = {"sh", "init","ls", "echo", "cat"};
    string test_12_Hint = "opening and reading /proc/pid"; 
    int test_12_time_limit = 600000;

    string test_13_Input = R"V0G0N(
generalcheck12
)V0G0N";
    string test_13_Expected = "@\n1\ngeneralcheck12 test starting...\n1\ngeneralcheck12 test exiting...\n0\nerror reading\n0\nerror writing" 
                              "\n0\nls: cannot open\n0\nls: cannot stat\n0\nls: path too long\n0\nfork failed\n0\ncannot stat"
                              "\n0\nnot a device file\n1\nname\n1\nstatus";
    vector<string> test_13_InteractiveExpect = {};
    vector<string> test_13_InteractiveSend = {};
    string test_13_ExecuteCommandArgs = "";
    vector<string> test_13_UserPrograms = {"quitXV6","generalcheck12"};
    vector<string> test_13_DefaultUserPrograms = {"sh", "init","ls", "echo", "cat"};
    string test_13_Hint = "opening and reading /proc/pid and its files"; 
    int test_13_time_limit = 240000;

    string test_14_Input = R"V0G0N(
generalcheck13
)V0G0N";
    string test_14_Expected = "@\n1\ngeneralcheck13 test starting...\n1\ngeneralcheck13 test exiting...\n0\nerror reading\n0\nerror writing" 
                              "\n0\nls: cannot open\n0\nls: cannot stat\n0\nls: path too long\n0\nfork failed\n0\ncannot stat"
                              "\n0\nnot a device file";
    vector<string> test_14_InteractiveExpect = {};
    vector<string> test_14_InteractiveSend = {};
    string test_14_ExecuteCommandArgs = "";
    vector<string> test_14_UserPrograms = {"quitXV6","generalcheck13"};
    vector<string> test_14_DefaultUserPrograms = {"sh", "init","ls", "echo", "cat"};
    string test_14_Hint = "opening and reading /proc/pid and its files"; 
    int test_14_time_limit = 600000;

    string test_15_Input = R"V0G0N(
generalcheck14
)V0G0N";
    string test_15_Expected = "@\n1\ngeneralcheck14 test starting...\n1\ngeneralcheck14 test exiting...\n0\nerror reading\n0\nerror writing" 
                              "\n0\nls: cannot open\n0\nls: cannot stat\n0\nls: path too long\n0\nfork failed\n0\ncannot stat"
                              "\n0\nnot a device file\n30\ndirAndFiles1\n30\ndirAndFiles2\n30\ndirAndFiles3\n30\n409600\n30\n"
                              "819200\n30\n1228800\n90\nname\n90\nstatus";
    vector<string> test_15_InteractiveExpect = {};
    vector<string> test_15_InteractiveSend = {};
    string test_15_ExecuteCommandArgs = "";
    vector<string> test_15_UserPrograms = {"quitXV6","generalcheck14","dirAndFiles1","dirAndFiles2","dirAndFiles3"};
    vector<string> test_15_DefaultUserPrograms = {"sh", "init","ls", "echo", "cat"};
    string test_15_Hint = "opening and reading /proc/pid and its files"; 
    int test_15_time_limit = 600000;

    string test_16_Input = R"V0G0N(
generalcheck15
)V0G0N";
    string test_16_Expected = "@\n1\ngeneralcheck15 test starting...\n1\ngeneralcheck15 test exiting...\n0\nerror reading\n0\nerror writing" 
                              "\n0\nls: cannot open\n0\nls: cannot stat\n0\nls: path too long\n0\nfork failed\n0\ncannot stat"
                              "\n0\nnot a device file\n30\nname1\n30\nname2\n30\nname3\n0\n409600\n0\n"
                              "819200\n0\n1228800";
    vector<string> test_16_InteractiveExpect = {};
    vector<string> test_16_InteractiveSend = {};
    string test_16_ExecuteCommandArgs = "";
    vector<string> test_16_UserPrograms = {"quitXV6","generalcheck15","name1","name2","name3"};
    vector<string> test_16_DefaultUserPrograms = {"sh", "init","ls", "echo", "cat"};
    string test_16_Hint = "opening and reading /proc/pid and its files"; 
    int test_16_time_limit = 600000;

    string test_17_Input = R"V0G0N(
generalcheck16
)V0G0N";
    string test_17_Expected = "@\n1\ngeneralcheck16 test starting...\n1\ngeneralcheck16 test exiting...\n0\nerror reading\n0\nerror writing" 
                              "\n0\nls: cannot open\n0\nls: cannot stat\n0\nls: path too long\n0\nfork failed\n0\ncannot stat"
                              "\n0\nnot a device file\n0\nsize1\n0\nsize2\n0\nsize3\n30\n409600\n30\n"
                              "819200\n30\n1228800";
    vector<string> test_17_InteractiveExpect = {};
    vector<string> test_17_InteractiveSend = {};
    string test_17_ExecuteCommandArgs = "";
    vector<string> test_17_UserPrograms = {"quitXV6","generalcheck16","size1","size2","size3"};
    vector<string> test_17_DefaultUserPrograms = {"sh", "init","ls", "echo", "cat"};
    string test_17_Hint = "opening and reading /proc/pid and its files"; 
    int test_17_time_limit = 600000;

    string test_18_Input = R"V0G0N(
generalcheck17
)V0G0N";
    string test_18_Expected = "@\n1\ngeneralcheck17 test starting...\n1\ngeneralcheck17 test exiting...\n0\nerror reading\n0\nerror writing" 
                              "\n0\nls: cannot open\n0\nls: cannot stat\n0\nls: path too long\n0\nfork failed\n0\ncannot stat"
                              "\n0\nnot a device file\n400\nsleep\n0\nerror process file can be read after its has exited !!!"
                              "\n0\nerror process dir can be read after its has exited !!!\n400\nname\n400\nstatus";
    vector<string> test_18_InteractiveExpect = {};
    vector<string> test_18_InteractiveSend = {};
    string test_18_ExecuteCommandArgs = "";
    vector<string> test_18_UserPrograms = {"quitXV6","generalcheck17","sleep"};
    vector<string> test_18_DefaultUserPrograms = {"sh", "init","ls", "echo", "cat"};
    string test_18_Hint = "opening and reading /proc/pid and its files"; 
    int test_18_time_limit = 600000;
    
    string test_19_Input = R"V0G0N(
generalcheck18
)V0G0N";
    string test_19_Expected = "@\n1\ngeneralcheck18 test starting...\n1\ngeneralcheck18 test exiting...\n0\nerror reading\n0\nerror writing" 
                              "\n0\nls: cannot open\n0\nls: cannot stat\n0\nls: path too long\n0\nfork failed\n0\ncannot stat"
                              "\n0\nnot a device file\n1600\nsleep\n0\nerror process file can be read after its has exited !!!"
                              "\n0\nerror process dir can be read after its has exited !!!\n1600\nname\n1600\nstatus";
    vector<string> test_19_InteractiveExpect = {};
    vector<string> test_19_InteractiveSend = {};
    string test_19_ExecuteCommandArgs = "";
    vector<string> test_19_UserPrograms = {"quitXV6","generalcheck18","sleep"};
    vector<string> test_19_DefaultUserPrograms = {"sh", "init","ls", "echo", "cat"};
    string test_19_Hint = "opening and reading /proc/pid and its files"; 
    int test_19_time_limit = 600000;

    string test_20_Input = R"V0G0N(
generalcheck19
)V0G0N";
    string test_20_Expected = "@\n1\ngeneralcheck19 test starting...\n1\ngeneralcheck19 test exiting...\n0\nerror reading\n0\nerror writing" 
                              "\n0\nls: cannot open\n0\nls: cannot stat\n0\nls: path too long\n0\nfork failed\n0\ncannot stat"
                              "\n0\nnot a device file\n0\nerror in file type to int conversion: unkown file type"
                              "\n0\ncould not find open file in lsnd data";
    vector<string> test_20_InteractiveExpect = {};
    vector<string> test_20_InteractiveSend = {};
    string test_20_ExecuteCommandArgs = "";
    vector<string> test_20_UserPrograms = {"quitXV6","generalcheck19"};
    vector<string> test_20_DefaultUserPrograms = {"sh", "init","ls", "echo", "cat","mkdir","ln","lsnd"};
    string test_20_Hint = "using lsnd"; 
    int test_20_time_limit = 600000;

    string test_21_Input = R"V0G0N(
generalcheck20
)V0G0N";
    string test_21_Expected = "@\n1\ngeneralcheck20 test starting...\n1\ngeneralcheck20 test exiting...\n0\nerror reading\n0\nerror writing" 
                              "\n0\nls: cannot open\n0\nls: cannot stat\n0\nls: path too long\n0\nfork failed\n0\ncannot stat"
                              "\n0\nnot a device file\n0\nerror in file type to int conversion: unkown file type"
                              "\n0\ncould not find open file in lsnd data";
    vector<string> test_21_InteractiveExpect = {};
    vector<string> test_21_InteractiveSend = {};
    string test_21_ExecuteCommandArgs = "";
    vector<string> test_21_UserPrograms = {"quitXV6","generalcheck20"};
    vector<string> test_21_DefaultUserPrograms = {"sh", "init","ls", "echo", "cat","mkdir","ln","lsnd"};
    string test_21_Hint = "using lsnd"; 
    int test_21_time_limit = 600000;

    string test_22_Input = R"V0G0N(
generalcheck21
)V0G0N";
    string test_22_Expected = "@\n1\ngeneralcheck21 test starting...\n1\ngeneralcheck21 test exiting...\n0\nerror reading\n0\nerror writing" 
                              "\n0\nls: cannot open\n0\nls: cannot stat\n0\nls: path too long\n0\nfork failed\n0\ncannot stat"
                              "\n0\nnot a device file\n0\nerror in file type to int conversion: unkown file type"
                              "\n0\ncould not find open file in lsnd data";
    vector<string> test_22_InteractiveExpect = {};
    vector<string> test_22_InteractiveSend = {};
    string test_22_ExecuteCommandArgs = "";
    vector<string> test_22_UserPrograms = {"quitXV6","generalcheck21"};
    vector<string> test_22_DefaultUserPrograms = {"sh", "init","ls", "echo", "cat","mkdir","ln","lsnd"};
    string test_22_Hint = "using lsnd"; 
    int test_22_time_limit = 600000;

    string test_23_Input = R"V0G0N(
generalcheck22
)V0G0N";
    string test_23_Expected = "@\n1\ngeneralcheck22 test starting...\n1\ngeneralcheck22 test exiting...\n0\nerror reading\n0\nerror writing" 
                              "\n0\nls: cannot open\n0\nls: cannot stat\n0\nls: path too long\n0\nfork failed\n0\ncannot stat"
                              "\n0\nnot a device file\n0\nerror in file type to int conversion: unkown file type"
                              "\n0\ncould not find open file in lsnd data";
    vector<string> test_23_InteractiveExpect = {};
    vector<string> test_23_InteractiveSend = {};
    string test_23_ExecuteCommandArgs = "";
    vector<string> test_23_UserPrograms = {"quitXV6","generalcheck22"};
    vector<string> test_23_DefaultUserPrograms = {"sh", "init","ls", "echo", "cat","mkdir","ln","lsnd"};
    string test_23_Hint = "using lsnd"; 
    int test_23_time_limit = 600000;

    string test_24_Input = R"V0G0N(
generalcheck23
)V0G0N";
    string test_24_Expected = "@\n1\ngeneralcheck23 test starting...\n1\ngeneralcheck23 test exiting...\n0\nerror reading\n0\nerror writing" 
                              "\n0\nls: cannot open\n0\nls: cannot stat\n0\nls: path too long\n0\nfork failed\n0\ncannot stat"
                              "\n0\nnot a device file\n0\nerror in file type to int conversion: unkown file type"
                              "\n0\ncould not find open file in lsnd data";
    vector<string> test_24_InteractiveExpect = {};
    vector<string> test_24_InteractiveSend = {};
    string test_24_ExecuteCommandArgs = "";
    vector<string> test_24_UserPrograms = {"quitXV6","generalcheck23"};
    vector<string> test_24_DefaultUserPrograms = {"sh", "init","ls", "echo", "cat","mkdir","ln","lsnd"};
    string test_24_Hint = "using lsnd"; 
    int test_24_time_limit = 600000;

    string test_25_Input = R"V0G0N(
generalcheck24
)V0G0N";
    string test_25_Expected = "@\n1\ngeneralcheck24 test starting...\n1\ngeneralcheck24 test exiting...\n0\nerror reading\n0\nerror writing" 
                              "\n0\nls: cannot open\n0\nls: cannot stat\n0\nls: path too long\n0\nfork failed\n0\ncannot stat"
                              "\n0\nnot a device file\n0\nerror in file type to int conversion: unkown file type"
                              "\n0\ncould not find open file in lsnd data";
    vector<string> test_25_InteractiveExpect = {};
    vector<string> test_25_InteractiveSend = {};
    string test_25_ExecuteCommandArgs = "";
    vector<string> test_25_UserPrograms = {"quitXV6","generalcheck24"};
    vector<string> test_25_DefaultUserPrograms = {"sh", "init","ls", "echo", "cat","mkdir","ln","lsnd"};
    string test_25_Hint = "using lsnd"; 
    int test_25_time_limit = 600000;

    string test_26_Input = R"V0G0N(
generalcheck25
)V0G0N";
    string test_26_Expected = "@\n1\ngeneralcheck25 test starting...\n1\ngeneralcheck25 test exiting...\n0\nerror reading\n0\nerror writing" 
                              "\n0\nls: cannot open\n0\nls: cannot stat\n0\nls: path too long\n0\nfork failed\n0\ncannot stat"
                              "\n0\nnot a device file\n0\nerror in file type to int conversion: unkown file type"
                              "\n0\ncould not find open file in lsnd data";
    vector<string> test_26_InteractiveExpect = {};
    vector<string> test_26_InteractiveSend = {};
    string test_26_ExecuteCommandArgs = "";
    vector<string> test_26_UserPrograms = {"quitXV6","generalcheck25"};
    vector<string> test_26_DefaultUserPrograms = {"sh", "init","ls", "echo", "cat","mkdir","ln","lsnd"};
    string test_26_Hint = "using lsnd"; 
    int test_26_time_limit = 600000;

    string test_27_Input = R"V0G0N(
generalcheck26
)V0G0N";
    string test_27_Expected = "@\n1\ngeneralcheck26 test starting...\n1\ngeneralcheck26 test exiting...\n0\nerror reading\n0\nerror writing" 
                              "\n0\nls: cannot open\n0\nls: cannot stat\n0\nls: path too long\n0\nfork failed\n0\ncannot stat"
                              "\n0\nnot a device file";
    vector<string> test_27_InteractiveExpect = {};
    vector<string> test_27_InteractiveSend = {};
    string test_27_ExecuteCommandArgs = "";
    vector<string> test_27_UserPrograms = {"quitXV6","generalcheck26"};
    vector<string> test_27_DefaultUserPrograms = {"sh", "init","ls", "echo", "cat"};
    string test_27_Hint = "trying to write to procfs files"; 
    int test_27_time_limit = 240000;

    string test_28_Input = R"V0G0N(
generalcheck27
)V0G0N";
    string test_28_Expected = "@\n1\ngeneralcheck27 test starting...\n1\ngeneralcheck27 test exiting...\n0\nerror reading\n0\nerror writing" 
                              "\n0\nls: cannot open\n0\nls: cannot stat\n0\nls: path too long\n0\nfork failed\n0\ncannot stat"
                              "\n0\nnot a device file";
    vector<string> test_28_InteractiveExpect = {};
    vector<string> test_28_InteractiveSend = {};
    string test_28_ExecuteCommandArgs = "";
    vector<string> test_28_UserPrograms = {"quitXV6","generalcheck27"};
    vector<string> test_28_DefaultUserPrograms = {"sh", "init","ls", "echo", "cat"};
    string test_28_Hint = "trying to write to procfs files"; 
    int test_28_time_limit = 240000;

    string test_29_Input = R"V0G0N(
generalcheck28
)V0G0N";
    string test_29_Expected = "@\n1\ngeneralcheck28 test starting...\n1\ngeneralcheck28 test exiting...\n0\nerror reading\n0\nerror writing" 
                              "\n0\nls: cannot open\n0\nls: cannot stat\n0\nls: path too long\n0\nfork failed\n0\ncannot stat"
                              "\n0\nnot a device file";
    vector<string> test_29_InteractiveExpect = {};
    vector<string> test_29_InteractiveSend = {};
    string test_29_ExecuteCommandArgs = "";
    vector<string> test_29_UserPrograms = {"quitXV6","generalcheck28"};
    vector<string> test_29_DefaultUserPrograms = {"sh", "init","ls", "echo", "cat"};
    string test_29_Hint = "trying to write to procfs files"; 
    int test_29_time_limit = 240000;

    string test_30_Input = R"V0G0N(
generalcheck29
)V0G0N";
    string test_30_Expected = "@\n1\ngeneralcheck29 test starting...\n1\ngeneralcheck29 test exiting...\n0\nerror reading\n0\nerror writing" 
                              "\n0\nls: cannot open\n0\nls: cannot stat\n0\nls: path too long\n0\nfork failed\n0\ncannot stat"
                              "\n0\nnot a device file\n0\nerror in file type to int conversion: unkown file type"
                              "\n0\ncould not find open file in lsnd data";
    vector<string> test_30_InteractiveExpect = {};
    vector<string> test_30_InteractiveSend = {};
    string test_30_ExecuteCommandArgs = "";
    vector<string> test_30_UserPrograms = {"quitXV6","generalcheck29"};
    vector<string> test_30_DefaultUserPrograms = {"sh", "init","ls", "echo", "cat","mkdir","ln","lsnd"};
    string test_30_Hint = "using lsnd"; 
    int test_30_time_limit = 600000;

    string test_31_Input = R"V0G0N(
generalcheck30
)V0G0N";
    string test_31_Expected = "@\n1\ngeneralcheck30 test starting...\n1\ngeneralcheck30 test exiting...\n0\nerror reading\n0\nerror writing" 
                              "\n0\nls: cannot open\n0\nls: cannot stat\n0\nls: path too long\n0\nfork failed\n0\ncannot stat"
                              "\n0\nnot a device file\n0\nerror in file type to int conversion: unkown file type"
                              "\n0\ncould not find open file in lsnd data";
    vector<string> test_31_InteractiveExpect = {};
    vector<string> test_31_InteractiveSend = {};
    string test_31_ExecuteCommandArgs = "";
    vector<string> test_31_UserPrograms = {"quitXV6","generalcheck30"};
    vector<string> test_31_DefaultUserPrograms = {"sh", "init","ls", "echo", "cat","mkdir","ln","lsnd"};
    string test_31_Hint = "using lsnd"; 
    int test_31_time_limit = 600000;

    string test_32_Input = R"V0G0N(
generalcheck31
)V0G0N";
    string test_32_Expected = "@\n1\ngeneralcheck31 test starting...\n1\ngeneralcheck31 test exiting...\n0\nerror reading\n0\nerror writing" 
                              "\n0\nls: cannot open\n0\nls: cannot stat\n0\nls: path too long\n0\nfork failed\n0\ncannot stat"
                              "\n0\nnot a device file\n0\nerror in file type to int conversion: unkown file type"
                              "\n0\ncould not find open file in lsnd data";
    vector<string> test_32_InteractiveExpect = {};
    vector<string> test_32_InteractiveSend = {};
    string test_32_ExecuteCommandArgs = "";
    vector<string> test_32_UserPrograms = {"quitXV6","generalcheck31"};
    vector<string> test_32_DefaultUserPrograms = {"sh", "init","ls", "echo", "cat","mkdir","ln","lsnd"};
    string test_32_Hint = "using lsnd"; 
    int test_32_time_limit = 600000;
    
    string test_33_Input = R"V0G0N(
generalcheck32
)V0G0N";
    string test_33_Expected = "@\n1\ngeneralcheck32 test starting...\n1\ngeneralcheck32 test exiting...\n1\nideinfo\n1\nfilestat\n1\ninodeinfo"
                             "\n0\nerror reading\n0\nerror writing"
                             "\n0\nls: cannot open\n0\nls: cannot stat\n0\nls: path too long\n0\nfork failed\n0\ncannot stat"
                             "\n0\nnot a device file"; 
    vector<string> test_33_InteractiveExpect = {};
    vector<string> test_33_InteractiveSend = {};
    string test_33_ExecuteCommandArgs = "";
    vector<string> test_33_UserPrograms = {"quitXV6","generalcheck32"};
    vector<string> test_33_DefaultUserPrograms = {"sh", "init","ls", "echo", "cat"};
    string test_33_Hint = "using '.' and '..' in procfs"; 
    int test_33_time_limit = 240000;

    string test_34_Input = R"V0G0N(
generalcheck33
)V0G0N";
    string test_34_Expected = "@\n1\ngeneralcheck33 test starting...\n1\ngeneralcheck33 test exiting...\n1\nideinfo\n1\nfilestat\n1\ninodeinfo"
                             "\n0\nerror reading\n0\nerror writing"
                             "\n0\nls: cannot open\n0\nls: cannot stat\n0\nls: path too long\n0\nfork failed\n0\ncannot stat"
                             "\n0\nnot a device file"; 
    vector<string> test_34_InteractiveExpect = {};
    vector<string> test_34_InteractiveSend = {};
    string test_34_ExecuteCommandArgs = "";
    vector<string> test_34_UserPrograms = {"quitXV6","generalcheck33"};
    vector<string> test_34_DefaultUserPrograms = {"sh", "init","ls", "echo", "cat"};
    string test_34_Hint = "using '.' and '..' in procfs";
    int test_34_time_limit = 240000;

    string test_35_Input = R"V0G0N(
generalcheck34
)V0G0N";
    string test_35_Expected = "@\n1\ngeneralcheck34 test starting...\n1\ngeneralcheck34 test exiting...\n1\nideinfo\n1\nfilestat\n1\ninodeinfo"
                             "\n0\nerror reading\n0\nerror writing"
                             "\n0\nls: cannot open\n0\nls: cannot stat\n0\nls: path too long\n0\nfork failed\n0\ncannot stat"
                             "\n0\nnot a device file"; 
    vector<string> test_35_InteractiveExpect = {};
    vector<string> test_35_InteractiveSend = {};
    string test_35_ExecuteCommandArgs = "";
    vector<string> test_35_UserPrograms = {"quitXV6","generalcheck34"};
    vector<string> test_35_DefaultUserPrograms = {"sh", "init","ls", "echo", "cat"};
    string test_35_Hint = "using '.' and '..' in procfs";
    int test_35_time_limit = 240000;

    string test_36_Input = R"V0G0N(
generalcheck35
)V0G0N";
    string test_36_Expected = "@\n1\ngeneralcheck35 test starting...\n1\ngeneralcheck35 test exiting...\n1\nproc\n1\necho\n1\nls\n1\nconsole"
                             "\n0\nerror reading\n0\nerror writing"
                             "\n0\nls: cannot open\n0\nls: cannot stat\n0\nls: path too long\n0\nfork failed\n0\ncannot stat"
                             "\n0\nnot a device file"; 
    vector<string> test_36_InteractiveExpect = {};
    vector<string> test_36_InteractiveSend = {};
    string test_36_ExecuteCommandArgs = "";
    vector<string> test_36_UserPrograms = {"quitXV6","generalcheck35"};
    vector<string> test_36_DefaultUserPrograms = {"sh", "init","ls", "echo", "cat"};
    string test_36_Hint = "using '.' and '..' in procfs";
    int test_36_time_limit = 240000;

    string test_37_Input = R"V0G0N(
generalcheck36
)V0G0N";
    string test_37_Expected = "@\n1\ngeneralcheck36 test starting...\n1\ngeneralcheck36 test exiting...\n1\nproc\n1\necho\n1\nls\n1\nconsole"
                             "\n0\nerror reading\n0\nerror writing"
                             "\n0\nls: cannot open\n0\nls: cannot stat\n0\nls: path too long\n0\nfork failed\n0\ncannot stat"
                             "\n0\nnot a device file"; 
    vector<string> test_37_InteractiveExpect = {};
    vector<string> test_37_InteractiveSend = {};
    string test_37_ExecuteCommandArgs = "";
    vector<string> test_37_UserPrograms = {"quitXV6","generalcheck36"};
    vector<string> test_37_DefaultUserPrograms = {"sh", "init","ls", "echo", "cat"};
    string test_37_Hint = "using '.' and '..' in procfs";
    int test_37_time_limit = 240000;

    string test_38_Input = R"V0G0N(
generalcheck37
)V0G0N";
    string test_38_Expected = "@\n1\ngeneralcheck37 test starting...\n1\ngeneralcheck37 test exiting...\n1\nproc\n1\necho\n1\nls\n1\nconsole"
                             "\n0\nerror reading\n0\nerror writing"
                             "\n0\nls: cannot open\n0\nls: cannot stat\n0\nls: path too long\n0\nfork failed\n0\ncannot stat"
                             "\n0\nnot a device file"; 
    vector<string> test_38_InteractiveExpect = {};
    vector<string> test_38_InteractiveSend = {};
    string test_38_ExecuteCommandArgs = "";
    vector<string> test_38_UserPrograms = {"quitXV6","generalcheck37"};
    vector<string> test_38_DefaultUserPrograms = {"sh", "init","ls", "echo", "cat"};
    string test_38_Hint = "using '.' and '..' in procfs"; 
    int test_38_time_limit = 240000;

     // Adding Tests inputs and expected
    testsInputs.push_back(test_0_Input);
    testsExpected.push_back(test_0_Expected);
    testsInteractiveExpect.push_back(test_0_InteractiveExpect);
    testsInteractiveSend.push_back(test_0_InteractiveSend);
    testsExecuteCommandArgs.push_back(test_0_ExecuteCommandArgs);
    testsUserPrograms.push_back(test_0_UserPrograms);
    testsDefaultUserPrograms.push_back(test_0_DefaultUserPrograms);
    testsHints.push_back(test_0_Hint);
    tesTimeLimits.push_back(test_0_time_limit);

    testsInputs.push_back(test_1_Input);
    testsExpected.push_back(test_1_Expected);
    testsInteractiveExpect.push_back(test_1_InteractiveExpect);
    testsInteractiveSend.push_back(test_1_InteractiveSend);
    testsExecuteCommandArgs.push_back(test_1_ExecuteCommandArgs);
    testsUserPrograms.push_back(test_1_UserPrograms);
    testsDefaultUserPrograms.push_back(test_1_DefaultUserPrograms);
    testsHints.push_back(test_1_Hint);
    tesTimeLimits.push_back(test_1_time_limit);

    testsInputs.push_back(test_2_Input);
    testsExpected.push_back(test_2_Expected);
    testsInteractiveExpect.push_back(test_2_InteractiveExpect);
    testsInteractiveSend.push_back(test_2_InteractiveSend);
    testsExecuteCommandArgs.push_back(test_2_ExecuteCommandArgs);
    testsUserPrograms.push_back(test_2_UserPrograms);
    testsDefaultUserPrograms.push_back(test_2_DefaultUserPrograms);
    testsHints.push_back(test_2_Hint);
    tesTimeLimits.push_back(test_2_time_limit);

    testsInputs.push_back(test_3_Input);
    testsExpected.push_back(test_3_Expected);
    testsInteractiveExpect.push_back(test_3_InteractiveExpect);
    testsInteractiveSend.push_back(test_3_InteractiveSend);
    testsExecuteCommandArgs.push_back(test_3_ExecuteCommandArgs);
    testsUserPrograms.push_back(test_3_UserPrograms);
    testsDefaultUserPrograms.push_back(test_3_DefaultUserPrograms);
    testsHints.push_back(test_3_Hint);
    tesTimeLimits.push_back(test_3_time_limit);

    testsInputs.push_back(test_4_Input);
    testsExpected.push_back(test_4_Expected);
    testsInteractiveExpect.push_back(test_4_InteractiveExpect);
    testsInteractiveSend.push_back(test_4_InteractiveSend);
    testsExecuteCommandArgs.push_back(test_4_ExecuteCommandArgs);
    testsUserPrograms.push_back(test_4_UserPrograms);
    testsDefaultUserPrograms.push_back(test_4_DefaultUserPrograms);
    testsHints.push_back(test_4_Hint);
    tesTimeLimits.push_back(test_4_time_limit);

    testsInputs.push_back(test_5_Input);
    testsExpected.push_back(test_5_Expected);
    testsInteractiveExpect.push_back(test_5_InteractiveExpect);
    testsInteractiveSend.push_back(test_5_InteractiveSend);
    testsExecuteCommandArgs.push_back(test_5_ExecuteCommandArgs);
    testsUserPrograms.push_back(test_5_UserPrograms);
    testsDefaultUserPrograms.push_back(test_5_DefaultUserPrograms);
    testsHints.push_back(test_5_Hint);
    tesTimeLimits.push_back(test_5_time_limit);

    testsInputs.push_back(test_6_Input);
    testsExpected.push_back(test_6_Expected);
    testsInteractiveExpect.push_back(test_6_InteractiveExpect);
    testsInteractiveSend.push_back(test_6_InteractiveSend);
    testsExecuteCommandArgs.push_back(test_6_ExecuteCommandArgs);
    testsUserPrograms.push_back(test_6_UserPrograms);
    testsDefaultUserPrograms.push_back(test_6_DefaultUserPrograms);
    testsHints.push_back(test_6_Hint);
    tesTimeLimits.push_back(test_6_time_limit);

    testsInputs.push_back(test_7_Input);
    testsExpected.push_back(test_7_Expected);
    testsInteractiveExpect.push_back(test_7_InteractiveExpect);
    testsInteractiveSend.push_back(test_7_InteractiveSend);
    testsExecuteCommandArgs.push_back(test_7_ExecuteCommandArgs);
    testsUserPrograms.push_back(test_7_UserPrograms);
    testsDefaultUserPrograms.push_back(test_7_DefaultUserPrograms);
    testsHints.push_back(test_7_Hint);
    tesTimeLimits.push_back(test_7_time_limit);

    testsInputs.push_back(test_8_Input);
    testsExpected.push_back(test_8_Expected);
    testsInteractiveExpect.push_back(test_8_InteractiveExpect);
    testsInteractiveSend.push_back(test_8_InteractiveSend);
    testsExecuteCommandArgs.push_back(test_8_ExecuteCommandArgs);
    testsUserPrograms.push_back(test_8_UserPrograms);
    testsDefaultUserPrograms.push_back(test_8_DefaultUserPrograms);
    testsHints.push_back(test_8_Hint);
    tesTimeLimits.push_back(test_8_time_limit);

    testsInputs.push_back(test_9_Input);
    testsExpected.push_back(test_9_Expected);
    testsInteractiveExpect.push_back(test_9_InteractiveExpect);
    testsInteractiveSend.push_back(test_9_InteractiveSend);
    testsExecuteCommandArgs.push_back(test_9_ExecuteCommandArgs);
    testsUserPrograms.push_back(test_9_UserPrograms);
    testsDefaultUserPrograms.push_back(test_9_DefaultUserPrograms);
    testsHints.push_back(test_9_Hint);
    tesTimeLimits.push_back(test_9_time_limit);

    testsInputs.push_back(test_10_Input);
    testsExpected.push_back(test_10_Expected);
    testsInteractiveExpect.push_back(test_10_InteractiveExpect);
    testsInteractiveSend.push_back(test_10_InteractiveSend);
    testsExecuteCommandArgs.push_back(test_10_ExecuteCommandArgs);
    testsUserPrograms.push_back(test_10_UserPrograms);
    testsDefaultUserPrograms.push_back(test_10_DefaultUserPrograms);
    testsHints.push_back(test_10_Hint);
    tesTimeLimits.push_back(test_10_time_limit);

    testsInputs.push_back(test_11_Input);
    testsExpected.push_back(test_11_Expected);
    testsInteractiveExpect.push_back(test_11_InteractiveExpect);
    testsInteractiveSend.push_back(test_11_InteractiveSend);
    testsExecuteCommandArgs.push_back(test_11_ExecuteCommandArgs);
    testsUserPrograms.push_back(test_11_UserPrograms);
    testsDefaultUserPrograms.push_back(test_11_DefaultUserPrograms);
    testsHints.push_back(test_11_Hint);
    tesTimeLimits.push_back(test_11_time_limit);

    testsInputs.push_back(test_12_Input);
    testsExpected.push_back(test_12_Expected);
    testsInteractiveExpect.push_back(test_12_InteractiveExpect);
    testsInteractiveSend.push_back(test_12_InteractiveSend);
    testsExecuteCommandArgs.push_back(test_12_ExecuteCommandArgs);
    testsUserPrograms.push_back(test_12_UserPrograms);
    testsDefaultUserPrograms.push_back(test_12_DefaultUserPrograms);
    testsHints.push_back(test_12_Hint);
    tesTimeLimits.push_back(test_12_time_limit);

    testsInputs.push_back(test_13_Input);
    testsExpected.push_back(test_13_Expected);
    testsInteractiveExpect.push_back(test_13_InteractiveExpect);
    testsInteractiveSend.push_back(test_13_InteractiveSend);
    testsExecuteCommandArgs.push_back(test_13_ExecuteCommandArgs);
    testsUserPrograms.push_back(test_13_UserPrograms);
    testsDefaultUserPrograms.push_back(test_13_DefaultUserPrograms);
    testsHints.push_back(test_13_Hint);
    tesTimeLimits.push_back(test_13_time_limit);

    testsInputs.push_back(test_14_Input);
    testsExpected.push_back(test_14_Expected);
    testsInteractiveExpect.push_back(test_14_InteractiveExpect);
    testsInteractiveSend.push_back(test_14_InteractiveSend);
    testsExecuteCommandArgs.push_back(test_14_ExecuteCommandArgs);
    testsUserPrograms.push_back(test_14_UserPrograms);
    testsDefaultUserPrograms.push_back(test_14_DefaultUserPrograms);
    testsHints.push_back(test_14_Hint);
    tesTimeLimits.push_back(test_14_time_limit);

    testsInputs.push_back(test_15_Input);
    testsExpected.push_back(test_15_Expected);
    testsInteractiveExpect.push_back(test_15_InteractiveExpect);
    testsInteractiveSend.push_back(test_15_InteractiveSend);
    testsExecuteCommandArgs.push_back(test_15_ExecuteCommandArgs);
    testsUserPrograms.push_back(test_15_UserPrograms);
    testsDefaultUserPrograms.push_back(test_15_DefaultUserPrograms);
    testsHints.push_back(test_15_Hint);
    tesTimeLimits.push_back(test_15_time_limit);

    testsInputs.push_back(test_16_Input);
    testsExpected.push_back(test_16_Expected);
    testsInteractiveExpect.push_back(test_16_InteractiveExpect);
    testsInteractiveSend.push_back(test_16_InteractiveSend);
    testsExecuteCommandArgs.push_back(test_16_ExecuteCommandArgs);
    testsUserPrograms.push_back(test_16_UserPrograms);
    testsDefaultUserPrograms.push_back(test_16_DefaultUserPrograms);
    testsHints.push_back(test_16_Hint);
    tesTimeLimits.push_back(test_16_time_limit);

    testsInputs.push_back(test_17_Input);
    testsExpected.push_back(test_17_Expected);
    testsInteractiveExpect.push_back(test_17_InteractiveExpect);
    testsInteractiveSend.push_back(test_17_InteractiveSend);
    testsExecuteCommandArgs.push_back(test_17_ExecuteCommandArgs);
    testsUserPrograms.push_back(test_17_UserPrograms);
    testsDefaultUserPrograms.push_back(test_17_DefaultUserPrograms);
    testsHints.push_back(test_17_Hint);
    tesTimeLimits.push_back(test_17_time_limit);

    testsInputs.push_back(test_18_Input);
    testsExpected.push_back(test_18_Expected);
    testsInteractiveExpect.push_back(test_18_InteractiveExpect);
    testsInteractiveSend.push_back(test_18_InteractiveSend);
    testsExecuteCommandArgs.push_back(test_18_ExecuteCommandArgs);
    testsUserPrograms.push_back(test_18_UserPrograms);
    testsDefaultUserPrograms.push_back(test_18_DefaultUserPrograms);
    testsHints.push_back(test_18_Hint);
    tesTimeLimits.push_back(test_18_time_limit);

    testsInputs.push_back(test_19_Input);
    testsExpected.push_back(test_19_Expected);
    testsInteractiveExpect.push_back(test_19_InteractiveExpect);
    testsInteractiveSend.push_back(test_19_InteractiveSend);
    testsExecuteCommandArgs.push_back(test_19_ExecuteCommandArgs);
    testsUserPrograms.push_back(test_19_UserPrograms);
    testsDefaultUserPrograms.push_back(test_19_DefaultUserPrograms);
    testsHints.push_back(test_19_Hint);
    tesTimeLimits.push_back(test_19_time_limit);

    testsInputs.push_back(test_20_Input);
    testsExpected.push_back(test_20_Expected);
    testsInteractiveExpect.push_back(test_20_InteractiveExpect);
    testsInteractiveSend.push_back(test_20_InteractiveSend);
    testsExecuteCommandArgs.push_back(test_20_ExecuteCommandArgs);
    testsUserPrograms.push_back(test_20_UserPrograms);
    testsDefaultUserPrograms.push_back(test_20_DefaultUserPrograms);
    testsHints.push_back(test_20_Hint);
    tesTimeLimits.push_back(test_20_time_limit);

    testsInputs.push_back(test_21_Input);
    testsExpected.push_back(test_21_Expected);
    testsInteractiveExpect.push_back(test_21_InteractiveExpect);
    testsInteractiveSend.push_back(test_21_InteractiveSend);
    testsExecuteCommandArgs.push_back(test_21_ExecuteCommandArgs);
    testsUserPrograms.push_back(test_21_UserPrograms);
    testsDefaultUserPrograms.push_back(test_21_DefaultUserPrograms);
    testsHints.push_back(test_21_Hint);
    tesTimeLimits.push_back(test_21_time_limit);

    testsInputs.push_back(test_22_Input);
    testsExpected.push_back(test_22_Expected);
    testsInteractiveExpect.push_back(test_22_InteractiveExpect);
    testsInteractiveSend.push_back(test_22_InteractiveSend);
    testsExecuteCommandArgs.push_back(test_22_ExecuteCommandArgs);
    testsUserPrograms.push_back(test_22_UserPrograms);
    testsDefaultUserPrograms.push_back(test_22_DefaultUserPrograms);
    testsHints.push_back(test_22_Hint);
    tesTimeLimits.push_back(test_22_time_limit);

    testsInputs.push_back(test_23_Input);
    testsExpected.push_back(test_23_Expected);
    testsInteractiveExpect.push_back(test_23_InteractiveExpect);
    testsInteractiveSend.push_back(test_23_InteractiveSend);
    testsExecuteCommandArgs.push_back(test_23_ExecuteCommandArgs);
    testsUserPrograms.push_back(test_23_UserPrograms);
    testsDefaultUserPrograms.push_back(test_23_DefaultUserPrograms);
    testsHints.push_back(test_23_Hint);
    tesTimeLimits.push_back(test_23_time_limit);

    testsInputs.push_back(test_24_Input);
    testsExpected.push_back(test_24_Expected);
    testsInteractiveExpect.push_back(test_24_InteractiveExpect);
    testsInteractiveSend.push_back(test_24_InteractiveSend);
    testsExecuteCommandArgs.push_back(test_24_ExecuteCommandArgs);
    testsUserPrograms.push_back(test_24_UserPrograms);
    testsDefaultUserPrograms.push_back(test_24_DefaultUserPrograms);
    testsHints.push_back(test_24_Hint);
    tesTimeLimits.push_back(test_24_time_limit);

    testsInputs.push_back(test_25_Input);
    testsExpected.push_back(test_25_Expected);
    testsInteractiveExpect.push_back(test_25_InteractiveExpect);
    testsInteractiveSend.push_back(test_25_InteractiveSend);
    testsExecuteCommandArgs.push_back(test_25_ExecuteCommandArgs);
    testsUserPrograms.push_back(test_25_UserPrograms);
    testsDefaultUserPrograms.push_back(test_25_DefaultUserPrograms);
    testsHints.push_back(test_25_Hint);
    tesTimeLimits.push_back(test_25_time_limit);

    testsInputs.push_back(test_26_Input);
    testsExpected.push_back(test_26_Expected);
    testsInteractiveExpect.push_back(test_26_InteractiveExpect);
    testsInteractiveSend.push_back(test_26_InteractiveSend);
    testsExecuteCommandArgs.push_back(test_26_ExecuteCommandArgs);
    testsUserPrograms.push_back(test_26_UserPrograms);
    testsDefaultUserPrograms.push_back(test_26_DefaultUserPrograms);
    testsHints.push_back(test_26_Hint);
    tesTimeLimits.push_back(test_26_time_limit);

    testsInputs.push_back(test_27_Input);
    testsExpected.push_back(test_27_Expected);
    testsInteractiveExpect.push_back(test_27_InteractiveExpect);
    testsInteractiveSend.push_back(test_27_InteractiveSend);
    testsExecuteCommandArgs.push_back(test_27_ExecuteCommandArgs);
    testsUserPrograms.push_back(test_27_UserPrograms);
    testsDefaultUserPrograms.push_back(test_27_DefaultUserPrograms);
    testsHints.push_back(test_27_Hint);
    tesTimeLimits.push_back(test_27_time_limit);

    testsInputs.push_back(test_28_Input);
    testsExpected.push_back(test_28_Expected);
    testsInteractiveExpect.push_back(test_28_InteractiveExpect);
    testsInteractiveSend.push_back(test_28_InteractiveSend);
    testsExecuteCommandArgs.push_back(test_28_ExecuteCommandArgs);
    testsUserPrograms.push_back(test_28_UserPrograms);
    testsDefaultUserPrograms.push_back(test_28_DefaultUserPrograms);
    testsHints.push_back(test_28_Hint);
    tesTimeLimits.push_back(test_28_time_limit);

    testsInputs.push_back(test_29_Input);
    testsExpected.push_back(test_29_Expected);
    testsInteractiveExpect.push_back(test_29_InteractiveExpect);
    testsInteractiveSend.push_back(test_29_InteractiveSend);
    testsExecuteCommandArgs.push_back(test_29_ExecuteCommandArgs);
    testsUserPrograms.push_back(test_29_UserPrograms);
    testsDefaultUserPrograms.push_back(test_29_DefaultUserPrograms);
    testsHints.push_back(test_29_Hint);
    tesTimeLimits.push_back(test_29_time_limit);

    testsInputs.push_back(test_30_Input);
    testsExpected.push_back(test_30_Expected);
    testsInteractiveExpect.push_back(test_30_InteractiveExpect);
    testsInteractiveSend.push_back(test_30_InteractiveSend);
    testsExecuteCommandArgs.push_back(test_30_ExecuteCommandArgs);
    testsUserPrograms.push_back(test_30_UserPrograms);
    testsDefaultUserPrograms.push_back(test_30_DefaultUserPrograms);
    testsHints.push_back(test_30_Hint);
    tesTimeLimits.push_back(test_30_time_limit);

    testsInputs.push_back(test_31_Input);
    testsExpected.push_back(test_31_Expected);
    testsInteractiveExpect.push_back(test_31_InteractiveExpect);
    testsInteractiveSend.push_back(test_31_InteractiveSend);
    testsExecuteCommandArgs.push_back(test_31_ExecuteCommandArgs);
    testsUserPrograms.push_back(test_31_UserPrograms);
    testsDefaultUserPrograms.push_back(test_31_DefaultUserPrograms);
    testsHints.push_back(test_31_Hint);
    tesTimeLimits.push_back(test_31_time_limit);

    testsInputs.push_back(test_32_Input);
    testsExpected.push_back(test_32_Expected);
    testsInteractiveExpect.push_back(test_32_InteractiveExpect);
    testsInteractiveSend.push_back(test_32_InteractiveSend);
    testsExecuteCommandArgs.push_back(test_32_ExecuteCommandArgs);
    testsUserPrograms.push_back(test_32_UserPrograms);
    testsDefaultUserPrograms.push_back(test_32_DefaultUserPrograms);
    testsHints.push_back(test_32_Hint);
    tesTimeLimits.push_back(test_32_time_limit);

    testsInputs.push_back(test_33_Input);
    testsExpected.push_back(test_33_Expected);
    testsInteractiveExpect.push_back(test_33_InteractiveExpect);
    testsInteractiveSend.push_back(test_33_InteractiveSend);
    testsExecuteCommandArgs.push_back(test_33_ExecuteCommandArgs);
    testsUserPrograms.push_back(test_33_UserPrograms);
    testsDefaultUserPrograms.push_back(test_33_DefaultUserPrograms);
    testsHints.push_back(test_33_Hint);
    tesTimeLimits.push_back(test_33_time_limit);

    testsInputs.push_back(test_34_Input);
    testsExpected.push_back(test_34_Expected);
    testsInteractiveExpect.push_back(test_34_InteractiveExpect);
    testsInteractiveSend.push_back(test_34_InteractiveSend);
    testsExecuteCommandArgs.push_back(test_34_ExecuteCommandArgs);
    testsUserPrograms.push_back(test_34_UserPrograms);
    testsDefaultUserPrograms.push_back(test_34_DefaultUserPrograms);
    testsHints.push_back(test_34_Hint);
    tesTimeLimits.push_back(test_34_time_limit);

    testsInputs.push_back(test_35_Input);
    testsExpected.push_back(test_35_Expected);
    testsInteractiveExpect.push_back(test_35_InteractiveExpect);
    testsInteractiveSend.push_back(test_35_InteractiveSend);
    testsExecuteCommandArgs.push_back(test_35_ExecuteCommandArgs);
    testsUserPrograms.push_back(test_35_UserPrograms);
    testsDefaultUserPrograms.push_back(test_35_DefaultUserPrograms);
    testsHints.push_back(test_35_Hint);
    tesTimeLimits.push_back(test_35_time_limit);

    testsInputs.push_back(test_36_Input);
    testsExpected.push_back(test_36_Expected);
    testsInteractiveExpect.push_back(test_36_InteractiveExpect);
    testsInteractiveSend.push_back(test_36_InteractiveSend);
    testsExecuteCommandArgs.push_back(test_36_ExecuteCommandArgs);
    testsUserPrograms.push_back(test_36_UserPrograms);
    testsDefaultUserPrograms.push_back(test_36_DefaultUserPrograms);
    testsHints.push_back(test_36_Hint);
    tesTimeLimits.push_back(test_36_time_limit);

    testsInputs.push_back(test_37_Input);
    testsExpected.push_back(test_37_Expected);
    testsInteractiveExpect.push_back(test_37_InteractiveExpect);
    testsInteractiveSend.push_back(test_37_InteractiveSend);
    testsExecuteCommandArgs.push_back(test_37_ExecuteCommandArgs);
    testsUserPrograms.push_back(test_37_UserPrograms);
    testsDefaultUserPrograms.push_back(test_37_DefaultUserPrograms);
    testsHints.push_back(test_37_Hint);
    tesTimeLimits.push_back(test_37_time_limit);

    testsInputs.push_back(test_38_Input);
    testsExpected.push_back(test_38_Expected);
    testsInteractiveExpect.push_back(test_38_InteractiveExpect);
    testsInteractiveSend.push_back(test_38_InteractiveSend);
    testsExecuteCommandArgs.push_back(test_38_ExecuteCommandArgs);
    testsUserPrograms.push_back(test_38_UserPrograms);
    testsDefaultUserPrograms.push_back(test_38_DefaultUserPrograms);
    testsHints.push_back(test_38_Hint);
    tesTimeLimits.push_back(test_38_time_limit);
}

// Converting int aschii to string
string aschiiToString(int aschii){
    // Asserting aschii is within aschii bounds
    if(aschii < 0 || aschii > 255){
        return "not aschii";
    }

    // Converting
    string s;
    s = (char)aschii;

    return s;
}