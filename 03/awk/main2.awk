{A[S]=$1; B[S]=$1; C[S]=$1; S=(S+1) % 3;
 T += (!S && A[0]<A[1]+A[2] && A[1]<A[0]+A[2] && A[2]<A[0]+A[1]);
 T += (!S && B[0]<B[1]+B[2] && B[1]<B[0]+B[2] && B[2]<B[0]+B[1]);
 T += (!S && C[0]<C[1]+C[2] && C[1]<C[0]+C[2] && C[2]<C[0]+C[1]);}
END {print T}
