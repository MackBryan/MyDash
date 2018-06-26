
Project 1 Minishell {#mainpage}
----------------------

|Filename       | Description                                                   |
|---------------|-------------------------------------------------------------------|
|README.dox     |This file |
|doxygen-config |Sample config file for doxygen |
|Makefile       |Build file for the mydash project (adapt to your needs) |
|TestCases      |An incomplete list of test cases |
|valgrind.supp  |Example suppression file for valgrind for the readline library |
|mydash-src/Makefile | Build file for mydash (adapt to your needs) |
|mydash-src/mydash.c | Starter version of mydash.c |
|mydash-src/error.c  | Error handling code used in class examples |
|mydash-src/mydash.h | Header file for the mydash project|
|mydash-src/changeDirectory.c | Handles change directory commands |
|mydash-src/changeDirectory.h | Header file for changeDirectory.c|
|mydash-src/checkBG.c | Checks for finished background jobs|
|mydash-src/checkBG.h | Header file for checkBG.c |
|mydash-src/getJobID.c | Gets the next job number to be assigned |
|mydash-src/getJobID.h | Header file for getJobID.c |
|mydash-src/handleCommand.c | Handles normal foreground command functionality |
|mydash-src/handleCommand.h | Header file for handleCommand.c |
|mydash-src/handleJob.c | Handles command functionality for backgroundtasks |
|mydash-src/handleJob.h | Header file for handleJob.c |
|mydash-src/listJobs.c | Lists all running and unotified Done jobs to the user |
|mydash-src/listJobs.h | Header file for listJobs.h |
|mydash-src/parseInput.c | Parses command line input to be processed |
|mydash-src/parseInput.h | Header file for parseInput.c |
|other-progs/test-readline.c|file on how to use auto completion with readline |
|other-progs/loop.c   |Simple infinite loop program for testing purposes |
|other-progs/Makefile |Makefile to build other program examples |

Building the project
--------

From the top level directory, p1, type the following into the command line to
compile the program:
$ make

To run the minishell type the following in the command line from the top level
directory:
$ ./mydash


!!README INFO!!
--------
This is a reference for readers!

Fixed Issues for p1 are listed in a section below.

If I have changed any sections since my
p1 implementatin I will differentiate with:

    From p1:
 or
    From p3:

This is for ease of access for future problem solving references.

Features and usage
--------

Mydash supports normal command line functionality including backgrounds jobs.

Mydash features readline functionality including using_history. Readline can be
prompted with the tab button on your keyboard and using history can be accessed
with arrow keys.

A background job can be made by appending an '&' to the end of a command.

Testing
-------------

To test this program I did simple functionality tests to ensure my most recent
implementation worked before attempting to add another.

A full list of tests may be found in testCases file

Valgrind
-------------
    From p3:

All valgrind leaks have been fixed. Check Discussion section
for information.

    From p1:

I have not fixed all valgrind errors. The most prominent is those related to
createList functions in which I am having a tough time dealing with. I have a
problem that exists in using freeList. I beleive these have todo with how I am
passing them to functions but it is keeping me from fixing this particular
issue.
I also have a leak with parsing only after having passed at least 2 commands
before exiting. I have spent alot of time trying to decide what it is but have
yet to be able to correct it.

Known Bugs
-------------

Not sure if a bug but when signaling sigint or sigtstp
with no foreground process did not return the prompt. It
acted as if it were still sitting in the while loop waiting
for input, typing a command would still work though.

This annoyed me so I cheesed it and my final implementation forces a fake prompt using printf.
This is for for ease of use and confusion for myself and users that may think
there was an error (or endless loop)  since no prompt was returned.


Fixed from P1
-------------

1. Valgrind memory leaks
2. Handling bad chdir commands
3. Header file javadocs
4. Default Prompt


Discussion
-------------
    From p3:

I have simplified my process of handling jobs.
Instead of returning new lists everytime a job
finished which would create memory issues, I
only remove and free a populated jobs list
when every job it contains is finished. This
fixed my bigger leaks.

Otherwise my freeTokens method was not properly
iterating the array and would leave the appended
null character in our array therefore leaking it
when a new array would be created for a new command.
This came from logical errors in decrementing numTokens
when parsing background jobs and was a simple fix.

Implementing signals was relatively following notes and posts
from piazza. I ran into issues attempting to setup SIGTSTP for
fg processes. The main one being that once I caught the SIGSTP
for a foreground process it would then return to the handleCommand
waitpid where it would never return since it was already stopped.
This put me in an endless loop resulting in ps augx and kill becoming
my best friends.

To fix this issue I had to modify my handleCommand class's waitpid
pid param to 0 so it waits for any child process to return and use the WUNTRACED
flag to return if a child has stopped.


   From p1:

I spent most of my time in this project dealing with memmory issues I dug myself
into for not being more proactive on designing classes. I believe linked list
issues stem from how I create the list to how I manipulate and them in the
passed function. After looking online I saw a few discussion where people got
the same error for trying to free an object already referenced by another
pointer. I was unable to fix mine in time.

The structure used to store our job objects consists of jobID, pid, the command
to be passed to execvp, as well as a string copy of the exact arguement passed
to display to the user when a job is created and finished. It also contains an
integer/boolean for determining a done task which I used mostly for bebugging.

If I could restart this project I would visualize my classes for passing
functions and ensure pointer manipulation is correct as well.


Sources used
-------------

Stackoverflow.com and other discussion websites were consulted in the debugging
process for understanding causes of gcc errors. As well used for valgrind errors, but no solutions were used. Problems were too ambiguous to determine a timely fix for my issues.
