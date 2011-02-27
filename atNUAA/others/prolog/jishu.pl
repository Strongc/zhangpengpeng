fun(N,Res):-
	N>1,M=N-1,fun(M,R),Res=R*N.
fun(N,Res):-
	N=1,Res=1.
run:-
	fun(3,R),write(R).
