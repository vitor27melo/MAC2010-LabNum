# EP3 - MAC0210 - Function file decompress.m
# Autor: Vítor Carvalho de Melo (nUSP 10723753)

function decompress(compressedImg, method, k, h)
  compressedImgFile = imread(compressedImg);
  # Número de linhas da imagem original(assumindo-a quadrada)
  p = size(compressedImgFile)(1);
  # Número de linhas da imagem descomprimida
  n = p+(p-1)*k;

  # Inicializando matriz da imagem descomprimida
  # com valores acima do máximo (255) para diferenciá-los de r/g/b 0
  decompImg = zeros(n, n, 3)+256;
  for i = 0:p-1;
    for j = 0:p-1;
      # Aloca os pixels da imagem original
      decompImg(i*(k+1)+1, j*(k+1)+1, :) = compressedImgFile(i+1,j+1,:);
    endfor
  endfor
  if(method == 1)
    decompImgFile = bilinear(decompImg, n, h, k);
  elseif(method == 2)
    decompImgFile = bicubic(decompImg, n, h, k);
  else
    disp("Please choose between the bilinear (1) and bicubic (2) methods.")
    return
  endif
  # O valor default para a opção "Quality" é 75
  # Ref: https://octave.sourceforge.io/octave/function/imwrite.html
  imwrite (uint8(decompImgFile), "decompressed.png", "Quality", 100);
endfunction

function img = bilinear(decompImg, n, h, k)
  M = [1,0,0,0;
       1,0,h,0;
       1,h,0,0;
       1,h,h,h*h];
  img = decompImg;
  # Vermelho para Q_ij
  img = interpolateColorBilinear(img, n, M, k, "red");
  # Verde para Q_ij
  img = interpolateColorBilinear(img, n, M, k, "green");
  # Azul para Q_ij
  img = interpolateColorBilinear(img, n, M, k, "blue");
endfunction

function img = interpolateColorBilinear(img, n, M, k, color)
  if (strcmpi(color, "red"))        color = 1;
  elseif (strcmpi(color, "green"))  color = 2;
  elseif (strcmpi(color, "blue"))   color = 3;
  endif

  for i = 1:k+1:n-1;
    for j = 1:k+1:n-1;
      F = zeros(4);
      F(1) = img(i,j,color);
      F(2) = img(i,j+k+1,color);
      F(3) = img(i+k+1,j,color);
      F(4) = img(i+k+1,j+k+1,color);
      A = inv(M)*F;
      # Itera por todos os pixels
      for x = i:i+k+1;
        for y = j:j+k+1;
          # Verifica se aquele pixel (na cor correta) está marcado p/ ser preenchido
          if (img(x,y,color) == 256);
            img(x,y,color) = A(1) + A(2)*(x-i) + A(3)*(y-j) + A(4)*(x-i)*(y-j);
          endif
        endfor
      endfor
    endfor
  endfor
endfunction

