 | _______________ |			
 | |SO_3 project:| |
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

The main directory contains five subdirectories and two files. One of the files consists of the makefile of the entire project(it calls the makefiles inside of the subdirectories) and the other this exact file.

The subdirectory called CircuitSeqSolver has the files of the sequential solution to the problem and inside of it there is a directory called lib which is a library of auxiliary structures and a makefile(for the files in the directory).

The subdirectory called CircuitRouter-AdvShell has the files that correspond to the server and a makefile(for the files in the directory). It also contains a subdirectory called lib that which is a library of auxiliary structures.

The subdirectory called CircuitRouter-Client has the files that correspond to the client that sends requests to the server(CircuitRouter-Client) and a makefile(for the files in the directory). It also contains a subdirectory called lib that which is a library of auxiliary structures.

The subdirectory called lib is a library of auxiliary structures.

At last, there is a folder called inputs that has a number of .txt files that can be used to test the project. Inside of this directory there is a subdirectory called results where there is a corresponding number of .csv files to the .txt files in the parent directory. This .csv files display the output of the project using each one of the .txt files.

├── lib
├── Makefile
├── README.txt
├── CircuitSeqSolver
│   ├── lib
│   ├── Makefile
├── CircuitRouter-AdvShell
│   ├── lib
│   ├── Makefile
├── CircuitRouter-Client
│   ├── lib
│   ├── Makefile
├── inputs
│   ├── results

// Steps for compilation and execution //

There is only one way to compile and execute the project. Its by using the command line and executing first ./CircuitRouter-AdvShell and secondly ./CircuitRouter-Client. It is better explained below.

Compilation and execution using the command line and ./CircuitAdvShell:
    - It receives one argument:
        1) The number of maxchildren
    - The number of maxchildren should be > 0
    - It should be run in the following way:
        ./CircuitRouter-AdvShell maxchildren
    - Example:
        ./CircuitRouter-AdvShell 4

Execution using the command line and ./CircuitRouter-Client:
    - It receives one argument:
	1) The path to the pipe: ../CircuitRouter-AdvShell/CircuitRouter-AdvShell.pipe
    -Example:
	./CircuitRouter-Client ../CircuitRouter-AdvShell/CircuitRouter-AdvShell.pipe

// Description of the processor and operating system //

Operating System: Linux #39-Ubuntu SMP Mon Sep 24 16:19:90 UTC 2018
Model name: Intel(R) Core(TM) i7-7500U CPU @ 2.70 GHz
Architecture: x86_64
Cpu cores: 2
CPU MHz: 800.017
CPU max MHz: 3500,0000
CPU min MHz: 400,0000


