clear;
close all
clc
tic;
%% Initialization
% Noise
eta = 0.05:0.05:5;
x = length(eta);
% Number of races
% N = [1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 2000,...
%     2000, 2000, 2000, 2000, 3000, 3000, 3000, 3000, 3000, 4000,...
%     4000, 4000, 4000, 4000, 5000, 5000, 5000, 5000, 5000, 6000,...
%     6000, 6000, 6000, 7000, 7000, 7000, 7000, 8000,...
%     8000, 8000, 8000, 9000, 9000, 9000, 9000, 10000, 10000, 10000,...
%     10000];
N = 4000*eta; 
for i=1:20
   N(i) = 1000;
end
% Number of particles
M = [40, 100, 400, 4000, 10000]; 
m = length(M);
% Sizes of cell
L = [3.1, 5, 10, 31.6, 50]; 

% Fixed parameters
r=1;
S=100;
v=0.03;
% Initialization of order parameter
va = zeros(m,x);
% Errorbar initialized in zero
err = va;
%% 
for i=1:1
   display(['N=',num2str(M(i))])
    for j=1:x
        display([num2str(j),'%'])
        % Computes the average va for each value of noise and stdev
        vt=0;
        et=0;
        for k=1:N(j)
            V = viscek(M(i),L(i),eta(j),r,S,v);
            vt = vt + V;
            et = et + V^2;
        end
        va(i,j) = vt/N(j);
        err(i,j) = sqrt( et/N(j) - va(i,j)^2 );
        toc
    end
end
save('var_N.mat','va','eta','err');
        


