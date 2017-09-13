function [va] = viscek( N, L, eta, r, T, S, v)
%VISCEK implements Viscek model por self-proppelled particles
%   N is the numebr of particles, L the size of the squared space
%   eta is the noise coeficcient and r is the radius of interaction
%   va is the absolute value of the average velocity that works as 
%   order parameter

T_steps=S;
delta_T=T/T_steps;
r=r*L;
%%%%%%%%%%%%%%%%%%%%%%%%%% Initialization %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
x=L*rand(T_steps,N);
y=L*rand(T_steps,N);
angle=2*pi*rand(T_steps,N);
% figure(1)
% quiver(x(1,:),y(1,:), cos(angle(1,:)), sin(angle(1,:)),0.25)
%%%%%%%%%%%%%%%%%%%%%%%% Time evolution %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
for i=2:T_steps
    for j=1:N
        %------------- Coordinates ---------------------%
        xt = x(i-1,j) + v * cos(angle(i-1,j)) * delta_T;
        yt = y(i-1,j) + v * sin(angle(i-1,j)) * delta_T;
        % Boundary Conditions
        x(i,j) = abs(xt - L*floor(xt/L));
        y(i,j) = abs(yt - L*floor(yt/L));
        %------------ Angle ---------------%
        sum_sin=0;
        sum_cos=0;
        % Determine firts neighbourgs
        for k=1:N
            if (sqrt( (x(i-1,j)-x(i-1,k))^2 + (y(i-1,j)-y(i-1,k))^2 ) < r)
                sum_sin = sum_sin + sin(angle(k));
                sum_cos = sum_cos + cos(angle(k));
            end
        end
        % Corrects the arctan problem and adds noise
        if (sum_cos < 0)
            angle(i,j) = atan(sum_sin/sum_cos) + pi + eta*rand-0.5*eta;
        else
            angle(i,j) = atan(sum_sin/sum_cos) + eta*rand-0-5*eta;
        end
        % Corrects the minus sign
        if angle(i,j)<0
            angle(i,j)= angle(i,j) +2*pi;
        end
        
    end
    hold on
    %quiver(x(i,:),y(i,:),cos(angle(i,:)), sin(angle(i,:)),0.25)
end

hold off
% figure
% quiver(x(end,:),y(end,:),cos(angle(end,:)), sin(angle(end,:)),0.25)
%%%%%%%%%%%%%% Calculation of order parameter %%%%%%%%%%%%%%%%%%%%%%%%%%%
vx=0;
vy=0;
for i=1:N
    vx = vx + cos(angle(end,i));
    vy = vy + sin(angle(end,i));
end
va= sqrt(vx^2 + vy^2)/N; 


end

