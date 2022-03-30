function data = getRawData(file_name, varargin)

fid = fopen(file_name);
if 0 < nargin-1
    chirp_iq = fread(fid, varargin{1}*2,'int16');
else
    chirp_iq = fread(fid,'int16');
end
% chirp_iq = fread(fid,'int16');
chirp_iq = reshape(chirp_iq, 2, []).';
data = complex(chirp_iq(:,1), chirp_iq(:,2));
fclose(fid);
end