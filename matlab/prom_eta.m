clear;
close all
clc
tic
%% Initialization
% Number of races
N = [5000, 5000, 5000, 5000, 5000, 5000, 5000, 5000, 5000, 5000,...
    2500, 2500, 2500, 2500, 2500, 2000, 2000, 2000, 2000, 2000, 500,...
    500, 500, 500, 500]; 
% Number of particles
M = [40,80,120,160,200,240,280,320,360,400,500,600,700,800,900,1000,1100,...
    1200,1300,1400,1500,1600,2000,3000,4000]; 
m = length(M); %25
L = 20; % Size of cell
rho = M/L^2;

% Noise
eta = 2.75;
% Other
r=1;
S=50;
v=0.03;
% Initialization of order parameter
va = zeros(1,m);
err = va;
%% 
for i=1:m
    display([num2str(i*4),'%'])
    % Computes the average va for each value of density
    vt = 0;
    et = 0;
    for k=1:N(i)
        V = viscek(M(i),L,eta,r,S,v);
        vt = vt + V;
        et = et + V^2;
    end
    va(i) = vt/N(i);
    err(i) = sqrt( et/N(i) - va(i)^2 );
    toc
end
save('var_rho.mat','va','rho','err');
scatter(rho,va);
        


