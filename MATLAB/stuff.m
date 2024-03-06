esko = [4.21, 4.69, 5.43, 5.739, 5.929, 7.4;
        31, 28.5, 25.4, 24.16, 24.2, 23.5];
arc = [4.7, 4.9, 6.65, 3.15, 5.7, 7.5, 4.495;
       25.8, 24.9, 23.8, 31.2, 24.1, 23.4, 26.5];
decc = [4.8, 4;
        26.2, 29.66];

% Set parameters
a = 1.2;
b = -6.6;
c = 23.275;


deltac = 1.025
deltab = 0.3
% Define the range of x values for the y function
x = linspace(3.5, 8, 100); % Adjusted the upper limit of x to ensure y < 30

% Calculate y values using the provided equation
y = exp(-a * x - b) + c;

% Plotting the points and the function
plot(x, y, 'DisplayName', 'Function y'); % Plot y against x with a display name
hold on;
plot(esko(1,:), esko(2,:), 'o', 'DisplayName', 'Esko'); 
plot(arc(1,:), arc(2,:), 'x', 'DisplayName', 'Arc'); 
plot(decc(1,:), decc(2,:), '*', 'DisplayName', 'Decc'); 
hold off;

% Add legend
legend('Location', 'best'); % Add legend with the best position
