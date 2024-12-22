Project Created: Spring 2023
Class: Data Structures

This project is simply a calculator, but there is essentially no limit as to how much it can calculate. Instead of storing the numbers as ints, doubles, short ints, etc., it stores them as unsigned chars. It works by doing the same operations any other numerical value can do, except it does them with the ASCII values that chars have.

For example, to add 65 + 66 we would really be adding A + B. This is because the ASCII representation of A is 65, and the ASCII representation of B is 66. 

In this project, you will be able to see that at the very top I defined my own vector, rather than using the #include <vector>. The reason for this is this is a data structures class, so we were required to create all our own data structures. 

The user must input their values in Reverse Polish Notation, which means the operators come after the operands. 

Regular Notation: (5 + 4) * 7
Reverse Polish Notation: 5 4 + 7 *

This calculator can calculate huge values. It can calculate 100! in a fraction of a second, which equates to:

```
> 100 !

 93326215443944152681699238856266700490715968264381
 62146859296389521759999322991560894146397615651828
 62536979208272237582511852109168640000000000000000
 00000000

```

You can also assign variables values and use those variables in later equations 

```
> 10 = x
 10
> 20 = y
 20
> x ! y ! +
 2432902008180268800
> x y + = z
 30
```


