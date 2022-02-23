function shifted = shifter(x, delta, table)
% get important values
shifted = zeros(size(x));
delta_int = trunc(delta);
delta_frac = delta - delta_int;
[rows, filt_len] = size(table);
table_frac = 1/rows;
frac = abs(round(delta_frac / table_frac));

% fractional shift first
if frac ~= 0
    if delta < 0 
        filter = table(frac, :);
    else
        filter = table(end-frac, :);
    end
    interped = real(fft_conv(filter.', x.', 'A', -5)).';
else
    interped = x;
end

% integer shift next
del = abs(delta_int);
if delta_int >= 0
    shifted((del+1):end) = interped(1:(end-del));
else
    shifted(1:(end-del)) = interped((del+1):end);
end

end

