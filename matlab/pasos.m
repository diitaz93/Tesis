% Corridas
N=100;
% Arreglo pasos
S=10:10:1000;
s=length(S);
% Parametro de orden
va=S;
for i=1:s
    display([num2str(i), '%'])
    vt=0;
    for j=1:N
        vt = vt + viscek(300,7,2,1,S(i),0.03);
    end
    va(i) = vt/N;
end
    