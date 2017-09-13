%%%%%%%%% PLOTS OF ABSOLUTE VELOCITY VS PARAMETERS %%%%%%%%
close all
clc
clear all
n=100; % Number of points in plots
% Fixed variables
N_f=40;
L_f=3.1;
eta_f=0.15;
r_f=0.15;
T_f=50;
S_f=50;
v_f=0.3;
%% Varying noise
% N=300, r=0.15, L=7, STEPS=20, dt=1, v=0.03
eta = linspace(0,5,n);
v_eta = zeros(1,n);
set(0,'DefaultFigureVisible','off') % No graphics

parfor i=1:n
    v_eta(i)=viscek(N_f, L_f, eta(i), r_f, T_f, S_f, v_f);
end

set(0,'DefaultFigureVisible','on') % Activate graphics
figure(1)
plot(eta,v_eta)
title('$N=300$, $r=0.15$, $L=7$, $\Delta t=1$, $T=20$, $v=0.03$,','interpreter','latex')
xlabel('Noise parameter')
ylabel('Absolute velocity $v_a$','interpreter','latex')
ylim([0,1])
%% Varying interaction radius
% N=300, eta=1.5, L=7, STEPS=20, dt=1, v=0.03
r = linspace(0,1,n);
v_r = zeros(1,n);
set(0,'DefaultFigureVisible','off') % No graphics

parfor i=1:n
    v_r(i) = viscek(N_f, L_f, eta_f, r(i), T_f, S_f, v_f);
end

set(0,'DefaultFigureVisible','on') % Activate graphics
figure(2)
plot(r,v_r)
title('$N=300$, $\eta=1.5$, $L=7$, $\Delta t=1$, $T=20$, $v=0.03$','interpreter','latex')
xlabel('Interaction Radius (fraction of L)')
ylabel('Absolute velocity $v_a$','interpreter','latex')
ylim([0,1])
%% Varying square size
% N=300, eta=0.75, r=0.15, STEPS=20, dt=1, v=0.03
L = linspace(0.5,40,n);
v_L = zeros(1,n);
set(0,'DefaultFigureVisible','off') % No graphics

parfor i=1:n
    v_L(i) = viscek(N_f ,L(i), eta_f , r_f, T_f, S_f, v_f);
end

set(0,'DefaultFigureVisible','on') % Activate graphics
figure(3)
plot(L,v_L)
title('$N=300$, $\eta=0.75$, $r=0.15$, $\Delta t=1$, $T=20$, $v=0.03$','interpreter','latex')
xlabel('Size of Square')
ylabel('Absolute velocity $v_a$','interpreter','latex')
ylim([0,1])
%% Varying number of particles
% L=7, eta=0.75, r=0.15, STEPS=20, dt=1, v=0.03
N = linspace(20,2000,n);
v_N = zeros(1,n);
set(0,'DefaultFigureVisible','off') % No graphics

parfor i=1:n
    v_N(i) = viscek(N(i), L_f, eta_f, r_f, T_f, S_f, v_f);
end

set(0,'DefaultFigureVisible','on') % Activate graphics
figure(4)
plot(N,v_N)
title('$L=7$, $\eta=0.75$, $r=0.15$, $\Delta t=1$, $T=20$, $v=0.03$','interpreter','latex')
xlabel('Number of Particles')
ylabel('Absolute velocity $v_a$','interpreter','latex')
ylim([0,1])
%% Varying norm of velocity
% N=300, L=7, eta=0.75, r=0.15, STEPS=20, dt=1
v = linspace(0.01,1,n);
v_v = zeros(1,n);
set(0,'DefaultFigureVisible','off') % No graphics

parfor i=1:n
    v_v(i) = viscek(N_f, L_f, eta_f, r_f, T_f, S_f, v(i));
end

set(0,'DefaultFigureVisible','on') % Activate graphics
figure(5)
plot(v,v_v)
title('$N=300$, $L=7$, $\eta=0.75$, $r=0.15$, $\Delta t=1$, $T=20$','interpreter','latex')
xlabel('Norm of velocity')
ylabel('Absolute velocity $v_a$','interpreter','latex')
ylim([0,1])
%% Varying total time
% N=300, L=7, eta=0.75, r=0.15, dt=1, v=0.03
T = linspace(10,200,n);
v_T = zeros(1,n);
set(0,'DefaultFigureVisible','off') % No graphics

parfor i=1:n
    v_T(i) = viscek(N_f, L_f, eta_f, r_f, T(i), S_f, v_f);
end

set(0,'DefaultFigureVisible','on') % Activate graphics
figure(6)
plot(T,v_T)
title('$N=300$, $L=7$, $\eta=0.75$, $r=0.15$, $\Delta t=1$, $v=0.03$','interpreter','latex')
xlabel('Total Time')
ylabel('Absolute velocity $v_a$','interpreter','latex')
ylim([0,1])
%% Varying timestep
% N=300, L=7, eta=0.75, r=0.15, T=20, v=0.03
S = 10:10:500;
v_S = zeros(1,n);
set(0,'DefaultFigureVisible','off') % No graphics

parfor i=1:n
    v_S(i) = viscek(N_f, L_f, eta_f, r_f, T_f, S(i), v_f);
end

set(0,'DefaultFigureVisible','on') % Activate graphics
figure(7)
plot(T,v_S)
title('$N=300$, $L=7$, $\eta=0.75$, $r=0.15$, $T=20$, $v=0.03$','interpreter','latex')
xlabel('Number of Timesteps')
ylabel('Absolute velocity $v_a$','interpreter','latex')
ylim([0,1])
%%
fname='graf.mat';
save(fname, 'eta', 'v_eta', 'r', 'v_r', 'L', 'v_L', 'N', 'v_N', ...
    'v', 'v_v', 'T', 'v_T');



