clear;
close all
clc

%% Initialization
N = 25; % Number of races
M = [40, 100, 400, 4000, 10000]; % Number of particles
m = length(M);
L = [3.1, 5, 10, 31.6, 50]; % Sizes of cell
% Noise
x=100;
eta = linspace(0,5,x);
% Other
r=0.25;
T=20;
S=20;
v=0.3;
% Initialization of order parameter
va = zeros(m,x);
%% 
figure(1)
for i=1:m
   display(['N=',num2str(M(i))])
    for j=1:x
        % Computes the average va for each value of noise
        vt=0;
        for k=1:N
            vt = vt + viscek(M(i),L(i),eta(j),r,T,S,v);
        end
        va(i,j) = vt/N;
    end
    plot(eta,va(i,:));
    hold on
end
save('promN.mat','va');
        


