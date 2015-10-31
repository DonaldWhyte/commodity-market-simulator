# Commodities Market System (CMS)

This project simulates an electronic trading platform for commodities contracts.

CMS allows dealers to list the contracts they have available to buy or sell, 
referred to as posting orders, and allows other dealers to trade these orders,
referred to as aggressing on orders. Dealers can modify and revoke their
orders, as well as query orders currently available.

The system is developed entirely in C++. The base CMS program accepts dealer
commands as input through stdin and outputs the results of these commands via
stdout (i.e. input/output is done through the console).

### Implemented Extensions

Extension 1 and Extension 2 have been implemented as server applications.
These accept dealer commands via TCP connections, sending command results
back to clients via the same connection.

A separate client application has been created to test extension 1 and 2. 
This application takes the hostname/IP address and port of the server and
establishes a connection. It then allows the user to enter commands which are
sent to the server and executed server-side. The output is sent back to the
client, where it is displayed to the user.

The source files for this application are stored in the `client` folder.

### Third-Party Libraries

In addition to the C++ standard library, the following third-party libraries
were used:

* Boost.Asio
* Boost.Memory
* Boost.Smart_Ptr
* Boost.System
* Boost.Thread

The minimum supported Boost version is 1.46.1.

### Design Overview

There are three main `modules` to the application.

* `client` -- contains all the source code for the CMS client application
* `cms` -- contains source code for parsing and executing commands, managing dealers and orders, as well as handling user input (whether that's through the command line or through TCP connections)
* `common` -- contains functionality used by both the `client` and `cms` modules

The following process is executed when CMS receives a dealer command:

1. The command, currently text, is parsed using the `CommandParser` class. This results in an instance of the Command class.
2. The command is executed by calling `Command::run()`, passing the application-wide instance of `OrderManager`. `OrderManager` is the class which stores all currently available orders, and can post, revoke or aggress those orders.
3. `Command::run()` returns a string which is displayed to the user on the command line. If the extensions are used, this string is send back to the client using the same TCP connection the client used to send the original command.

All commands are children of the `Command` abstract class. Through polymorphism
and multiple global lists, adding new commands is straightforward. To create a new command, these steps must be followed:

1. Implement the command's functionality by creating a subclass of `Command`
2. Implement a function which parses the textual command and returns
   an instance of the command's class, placing the function in the file
   `cms/include/CommandParseFunctions.hpp`
3. Add the command to the `COMMAND_TYPES` array in
   `cms/include/CommandTypes.hpp`. This list stores the identifier for the
   command (e.g. "POST", "LIST"), its minimum required arguments and the
   function which parses the command.

Currently, dealers are hard-coded into the system. However, the hard-coded
dealer list is wrapped in the DealerManager class. This means other ways of
creating/loading dealers can be implemented without affecting the rest of
the system.

Extension 2 allows several clients to send commands to CMS at the same time.
If these commands modify orders, then there is the possibility of race
conditions occurring. Synchronisation mechanisms have been put in place to
prevent these from occurring. Specifically, mutex locks have been used 
within the ClientThreadManager class and on the application-wide OrderManager
instance. These ensure that only client can modify orders at a time.

### Documentation

No explicit documentation has been written for this project. It is felt that
much of the code is self-documented through descriptive variable and method
names. Comments have been added to fields and methods when what they do may
not be immediately obvious.

Additionally, comment headers are provided above each class, namespace,
structure and enumerator. These describe what the intent of the structure is
and how it works.

### Compilation Guide

Makefiles are provided for each executable. These makefiles assume that
Boost has been installed in the system's include and library directories. On
Unix-based systems, the system include and library directories are typically
`/usr/include` and `/usr/lib` respectively.

To compile the main CMS application, navigate to the `cms` directory and type
`make`. The generated executable is called `cms`.

To compile the CMS client application, navigate to the `client` directory and
type `make`. The generated executable is called `cmsclient`.

### Usage Guide

The CMS program is executed as described in the given specification.
The first argument is the input mode, which is used to enable the extensions,
and the second argument is the port number (used by the extensions).

Usage:

```
./cms {base|ext1|ext2} <portNo>
```

The CMS client application requires the hostname and port of the CMS server,
which is executed by using the two extensions in the CMS program. 

Usage:

```
    ./cmsclient <hostname> <port>
```

Note that an IP address can be used instead of a hostname. `localhost` or
`127.0.0.1` should be used as the hostname if the CMS server is running on the
same machine as the client.

### Test Suite

During development, tests were developed to ensure the correctness of certain
parts of the project. The parsing and execution of commands, as well as order
management, are the focus of these tests.

For completeness, these tests have been provided in the `test` directory. This
test suite has its own makefile, just like the `cms` and `cmsclient` programs.
This makefile produces an executable called `cmstests`, which executes all the
implemented tests.

The tests are implemented using the google-test library. If the user is
interested in running these tests, then they must install google-test. The
test suite's makefile expects google-test to be installed in the system
directories. This means google-test's static library should be stored in
/usr/lib and a directory containing google-test's header files (called
`gtest`) to be present in /usr/include.

### Known Issues

There are no known bugs or issues in any of the CMS applications at this time.
