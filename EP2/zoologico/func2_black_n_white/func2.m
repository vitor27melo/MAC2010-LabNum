function func2()
  n = 720;
  M = ones(n, n, 3);
  for i = 1:n
    for j = 1:n
      M(i, j, 1) = floor((cos(axisToAngle(i)) + sin(axisToAngle(j)))/2 * 255);
      M(i, j, 2) = floor((cos(axisToAngle(i)) + sin(axisToAngle(j)))/2 * 255);
      M(i, j, 3) = floor((cos(axisToAngle(i)) + sin(axisToAngle(j)))/2 * 255);
    endfor
  endfor
  imwrite(uint8(M), "img.png", 'Quality', 100);
endfunction

function ang = axisToAngle(x)
  # Limitando o resultado de 0 a 1
  ang = deg2rad(x)/6.28319;
endfunction
