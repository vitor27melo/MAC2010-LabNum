# EP3 - MAC0210 - Function file calculateError.m
# Autor: Vítor Carvalho de Melo (nUSP 10723753)

function calculateError(originalImg, decompressedImg)
  originalImgFile = imread(originalImg);
  decomppressedImgFile = imread(decompressedImg);

  errR = calculateColorErr(originalImgFile, decomppressedImgFile, "red");
  errG = calculateColorErr(originalImgFile, decomppressedImgFile, "green");
  errB = calculateColorErr(originalImgFile, decomppressedImgFile, "blue");

  err = (errR + errG + errB) / 3;
  disp(err);
endfunction

function colorErr = calculateColorErr(origImg, decompImg, color)
  if (strcmpi(color, "red"))        color = 1;
  elseif (strcmpi(color, "green"))  color = 2;
  elseif (strcmpi(color, "blue"))   color = 3;
  endif

  # A imagem descomprimida pode possuir uma linha e uma coluna de pixels a menos
  p = size(decompImg)(1);
  for i = 1:p;
    for j = 1:p;
      origR(i, j) = double(origImg(i+1, j+1, color));
      decompR(i, j) = double(decompImg(i, j, color));
    endfor
  endfor
  colorErr = norm(origR-decompR, 2)/norm(origR, 2);
endfunction



