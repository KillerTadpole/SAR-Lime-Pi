function nyquist = find_nyquist_F_pr(Fc, Vr, theta3dB, h, range_gate_s, squint, c)
% find the max azimuth chirp rate
R_min = sqrt((range_gate_s*c/2)^2 + h^2);
lambda = c/Fc;
Ka = 2*Vr^2 / (lambda*R_min);
% find 
ym_off_cent = R_min * tan(theta3dB/2 + abs(squint));
ys_off_cent = ym_off_cent / Vr;

max_az_freq = Ka * ys_off_cent;

nyquist = 2*max_az_freq;

end