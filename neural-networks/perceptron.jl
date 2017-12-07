pattern0 = [0 1 1 1 0;
            1 0 0 0 1;
            1 0 0 0 1;
            1 0 0 0 1;
            1 0 0 0 1;
            0 1 1 1 0]

pattern1 = [0 0 1 0 0;
            0 1 1 0 0;
            0 0 1 0 0;
            0 0 1 0 0;
            0 0 1 0 0;
            1 1 1 1 1]

pattern2 = [0 1 1 1 0;
            0 1 0 1 0;
            0 0 0 1 0;
            0 0 1 0 0;
            0 1 0 0 0;
            1 1 1 1 1]

pattern3 = [0 1 1 1 1;
            0 0 0 0 1;
            0 1 1 1 1;
            0 0 0 0 1;
            0 0 0 0 1;
            0 1 1 1 1]

pattern4 = [1 0 0 1 0;
            1 0 0 1 0;
            1 0 0 1 0;
            1 1 1 1 0;
            0 0 0 1 0;
            0 0 0 1 0]

pattern5 = [0 1 1 1 1;
            0 1 0 0 0;
            0 1 1 1 1;
            0 0 0 0 1;
            0 0 0 0 1;
            0 1 1 1 1]

# transform matrix in array
function snake(pattern)
  hpattern = zeros(Int,1,30)
  counter = 1
  for i in 1:6
    for j in 1:5
      hpattern[counter] = pattern[i, j]
      counter += 1
    end
  end

  return hpattern
end

# Training Matrix: w0 to w30 and y value
TM = [hcat(hcat( 1, snake(pattern0)), 0);
      hcat(hcat( 1, snake(pattern1)), 1)];

# Learning weights from w0 to w31
W = zeros(Int,1,31)

function training(W, TM)
  epoch = 0
  for i in 1:1000
  end
end

# Receive training row and actual weights
function sumXW(X, W)
  sum = 0
  for i in 1:31
    sum += X[i]*W[i]
  end
  return sum
end
