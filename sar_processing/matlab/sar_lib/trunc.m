function val = trunc(num)
if num >= 0
    val = floor(num);
else
    val = ceil(num);
end
end