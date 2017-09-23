clear all
close all
clc
load('data1.mat')
m=length(x(:,1))-20;
figure(1)
for i=1:20
    scatter(x(i+m,:),y(i+m,:),1)
    hold on
end
quiver(x(end,:),y(end,:),cos(an(end,:)), sin(an(end,:)),0.25)