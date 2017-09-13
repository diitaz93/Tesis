function [ new ] = angle_update( N, x, y, angle, r, eta )
% ANGLE_UPDATE updates the angle velocity of the particles for one step
%   x, y and angle are row vectors
new=angle;

for j=1:N
    sum_sin=0;
    sum_cos=0;  
    for k=1:N
        if (sqrt( (x(j)-x(k))^2 + (y(j)-y(k))^2 ) < r)
            sum_sin = sum_sin + sin(angle(k));
            sum_cos = sum_cos + cos(angle(k));
        end
    end
    % Corrects the arctan problem and adds noise
    if (sum_cos < 0)
        new(j) = atan(angle(j)) + pi + eta*rand-0.5*eta;
    else
        new(j) = atan(angle(j)) + eta*rand-0-5*eta;
    end
    % Corrects the minus sign
    if new(j)<0
        new(j)= new(j) +2*pi;
    end
    
end
    
    
            
end