function img = bicubic(decompImg, n, h, k)
  img = decompImg;
  B = inv([1,  0,  0,   0;
           1,  h,  h^2, h^3;
           0,  1,  0,   0;
           0,  1,  2*h, 3*(h^2)]);

  for i = 1:k+1:n-1;
    for j = 1:k+1:n-1;
      F = zeros(4,4,3);

      # Sub-matriz 2x2 superior esquerda
      F(1,1,:) = img(i,j,:);
      F(2,1,:) = img(i+k+1,j,:);
      F(1,2,:) = img(i,j+k+1,:);
      F(2,2,:) = img(i+k+1,j+k+1,:);

      # Sub-matriz 2x2 superior direita
      F(1,3,:) = partialDeriv(img, i, j, h, k, n, "y");
      F(2,3,:) = partialDeriv(img, i+k+1, j, h, k, n, "y");
      F(1,4,:) = partialDeriv(img, i, j+k+1, h, k, n, "y");
      F(2,4,:) = partialDeriv(img, i+k+1, j+k+1, h, k, n, "y");

      # Sub-matriz 2x2 inferior esquerda
      F(3,1,:) = partialDeriv(img, i, j, h, k, n, "x");
      F(4,1,:) = partialDeriv(img, i+k+1, j, h, k, n, "x");
      F(3,2,:) = partialDeriv(img, i, j+k+1, h, k, n, "x");
      F(4,2,:) = partialDeriv(img, i+k+1, j+k+1, h, k, n, "x");

      # Sub-matriz 2x2 inferior direita
      F(3,3,:) = mixedDeriv(img, i, j, h, k, n);
      F(4,3,:) = mixedDeriv(img, i+k+1, j, h, k, n);
      F(3,4,:) = mixedDeriv(img, i, j+k+1, h, k, n);
      F(4,4,:) = mixedDeriv(img, i+k+1, j+k+1, h, k, n);

      for x = i : i+k+1;
        for y = j : j+k+1;
          if(img(x,y,1) == 256);
            # Vermelho para Q_xy
            img(x,y,1) = interpolateColorBicubic(img, B, F, x, y, i, j, "red");
            # Verde para Q_xy
            img(x,y,2) = interpolateColorBicubic(img, B, F, x, y, i, j, "green");
            # Azul para Q_xy
            img(x,y,3) = interpolateColorBicubic(img, B, F, x, y, i, j, "blue");
         endif
        endfor
      endfor
    endfor
  endfor
endfunction

function pixelColor = interpolateColorBicubic(img, B, F, x, y, i, j, color)
  if (strcmpi(color, "red"))        color = 1;
  elseif (strcmpi(color, "green"))  color = 2;
  elseif (strcmpi(color, "blue"))   color = 3;
  endif

  A = B * F(:,:,color) * B';
  pixelColor = [1,(x-i),(x-i)^2,(x-i)^3]*A*[1; y-j; (y-j)^2; (y-j)^3];
endfunction

function derivative = partialDeriv(img, x, y, h, k, n, axis)
  # Nas "bordas" da imagem em relação ao eixo "axis",
  # calcula-se a derivada apenas "para frente" ou apenas "para trás".
  #Caso contrário, calcula-se a diferença centralizada
  if     (axis == "x" && x == 1)
    x_plus = k+1; y_plus = 0; x_minus = 0; y_minus = 0; dist = h;
  elseif (axis == "x" && x == n)
    x_plus = 0; y_plus = 0; x_minus = -1-k; y_minus = 0; dist = h;
  elseif (axis == "x")
    x_plus = k+1; y_plus = 0; x_minus = -1-k; y_minus = 0; dist = 2*h;
  elseif (axis == "y" && y == 1)
    x_plus = 0; y_plus = k+1; x_minus = 0; y_minus = 0; dist = h;
  elseif (axis == "y" && y == n)
    x_plus = 0; y_plus = 0; x_minus = 0; y_minus = -1-k; dist = h;
  elseif (axis == "y")
    x_plus = 0; y_plus = k+1; x_minus = 0; y_minus = -1-k; dist = 2*h;
  endif

  derivative = (img(x+x_plus, y+y_plus, :) - img(x+x_minus, y+y_minus, :))/dist;
endfunction


function derivative = mixedDeriv(img, x, y, h, k, n)
  if(x == 1)
    derivative = (partialDeriv(img, x, y, h, k, n, "y") - partialDeriv(img, x+k+1, y, h, k, n, "y"))/h;
  elseif(x == n)
    derivative = (partialDeriv(img, x-k-1, y, h, k, n, "y") - partialDeriv(img, x, y, h, k, n, "y"))/h;
  else
    derivative = (partialDeriv(img, x-k-1, y, h, k, n, "y") - partialDeriv(img, x+k+1, y, h, k, n, "y"))/2*h;
  endif
endfunction
