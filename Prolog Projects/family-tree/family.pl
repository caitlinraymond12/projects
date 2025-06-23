male(tim-ant).
male(jim-bat).
male(joe-ant).
male(mike-ant).
male(bill-bat).
male(matt-dog).
male(bob-ant).
male(jim-ant).
male(joe-dog).
male(bob-fig).
male(tim-fig).
male(tom-ink).
male(jim-ink).
male(dominic-fike).
male(john-box).
male(mike-box).
male(will-box).
male(bryan-jones).
male(peter-jones).
male(scott-ink).
male(richard-fig).


female(susan-fig).
female(lily-flo).
female(grace-ink).
female(megan-jones).
female(jen-box).
female(sue-tree).
female(bri-box).
female(jill-emu).
female(meg-gum).
female(pam-ant).
female(amy-bat).
female(mab-cat).
female(emma-ham).
female(ann-ant).
female(sal-dog).
female(moll-bat).
female(pat-hat).
female(mary-ant).
female(amy-ant).
female(cindy-cat).
female(dolly-cat).


married(mary-ant, john-box).
married(mike-box,sue-tree).
married(jen-box, bryan-jones).
married(jim-ink, lily-flo).
married(tim-ant, jill-emu).
married(jim-bat, meg-gum).
married(joe-ant, amy-bat).
married(mike-ant, mab-cat).
married(pam-ant, matt-dog).
married(bill-bat, emma-ham).
married(ann-ant, bob-fig).
married(bob-ant, tim-fig).
married(jim-ant, pat-hat).
married(moll-bat, tom-ink).
married(dolly-cat, dominic-fike).
married(lily-flo, jim-ink).

parent(cindy-cat, dolly-cat).
parent(joe-ant, tim-ant).
parent(joe-ant, jill-emu).
parent(mike-ant, tim-ant).
parent(mike-ant, jill-emu).
parent(pam-ant, tim-ant).
parent(pam-ant, jill-emu).
parent(amy-bat, jim-bat).
parent(amy-bat, meg-gum).
parent(bill-bat, jim-bat).
parent(bill-bat, meg-gum).
parent(ann-ant, joe-ant).
parent(ann-ant, amy-bat).
parent(bob-ant, joe-ant).
parent(bob-ant, amy-bat).
parent(jim-ant, joe-ant).
parent(jim-ant, amy-bat).
parent(joe-dog, pam-ant).
parent(joe-dog, matt-dog).
parent(sal-dog, pam-ant).
parent(sal-dog, matt-dog).
parent(moll-bat, bill-bat).
parent(moll-bat, emma-ham).
parent(mary-ant, jim-ant).
parent(mary-ant, pat-hat).
parent(amy-ant, jim-ant).
parent(amy-ant, pat-hat).
parent(jim-ink, moll-bat).
parent(jim-ink, tom-ink).
parent(susan-fig, ann-ant).
parent(susan-fig, bob-fig).
parent(richard-fig, ann-ant).
parent(richard-fig, bob-fig).
parent(bri-box, john-box).
parent(bri-box, mary-ant).
parent(mike-box, john-box).
parent(mike-box, mary-ant).
parent(will-box, mike-box).
parent(will-box, sue-tree).
parent(jen-box, mike-box).
parent(jen-box, sue-tree).
parent(megan-jones, jen-box).
parent(megan-jones, bryan-jones).
parent(peter-jones, jen-box).
parent(peter-jones, bryan-jones).
parent(grace-ink, lily-flo).
parent(grace-ink, jim-ink).
parent(scott-ink, lily-flo).
parent(scott-ink, jim-ink).


related(X, is-mother-of, Y) :- female(X), parent(Y,X).
related(X, is-father-of, Y) :- male(X), parent(Y,X).
related(X, is-daughter-of, Y) :- female(X), parent(X, Y).
related(X, is-son-of, Y) :- male(X), parent(X, Y).


related(X, is-brother-of, Y) :- male(X), parent(X, Z), parent(Y, Z), X \= Y.
related(X, is-sister-of, Y) :- female(X),parent(X, Z), parent(Y, Z), X \= Y.
related(X, is-sibling-of, Y) :- parent(X, Z), parent(Y, Z), X \= Y.

