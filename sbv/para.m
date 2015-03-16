clear all;clc;close all;
Mp = 200;
L = 1;
Jp = 27.6;
g = 9.8;
beta = Jp / (Mp * L) + L;
gama = L * Mp * g;
A43 = gama / Jp - (L * gama) / (Jp * beta);
B4 = (L / beta - 1) / Jp;

wn = 10;
ksi = 0.707;

gama1 = -4;
gama2 = -10000;

p11 = ksi / wn + (wn ^ 2 + 1) / (4 * ksi);
p12 = 1 / (2 * wn ^ 2);
p22 = (wn ^ 2 + 1) / (4 * ksi * wn ^ 3);

Kp0 = (wn ^ 2 + A43) / B4;
Kd0 = 2 * ksi * wn / B4;

f4 = 100;
Kthi0 = 1000;
K2max = 100;












