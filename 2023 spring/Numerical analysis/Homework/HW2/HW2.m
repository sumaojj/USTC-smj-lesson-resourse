N_vector = [5, 10, 20, 40];

for i = 1:length(N_vector)
    N = N_vector(i);
    % create the intermediary vector with size N and vector x2=
    x1 = ones(N + 1, 1);
    x2 = ones(N + 1, 1);
    y1 = ones(N + 1, 1);
    y2 = ones(N + 1, 1);

    for j = 1:N + 1
        x1(j) = 1 - 2 * (j - 1) / N;
        x2(j) = -cos(pi * (2 * j - 1) / (2 * (N + 1)));
        y1(j) = myfunc(x1(j));
        y2(j) = myfunc(x2(j));
    end

    %calculate the intermediary with myfunc
    for j = 1:N

        for k = N + 1:j + 1
            y1(k) = (y1(k) - y1(k - 1)) / (x1(k) - x1(k - j));
            y2(k) = (y2(k) - y2(k - 1)) / (x2(k) - x2(k - j));
        end

    end

    % %reverse the vector
    % y1 = flipud(y1);
    % y2 = flipud(y2);

    %calculate the error
    z = ones (101, 1);

    for j = 1:101
        z(j) = (j - 1) / 50 - 1;
    end

    error1 = ones(101, 1);
    error2 = ones(101, 1);

    for j = 1:101
        error1(j) = abs(myfunc(z(j)) - polyval(y1, z(j)));
        error2(j) = abs(myfunc(z(j)) - polyval(y2, z(j)));
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