related(X, is-sibling-in-law-of, Y) :- married(X, Z), related(Z, is-sibling-of, Y).
related(X, is-sister-in-law-of, Y) :- female(X), married(X, Z), related(Z, is-sibling-of, Y).
related(X, is-brother-in-law-of, Y) :- male(X), married(X, Z), related(Z, is-sibling-of, Y).

related(X, is-step-parent-of, Y) :- parent(Y, Z), married(Z, X).
related(X, is-step-mother-of, Y) :- female(X), parent(Y, Z), married(Z, X).
related(X, is-step-father-of, Y) :- male(X), parent(Y, Z), married(Z, X).


related(X, is-uncle-of, Y) :- male(X), related(X, is-sibling-of, Z), parent(Y, Z).
related(X, is-aunt-of, Y) :- female(X), related(X, is-sibling-of, Z), parent(Y, Z).
related(X, is-nephew-of, Y) :- male(X), related(Y, is-uncle-of, X).
related(X, is-nephew-of, Y) :- male(X), related(Y, is-aunt-of, X).
related(X, is-niece-of, Y) :- female(X), related(Y, is-uncle-of, X).
related(X, is-niece-of, Y) :- female(X), related(Y, is-aunt-of, X).


related(X, is-grandparent-of, Y) :- parent(Y, Z), parent(Z, X).
related(X, is-grandma-of, Y) :- female(X), parent(Y, Z), parent(Z, X).
related(X, is-grandpa-of, Y) :- male(X), parent(Y, Z), parent(Z, X).

related(X, is-great-grandparent-of, Y) :- related(Z, is-grandparent-of, Y), parent(Z, X).
related(X, is-great-grandma-of, Y) :- female(X), related(Z, is-grandparent-of, Y), parent(Z, X).
related(X, is-great-grandpa-of, Y) :- male(X), related(Z, is-grandparent-of, Y), parent(Z, X).

related(X, is-great-great-grandparent-of, Y) :- related(Z, is-great-grandparent-of, Y), parent(Z, X).
related(X, is-great-great-grandma-of, Y) :- female(X), related(Z, is-great-grandparent-of, Y), parent(Z, X).
related(X, is-great-great-grandpa-of, Y) :- male(X), related(Z, is-great-grandparent-of, Y), parent(Z, X).


related(X, is-great-aunt-of, Y) :- female(X), parent(Y, Z), related(X, is-aunt-of, Z).
related(X, is-great-uncle-of, Y) :- male(X), parent(Y, Z), related(X, is-uncle-of, Z).

related(X, is-ancestor-of, Y) :- parent(Y, X).
related(X, is-ancestor-of, Y) :- parent(Y, Z), related(X, is-ancestor-of, Z).

related(X, is-descendant-of, Y) :- parent(X, Y).
related(X, is-descendant-of, Y) :- parent(X, Z), related(Z, is-descendant-of, Y).


related(X, is-blood-related-to, Y) :- related(X, is-descendant-of, Z), related(Y, is-descendant-of, Z).


related(X, is-nth-cousin-of(0), Y) :- parent(X, Z), parent(Y, Z), X \= Y.
related(X, is-nth-cousin-of(N), Y) :- parent(X, A), parent(Y, B), N1 is N - 1, related(A, is-nth-cousin-of(N1), B).


related(X, is-nth-cousin-of-two(N), Y) :- N1 is N + 1, parent(X, P1), parent(Y, P2), P1 \= P2, related(Z, is-nth-ancestor-of(N1), X), related(Z, is-nth-ancestor-of(N1), Y).


related(X, is-nth-ancestor-of(1), Y) :- parent(Y, X).
related(X, is-nth-ancestor-of(N), Y) :- parent(Y, Z) , N1 is N - 1, related(X, is-nth-ancestor-of(N1), Z).

related(X, is-nth-cousin-of(N, removed-up, M), Y) :- YA is N + 1, XA is YA - M, related(Z, is-nth-ancestor-of(XA), X), related(Z, is-nth-ancestor-of(YA), Y).

related(X, is-nth-cousin-of(N, removed-down, M), Y) :- YA is N + 1, XA is YA + M, related(Z, is-nth-ancestor-of(XA), X), related(Z, is-nth-ancestor-of(YA), Y).



