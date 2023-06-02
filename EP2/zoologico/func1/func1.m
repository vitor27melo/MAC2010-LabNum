function func1()
  n = 600;
  M = ones(n, n, 3);

  ceil = 255;
  for i = 1:n
    for j = 1:n
      M(i, j, 1) = floor(sin(axisToAngle(i)) * ceil);
      M(i, j, 2) = floor(((sin(axisToAngle(j)) + sin(axisToAngle(i)))/2) * ceil);
      M(i, j, 3) = floor(sin(axisToAngle(i)) * ceil);
    endfor
    disp(i);
  endfor
  imwrite(uint8(M), "img1.png", 'Quality', 100);
endfunction

function ang = axisToAngle(x)
  ang = deg2rad(x)/6.28319;

endfunction
