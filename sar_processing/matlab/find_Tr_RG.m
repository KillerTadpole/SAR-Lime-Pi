% find chirp duration and range gate
load("data/sarA1.mat")

s0 = recv;
c = 3e8;
h = 1000; %
F_pr = 700; %
T_pr = 1/F_pr; %
K = 4e12; %
Vr = 200; %
lambda = 0.03; %
Fc = c/lambda; %
Lant = 1; %
Fs = 30e6; %
Ts = 1/Fs; %
squint = deg2rad(0); %
[N_az, Nrangesamp] = size(s0);
ada = (1:N_az) / F_pr;
theta3dB = 0.886*lambda/Lant;

%% get range bin of azimuth chirp
figure(1);
imagesc(real(s0));
[x, ~] = ginput(2);
x_r = round(x);
Tr = abs(x_r(2)-x_r(1)) / Fs;
disp(strcat("Tr = ", num2str(Tr)));

%% find range with slope of K_a
short_chirp = makeChirp(f_start, Tr, Fs, K, 0);
r_compressed = fft_corr(short_chirp.', s0.').';
figure(1);
imagesc(real(r_compressed));
[x, ~] = ginput(1);
x_az = round(x);
az_K = diff(unwrap(angle(r_compressed(:, x_az))), 2) * F_pr^2;
figure(1);
plot(az_K);
[x, ~] = ginput(2);
x = round(x);
K_a = mean(az_K(min(x):max(x))/(2*pi));
R0 = -2*Vr^2 / (lambda*K_a);
del_x = min(x_r) * c/2/Fs;
range_gate_m = R0 - del_x;
range_gate_s = range_gate_m*2/c;

disp(strcat("range_gate_s = ", num2str(range_gate_s)))

close(figure(1))



