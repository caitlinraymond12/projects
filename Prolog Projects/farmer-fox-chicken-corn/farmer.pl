opposite(w, e).
opposite(e, w).


safe(stateis(FaFoCh, FaFoCh, FaFoCh, _)).
safe(stateis(FaChCo, _, FaChCo, FaChCo)).
safe(stateis(FaFoCo, FaFoCo, _, FaFoCo)).
safe(stateis(FaCh, FoCo, FaCh, FoCo)).



move(stateis(Fa, Fo, Ch, Co), stateis(NFa, Fo, Ch, Co)) :- opposite(Fa, NFa), safe(stateis(NFa, Fo, Ch, Co)).

move(stateis(FaFo, FaFo, Ch, Co), stateis(NFaFo, NFaFo, Ch, Co)) :- opposite(FaFo, NFaFo), safe(stateis(NFaFo, NFaFo, Ch, Co)).

move(stateis(FaCh, Fo, FaCh, Co), stateis(NFaCh, Fo, NFaCh, Co)) :- opposite(FaCh, NFaCh), safe(stateis(NFaCh, Fo, NFaCh, Co)).

move(stateis(FaCo, Fo, Ch, FaCo), stateis(NFaCo, Fo, Ch, NFaCo)) :- opposite(FaCo, NFaCo), safe(stateis(NFaCo, Fo, Ch, NFaCo)).


unvisited([
    stateis(w,w,w,e), stateis(w,w,e,w), stateis(w,w,e,e),
    stateis(w,e,w,w), stateis(w,e,w,e), stateis(w,e,e,w), stateis(w,e,e,e),
    stateis(e,w,w,w), stateis(e,w,w,e), stateis(e,w,e,w), stateis(e,w,e,e),
    stateis(e,e,w,w), stateis(e,e,w,e), stateis(e,e,e,w), stateis(e,e,e,e)
]).


in(Y, [Y | _]).
in(Y, [_ |T]) :- in(Y, T).


goal(stateis(e, e, e, e)).
solve(X, Path, _, Path) :- goal(X).
solve(X, Path, Unvisited, PathHold) :- move(X, Y), in(Y, Unvisited), delete(Unvisited, Y, UnvisitedUpdate), solve(Y, [Y|Path], UnvisitedUpdate, PathHold).



printPath([]).
printPath([H|T]) :- printPath(T), write(H), write("\n").

start :- unvisited(PossibleStates), solve(stateis(w,w,w,w), [stateis(w,w,w,w)], PossibleStates, Path), printPath(Path).