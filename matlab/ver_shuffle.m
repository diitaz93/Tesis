N=300;
T_steps=100;
L=10;
for i=0:T_steps
    delta_T=1; % Timestep
    %%%%%%%%%%%%%%%%%%%%%%%%%% Initialization %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    % Seed the random generation with time
    rng('shuffle')

    % Positions for ALL times are initialized randomly and modified in time ev.
    x=L*rand(T_steps,N); % Matrix of x positions for all times
    y=L*rand(T_steps,N); % Matrix of y positions for all times
    an=2*pi*rand(T_steps,N); % Matrix of angles for all times
end
N=1:300;
X=mean(x);
err_x=std(x);
Y=mean(y);
err_y=std(y);
A=mean(an);
err_a=std(an);

figure(1)
subplot(3,1,1)
errorbar(N,X,err_x)
xlim([-5,305])
title('Desviación estándar X varias inicializaciones (L=10)')
xlabel('$N$','Interpreter','latex')
ylabel('$\bar(X)$','Interpreter','latex')

subplot(3,1,2)
errorbar(N,Y,err_y)
xlim([-5,305])
title('Desviación estándar Y varias inicializaciones (L=10)')
xlabel('$N$','Interpreter','latex')
ylabel('$\bar(Y)$','Interpreter','latex')


subplot(3,1,3)
errorbar(N,A,err_a)
xlim([-5,305])
title('Desviación estándar ángulo varias inicializaciones')
xlabel('$N$','Interpreter','latex')
ylabel('$\theta$','Interpreter','latex')
% yticks([0 -pi/4 -pi/2 3*pi/4 pi 5*pi/4 3*pi/2 7*pi/4 2*pi])
% yticklabels({'0','-\pi/4','-\pi/2','3\pi/4','\pi','5\pi/4','3\pi/2','7\pi/4','2\pi'})
