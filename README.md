# Interpreter 2002
Interpreter 2002 is a program that acts as an interpreter for a simple programming language called 2002. This interpreter accepts and executes the commands, each of which is given on a separate line. The following are the lists of commands the user can implement:

|**Command**|**Description**|
| ------------- |:-------------:|
| set [*var*] [*val*] | Sets the variable [*var*] to [*val*]. [*val*] is written as an integer inclusively between 0 and 2002. |
| add [*var1*] [*var2*] | Stores [*var1*] + [*var2*] in [*var1*]. If the result of the addition is more than 2002, it is truncated to 2002. |
| sub [*var1*] [*var2*] | Stores [*var1*] - [*var2*] in [*var1*]. If the result of the subtraction is less than 0, it is truncated to 0. |
| mul [*var1*] [*var2*] | Stores [*var1*] * [*var2*] in [*var1*]. If the result of the multiplication is more than 2002, it is truncated to 2002. |
| div [*var1*] [*var2*] | Stores [*var1*] / [*var2*] in [*var1*]. If the result of the division is not an integer, it is truncated to the nearest lower integer. |
| print [*var*] | Prints the value of [*var*]. The format is “[*var*] = [*val*]”. |
| goto [*lines*] [*var1*] [*var2*] | Go back the line number [*lines*] if [*var1*] < [*var2*]. The interpreter should automatically continue executing the commands as necessary. The execution will get past this point only if the goto command is re-executed while [*var1*] ≥ [*var2*]. |
| exit | Exits the interpreter. |

### Some charachteristics of the Interpreter 2002:
* It accepts only integers between 0 to 2002.
* Any undeclared variable is automatically declared with the initial value of 0 whenever it is referred.
* Traditionally, an interpreter executes commands one by one, providing immediate feedback. However, since this is a primitive interpreter, it reads the whole program before starting any execution.

### Sample I/O:
| Example Input | Example Output |
| ------------- |:-------------:|
| set ONE 1 | sum = 55 |
| set i 10 | |
| add sum i | |
| sub i ONE | |
| goto 2 ZERO i | |
| print sum | |
| exit | |
