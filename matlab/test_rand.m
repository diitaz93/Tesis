n=1000;
N=1:n;
x=zeros(n);
for i=1:n
    x(i,:)=rand(1,n);
%     scatter(N,x);
%     hold on
%     plot(N,x)
end
hist(x(:),100)