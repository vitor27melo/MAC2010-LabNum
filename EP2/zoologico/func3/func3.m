function func3()
  n = 600;
  M = ones(n, n, 3);
  for i = 1:n
    for j = 1:n
      if (i < 301)
        M(i, j, 1) = floor((axisToAngle(2*i) + axisToAngle(j/2)) * 255);
        M(i, j, 2) = floor((axisToAngle(i) + axisToAngle(j))  * 255);
        M(i, j, 3) = floor((axisToAngle(i/2) + axisToAngle(2*i)) * 255);
      else
        M(i, j, 3) = floor((axisToAngle(2*i)) * 255);
        M(i, j, 2) = floor((axisToAngle(600-i) + axisToAngle(600-j))  * 255);
        M(i, j, 1) = floor((axisToAngle(i/2)) * 255);
      endif

    endfor
  endfor
  imwrite(uint8(M), "img.png", 'Quality', 100);
endfunction

function ang = axisToAngle(x)
  # Limitando o resultado de 0 a 1
  ang = deg2rad(x)/6.28319;
endfunction
