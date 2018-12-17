 | _______________ |			
 | |SO_2 project:| |
 | |-README.txt  | |
 | |             | |
 | |             | |
 | |             | |
 |_________________|
     _[_______]_
 ___[___________]___
|         [_____] []|__
|         [_____] []|  \__
L___________________J     \ \___\/
 ___________________      /\
/###################\    (__)


    
// The Directory structure //

The main directory contains three subdirectories and three files. One of the files consists of a script, the other of the makefile of the entire project(it calls the makefiles inside of the subdirectories) and the other this exact file.

The subdirectory called CircuitSeqSolver has the files of the sequential solution to the problem and inside of it there is a directory called lib which is a library of auxiliary structures and a makefile(for the files in the directory).

The folder called CircuitParSolver has the same structure and files as CircuitSeqSolver, the only difference is that it contains the files of the parallel solution.

At last, there is a folder called inputs that has a number of .txt files that can be used to test the project. Inside of this directory there is a subdirectory called results where there is a corresponding number of .csv files to the .txt files in the parent directory. This .csv files display the output of the project using each one of the .txt files.

├── DoTest.sh
├── Makefile
├── README.txt
├── CircuitSeqSolver
│   ├── lib
│   ├── Makefile
├── CircuitParSolver
│   ├── lib
│   ├── Makefile
├── inputs
│   ├── results



// Steps for compilation and execution //

There are two different ways to compile and execute the project. The first one is by using the script doTest.sh and the other is by using the command line and ./CircuitParSolver. Both of them are explained below.

Compilation and execution with the script doTest.sh:
    - The script receives two arguments:
        1) N - the number of tasks it will execute
        2) The path to the file with the problem to analyse
    - The number of tasks should be > 0    
    - It should be run in the following way:
        ./doTest N path_to_file
    - Example: 
        ./doTest 4 inputs/random-x128-y128-z5-n128.txt

Compilation and execution using the command line and ./CircuitParSolver:
    - It has a flag and receives two arguments:
        1) Using the flag -t it should receive the number of tasks(N) it will execute 
        2) The path to the file with the problem to analyse
    - The number of tasks should be > 0
    - It should be run in the following way:
        ./CircuitParSolver -t N path_to_file
    - Example:
        ./CircuitParSolver -t 4 ../inputs/random-x128-y128-z5-n128.txt



// Description of the processor and operating system //

Operating System: Linux #39-Ubuntu SMP Mon Sep 24 16:19:90 UTC 2018
Model name: Intel(R) Core(TM) i7-7500U CPU @ 2.70 GHz
Architecture: x86_64
Cpu cores: 2
CPU MHz: 800.017
CPU max MHz: 3500,0000
CPU min MHz: 400,0000


