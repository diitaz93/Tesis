clear all
clc
tic
% Corridas
N=100;
% Arreglo pasos
S=10:10:500;
s=length(S);
% Parametro de orden
va=S;
%stdev
err=va;
for i=1:s
    display([num2str(2*i), '%'])
    vt=0;
    et=0;
    V=0;
    for j=1:N
        V = viscek(300,7,2,1,S(i),0.03);
        vt = vt + V;
        et = et +V^2;
    end
    va(i) = vt/N;
    err(i) = sqrt( et/N - va(i)^2 );
    toc
end
    