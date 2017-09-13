function [  ] = vary_noise(N_f, L_f, r_f, v_f)
%UNTITLED6 Summary of this function goes here
%   Detailed explanation goes here

% Fixed Parameters
n=100;
% N_f=40;
% L_f=3.1;
% r_f=0.15;
T_f=50;
S_f=50;
% v_f=0.3;

% Plot
eta = linspace(0,5,n);
v_eta = zeros(1,n);
set(0,'DefaultFigureVisible','off') % No graphics

parfor i=1:n
    v_eta(i)=viscek(N_f, L_f, eta(i), r_f, T_f, S_f, v_f);
end

set(0,'DefaultFigureVisible','on') % Activate graphics
% figure(1)
hold on
plot(eta,v_eta)
% title('$N=300$, $r=0.15$, $L=7$, $\Delta t=1$, $T=20$, $v=0.03$,','interpreter','latex')
xlabel('Noise parameter')
ylabel('Absolute velocity $v_a$','interpreter','latex')
ylim([0,1])
legend('N=40, L=3.1','N=100, L=5','N=400, L=10','N=4000, L=31.6','N=10000, L=50')

end

