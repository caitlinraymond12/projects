### **Project Created**: Spring 2025 

### **Class**: Principles of Artificial Intelligence

Creating a family tree is one of the most basic projects you can complete in prolog, and the purpose of this project is to gain and understanding of how prolog works. Using recursion in prolog was another focus of this assignment, and it was necessary to utilize in some of the family relations. 

All of the expected familial relations were there, but there were a few interesting ones that took a little more thinking to get working present as well. In my family tree, you are also able to find the nth ancestor of a person, the nth cousin of a person, and even the nth-cousin-of a person removed either up or down.  


Code:
```
related(X, is-nth-cousin-of(0), Y) :- parent(X, Z), parent(Y, Z), X \= Y.
related(X, is-nth-cousin-of(N), Y) :- parent(X, A), parent(Y, B), N1 is N - 1, related(A, is-nth-cousin-of(N1), B).

related(X, is-nth-ancestor-of(1), Y) :- parent(Y, X).
related(X, is-nth-ancestor-of(N), Y) :- parent(Y, Z) , N1 is N - 1, related(X, is-nth-ancestor-of(N1), Z).

related(X, is-nth-cousin-of(N, removed-up, M), Y) :- YA is N + 1, XA is YA - M, related(Z, is-nth-ancestor-of(XA), X), related(Z, is-nth-ancestor-of(YA), Y).
related(X, is-nth-cousin-of(N, removed-down, M), Y) :- YA is N + 1, XA is YA + M, related(Z, is-nth-ancestor-of(XA), X), related(Z, is-nth-ancestor-of(YA), Y).
```

Output:
```
?- related(joe-dog, is-nth-cousin-of(1), ann-ant).
true .

?- related(joe-dog, is-nth-cousin-of(2, removed-up, 1), mary-ant).
true .

?- related(mary-ant, is-nth-cousin-of(1, removed-down, 1), joe-dog).
true .


```