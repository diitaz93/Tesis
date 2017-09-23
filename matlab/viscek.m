function [va] = viscek( N, L, eta, r, T_steps, v)
%VISCEK implements Viscek model por self-proppelled particles
%   N is the numebr of particles, L the size of the squared space
%   eta is the noise coeficcient, r is the radius of interaction,
%   T_steps the number of steps and v the norm of velocity (constant).
%   va is the absolute value of the average velocity that works as 
%   order parameter

delta_T=1; % Timestep
%%%%%%%%%%%%%%%%%%%%%%%%%% Initialization %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Seed the random generation with time
rng('shuffle')

% Positions for ALL times are initialized randomly and modified in time ev.
x=L*rand(T_steps,N); % Matrix of x positions for all times
y=L*rand(T_steps,N); % Matrix of y positions for all times
an=2*pi*rand(T_steps,N); % Matrix of angles for all times

%%%%%%%%%%%%%%%%%%%%%%%% Time evolution %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
for i=2:T_steps
    for j=1:N
        %------------------------ Coordinates ---------------------------%
        xt = x(i-1,j) + v * cos(an(i-1,j)) * delta_T;
        yt = y(i-1,j) + v * sin(an(i-1,j)) * delta_T;
        % Boundary Conditions
        x(i,j) = abs(xt - L*floor(xt/L));
        y(i,j) = abs(yt - L*floor(yt/L));
        %---------------------------- Angle -----------------------------%
        sum_sin=0;
        sum_cos=0;
        % Determines first neighbourgs
        for k=1:N
            % Euclidean distance
            dist_eu = sqrt( (x(i-1,j)-x(i-1,k))^2 + (y(i-1,j)-y(i-1,k))^2 );
            % Distance with periodic boundary conditions
            dist_per = sqrt( (L - abs(x(i-1,j)-x(i-1,k)) )^2 +...
                (L - abs(y(i-1,j)-y(i-1,k)) )^2);
            if (dist_eu < r || dist_per < r)
                sum_sin = sum_sin + sin(an(k));
                sum_cos = sum_cos + cos(an(k));
            end
        end
        % Corrects the arctan problem and adds noise
        if (sum_cos < 0)
            an(i,j) = atan(sum_sin/sum_cos) + pi + eta*rand-0.5*eta;
        else
            an(i,j) = atan(sum_sin/sum_cos) + eta*rand-0-5*eta;
        end
        % Corrects the minus sign
        if an(i,j)<0
            an(i,j)= an(i,j) +2*pi;
        end
        %-----------------------------------------------------------------%
    end
end
%save('data1.mat','x','y','an')

%%%%%%%%%%%%%% Calculation of order parameter %%%%%%%%%%%%%%%%%%%%%%%%%%%
vx=sum(cos(an(end,:))); % Sum of velocities in x
vy=sum(sin(an(end,:))); % Sum of velocities in y
va= sqrt(vx^2 + vy^2)/N; % Average norm of velocity


end

