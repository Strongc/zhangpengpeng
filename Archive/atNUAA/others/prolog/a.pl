% Name:   Anderson Silva
% Date:   March 10, 1999

% ================================
% A graph that will be used for a Depth First Search Algorithm Knowlodge Base.
%
% ================================

% linked/2
% A nodes and its children

linked(a, [b,c,d]).
linked(b, [e,f]).
linked(c, [g,h]).
linked(d, [i,j]).
linked(e, [k,l]).
linked(f, [l,m]).
linked(g, [n]).
linked(h, [o,p]).
linked(i, [p,q]).
linked(j, [r]).
linked(k, [s]).
linked(l, [t]).
linked(m, []).
linked(n, []).
linked(o, []).
linked(p, [u]).
linked(q, []).
linked(r, []).
linked(s, []).
linked(t, []).
linked(u, []).

% arc/2
% A rule that checks to see if
% there is an arc between two given nodes.

arc(X,Y):- linked(X,L), member(Y,L).
run:- arc(X,Y).
