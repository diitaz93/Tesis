function [ x,y,an ] = initialization(N,L,T_steps)
%INITIALIZATION creates a matrix of x positions, a matrix of y positions
%   and a matrix of angles. The columns are the different particles and
%   the rows are timesteps for future time evolution. For simplicity and
%   shortness of code, the matrix is initialized randomly all together,
%   although the only row that should be initialized is the first one

%   N is the number of particles (columns), L is the size of the square and
%   T_steps is the number of timesteps (rows).
x=L*rand(T_steps,N);
y=L*rand(T_steps,N);
an=2*pi*rand(T_steps,N);
save('init.mat','x','y','an');
% Show initial conditions
%figure(1)
%quiver(x(1,:),y(1,:), cos(angle(1,:)), sin(angle(1,:)),0.25)

end

