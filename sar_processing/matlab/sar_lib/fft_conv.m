function out = fft_corr_interp(A, B, varargin)
% handle varargin
if 0 < nargin-2
    assert(mod(nargin-2,2)==0)
    for i = 1:2:length(varargin)
        if 'A' == varargin{i}
            A_samp_shift = varargin{i+1};
        elseif 'B' == varargin{i}
            B_samp_shift = varargin{i+1};
        elseif "up_samp" == varargin{i}
            up_samp = varargin{i+1};
        end
            
    end
end
if ~exist('A_samp_shift', 'var')
    A_samp_shift = 0;
end
if ~exist('B_samp_shift', 'var')
    B_samp_shift = 0;
end
if ~exist('up_samp', 'var')
    up_samp = 1;
end
% get sizes
dim = size(A);
A_len = dim(1);
A_deep = dim(2);
dim = size(B);
B_len = dim(1);
B_deep = dim(2);

% determin the size of convolving and output
corr_len = 2^nextpow2(A_len + B_len - 1);
out_len = max(A_len, B_len);
out_deep = max(A_deep, B_deep);

% make zero padded variabls
A_corr = zeros(corr_len, A_deep);
B_corr = zeros(corr_len, B_deep);
A_corr(1:A_len, :) = A;
B_corr(1:B_len, :) = B;

% flip one of the inputs to make conv a correlation
A_corr = conj(flipud(A_corr));

% compute time shift for frequency domain
f = ((1:corr_len)-1) / corr_len;
A_fft_shift = exp(-1j*2*pi*A_samp_shift.*f);
B_fft_shift = exp(-1j*2*pi*B_samp_shift.*f);

% fft , mult, ifft
A_corr_fft = fft(A_corr) .* A_fft_shift.';
B_corr_fft = fft(B_corr) .* B_fft_shift.';
out_corr_fft = A_corr_fft .* B_corr_fft;

if up_samp > 1
    zero_pad = zeros(corr_len*(up_samp-1), out_deep);
    out_fft_zero_padded = [out_corr_fft(1:(corr_len/2), :); zero_pad; out_corr_fft((corr_len/2+1):end, :)];
    out_corr = circshift(ifft(out_fft_zero_padded),up_samp);
else
    out_corr = circshift(ifft(out_corr_fft),1);
end
% trim the transients
out = out_corr(1:out_len*up_samp, 1:out_deep) * up_samp;

end