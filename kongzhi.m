clc
clear
num = 40*[0.5, 1];
den = conv([1,2,0], [0.02, 1]);
sys1 = tf(num, den);
sys = feedback(sys1,1);

a = sys.den{1};
a1 = a(1);
a2 = a(3);
b1 = a(2);
b2 = a(4);
c1 = (b1*a2-a1*b2)/b1;
c2 = 0;
d1 = (c1*b2-c2*b1)/c1;
k=[a1,b1,c1,d1];
disp(k);
if c1>0 && d1>0
    disp('conclusion: the system is steady')

end

---------------------------------------------------------
figure(1)
nyquist(sys);
grid on
figure(2)
bode(sys)
grid on


