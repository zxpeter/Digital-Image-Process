x = load('pixel.txt');
y = [];
for i = 1:3
    for j = 1:202*255
    y(j) = x (j*3+i);
    end;
    figure;
    hist(y,256)
end;