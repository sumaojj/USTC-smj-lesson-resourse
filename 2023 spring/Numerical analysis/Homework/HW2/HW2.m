N_vector = [5, 10, 20, 40];

for i = 1:length(N_vector)
    N = N_vector(i);
    % create the intermediary vector with size N and vector x2=
    x1 = ones(N + 1, 1);
    x2 = ones(N + 1, 1);

    for j = 1:N + 1
        x1(j) = 1 + 2 * (j - 1) / N;
        x2(j) = -cos(pi * (2 * i - 1) / 2 * (N + 1));
    end

    y1 = myfunc(x1);
    y2 = myfunc(x2);
    %calculate the intermediary with myfunc
    for j = 1:N + 1

        for k = N + 1:j
            y1(k) = (y1(k) - y1(k - 1)) / (x1(k) - x1(k - j));
            y2(k) = (y2(k) - y2(k - 1)) / (x2(k) - x2(k - j));
        end

    end

    %calculate  the polynomial

    fx1 = y(N + 1);
    fx2 = y(N + 1);

    for j = N + 1:1
        fx1 = y(j - 1) + (x - x1(j - 1)) * fx;
        fx2 = y(j - 1) + (x - x2(j - 1)) * fx;
    end

    %calculate the error
    z = ones (101, 1);

    for j = 1:101
        z(j) = j / 50 - 1;
    end

    error1 = ones(101, 1);
    error2 = ones(101, 1);

    for j = 1:101
        error1(j) = abs(fx1 - myfunc(z(j)));
        error2(j) = abs(fx2 - myfunc(z(j)));
    end

    %for every N, ouput max error
    max_error1 = max(error1);
    max_error2 = max(error2);
    fprintf('N = %d, max_error1 = %f, max_error2 = %f\n', N, max_error1, max_error2);
    %plot the graph with N = 20

    if N == 20
        figure;
        plot(z, error1, 'r');
        hold on;
        plot(z, error2, 'b');
        title('Error of the polynomial interpolation');
        xlabel('x');
        ylabel('error');
        legend('x1', 'x2');
    end

end
