x = 1.0/51*(1:50);
y = 1.0/51*(1:50);
R = (y'*(x.*x.*x) + x'*(y.*y.*y))/6;
% B(50,:) = B(50,:) - x;
% B(:,50) = B(:,50) - (y.*y)';
load result1.dat
hold on
grid on
% surf(x,y,R);
% surf(x,y,result1);
surf(x, y, R - result1);