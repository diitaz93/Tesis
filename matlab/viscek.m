function [va] = viscek( N, L, eta, r, T_steps, v)
%VISCEK implements Viscek model por self-proppelled particles
%   N is the numebr of particles, L the size of the squared space
%   eta is the noise coeficcient, r is the radius of interaction,
%   T_steps the number of steps and v the norm of velocity (constant).
%   va is the absolute value of the average velocity that works as 
%   order parameter

delta_T=1; % Timestep
%%%%%%%%%%%%%%%%%%%%%%%%%% Initialization %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Positions for ALL times are initialized randomly and modified in time ev.
% Rows = timesteps
% Columns = particles
% Seed the random generation with time
rng('shuffle')
x=L*rand(T_steps,N); % Matrix of x positions for all times
rng('shuffle')
y=L*rand(T_steps,N); % Matrix of y positions for all times
rng('shuffle')
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
        cont = 0;
        for k=1:N
            % X distance between particles k and j (j as zero)
            x_v = abs(x(i-1,k) - x(i-1,j));
            % Y distance between particles k and j (j as zero)
            y_v = abs(y(i-1,k) - y(i-1,j));
            % Find the lowest distance considering PBC
            x_v = min(x_v,L-x_v);
            y_v = min(y_v,L-y_v);
            % Euclidean distance
            dist = sqrt( x_v^2 + y_v^2 );
            % Decide if is neighbourg
            if (dist < r)
                % Sum x and y components
                sum_sin = sum_sin + sin(an(i-1,k));
                sum_cos = sum_cos + cos(an(i-1,k));
                cont = cont +1;
            end
        end
        %-------- Corrects the arctan problem and adds noise -------------%
        % In case there is no neighbourg
        if cont == 0
            A = an(i-1,j) + eta*rand-0.5*eta; 
        else
            A = atan2(sum_sin,sum_cos) + eta*rand-0.5*eta;
        end
        % Only positive angles
        if A < 0
            A = A + 2*pi;
        end
        % Boundary Conditions
        an(i,j) = abs(A - 2*pi*floor(A/(2*pi)));
        %-----------------------------------------------------------------%
    end
end

%%%%%%%%%%%%%% Calculation of order parameter %%%%%%%%%%%%%%%%%%%%%%%%%%%
vx=sum(cos(an(end,:))); % Sum of velocities in x
vy=sum(sin(an(end,:))); % Sum of velocities in y
va= sqrt(vx^2 + vy^2)/N; % Average norm of velocity

end
