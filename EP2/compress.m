# EP3 - MAC0210 - Function file compress.m
# Autor: Vítor Carvalho de Melo (nUSP 10723753)

function compress(originalImg, k)
  origImgFile = imread(originalImg);
  # Número de linhas da imagem original(assumindo-a quadrada)
  p = size(origImgFile)(1);
  # Número de linhas da imagem comprimida
  n = floor((p+k)/(1+k));
  # Inicializando matriz da imagem comprimida
  img = zeros(n, n, 3);
  for i = 0:n-1;
    for j = 0:n-1;
      # Fórmula derivada da condição "i (equiv) mod k+1"
      # Ref: https://en.wikipedia.org/wiki/Congruence_relation
      compressedImg(i+1, j+1, :) = origImgFile(i*(k+1)+1, j*(k+1)+1, :);
    endfor
  endfor
  # O valor default para a opção "Quality" é 75
  # Ref: https://octave.sourceforge.io/octave/function/imwrite.html
  imwrite(uint8(compressedImg), "compressed.png", "Quality", 100);
endfunction
