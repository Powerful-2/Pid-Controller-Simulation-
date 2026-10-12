#include <iostream>
#include <cmath>
#include <iomanip>
#include <limits>

using namespace std;

const double PI = 3.14159265358979323846;

void showMenu();
void solvePID();
void solveRLC();
void solvePipeFlow();

int main()
{
    int choice = 0;

    cout << "===========================================\n";
    cout << "   MULTI-DISCIPLINARY ENGINEERING BOARD    \n";
    cout << "===========================================\n";

    do
    {
        showMenu();
        cout << "Enter your choice (1-4): ";
        if (!(cin >> choice))
        {
            // Non-numeric input: clear the error and discard the bad line
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            choice = 0;
        }
        cout << "\n";

        switch (choice)
        {
        case 1:
            solvePID();
            break;
        case 2:
            solveRLC();
            break;
        case 3:
            solvePipeFlow();
            break;
        case 4:
            cout << "Exiting Engineering Board. Goodbye!\n";
            break;
        default:
            cout << "Invalid choice! Please select between 1 and 4.\n\n";
        }
    } while (choice != 4);

    return 0;
}

void showMenu()
{
    cout << "-------------------------------------------\n";
    cout << " Select an Engineering Module to Solve:\n";
    cout << "-------------------------------------------\n";
    cout << " 1. Robotics & Controls: PID Controller Simulation\n";
    cout << " 2. Electrical: RLC Circuit AC Impedance Calculator\n";
    cout << " 3. Fluid Mechanics: Pipe Friction Loss\n";
    cout << " 4. Exit Program\n";
    cout << "-------------------------------------------\n";
}

void solvePID()
{
    cout << ">>> MODULE 1: PID CONTROLLER SIMULATION <<<\n";
    double Kp = 1.5, Ki = 0.5, Kd = 0.1, setpoint, pv;
    int steps;
    cout << "Enter target value (Setpoint): ";
    cin >> setpoint;
    cout << "Enter current starting value (Process Variable): ";
    cin >> pv;
    cout << "Enter simulation steps (e.g., 5): ";
    cin >> steps;

    if (cin.fail() || steps < 1)
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Enter numbers only, with at least 1 step.\n\n";
        return;
    }

    double integral = 0.0, prev_error = 0.0, dt = 0.1;
    cout << "\nStep | Error     | P-Term    | I-Term    | D-Term    | Control Output\n";
    cout << "---------------------------------------------------------------------\n";
    for (int i = 1; i <= steps; ++i)
    {
        double error = setpoint - pv;
        integral += error * dt;
        double derivative = (error - prev_error) / dt;
        double output = (Kp * error) + (Ki * integral) + (Kd * derivative);
        cout << setw(4) << i << " | " << setw(9) << error << " | " << setw(9) << Kp * error
             << " | " << setw(9) << Ki * integral << " | " << setw(9) << Kd * derivative
             << " | " << setw(14) << output << "\n";
        pv += output * 0.4;
        prev_error = error;
    }
    cout << "---------------------------------------------------------------------\n\n";
}

void solveRLC()
{
    cout << ">>> MODULE 2: RLC CIRCUIT AC IMPEDANCE <<<\n\n";
    double R, L, C, freq;
    cout << "Enter Resistance R (Ohms): ";
    cin >> R;
    cout << "Enter Inductance L (Henries): ";
    cin >> L;
    cout << "Enter Capacitance C (Farads): ";
    cin >> C;
    cout << "Enter AC Frequency f (Hz): ";
    cin >> freq;

    if (cin.fail() || C <= 0 || freq <= 0)
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Capacitance and frequency must be greater than 0.\n\n";
        return;
    }

    cout << "\n=========================================================\n";
    cout << "               COMPREHENSIVE SOLUTION SHEET              \n";
    cout << "=========================================================\n";

    // STEP 1: Angular Frequency
    double omega = 2.0 * PI * freq;
    cout << "[STEP 1] Calculate Angular Frequency (w):\n";
    cout << "         Formula : w = 2 * pi * f\n";
    cout << "         Working : w = 2 * 3.14159 * " << freq << "\n";
    cout << "         Result  : w = " << omega << " rad/s\n\n";

    // STEP 2: Reactances
    double X_L = omega * L;
    double X_C = 1.0 / (omega * C);
    cout << "[STEP 2] Calculate Inductive & Capacitive Reactances:\n";
    cout << "         Formula : X_L = w * L  |  X_C = 1 / (w * C)\n";
    cout << "         Working : X_L = " << omega << " * " << L << "\n";
    cout << "                   X_C = 1 / (" << omega << " * " << C << ")\n";
    cout << "         Result  : X_L = " << X_L << " Ohms\n";
    cout << "                   X_C = " << X_C << " Ohms\n\n";

    // STEP 3: Net Reactance
    double X_total = X_L - X_C;
    cout << "[STEP 3] Calculate Net Reactance (X_total):\n";
    cout << "         Formula : X_total = X_L - X_C\n";
    cout << "         Working : X_total = " << X_L << " - " << X_C << "\n";
    cout << "         Result  : X_total = " << X_total << " Ohms\n\n";

    // STEP 4: Total Impedance
    double Z = sqrt((R * R) + (X_total * X_total));
    cout << "[STEP 4] Calculate Total Impedance Magnitude (|Z|):\n";
    cout << "         Formula : |Z| = sqrt(R^2 + X_total^2)\n";
    cout << "         Working : |Z| = sqrt(" << R << "^2 + (" << X_total << ")^2)\n";
    cout << "                   |Z| = sqrt(" << (R * R) << " + " << (X_total * X_total) << ")\n";
    cout << "         Result  : |Z| = " << Z << " Ohms\n\n";

    // STEP 5: Phase Angle
    double phase_deg = atan2(X_total, R) * (180.0 / PI);
    cout << "[STEP 5] Calculate Phase Angle (theta):\n";
    cout << "         Formula : theta = arctan(X_total / R) * (180 / pi)\n";
    cout << "         Working : theta = arctan(" << X_total << " / " << R << ")\n";
    cout << "         Result  : theta = " << phase_deg << " degrees\n";
    cout << "=========================================================\n\n";
}

void solvePipeFlow()
{
    cout << ">>> MODULE 3: PIPE FRICTION LOSS <<<\n\n";
    double length, diameter, velocity, friction_factor, g = 9.81;
    cout << "Enter pipe length (meters): ";
    cin >> length;
    cout << "Enter pipe inner diameter (meters): ";
    cin >> diameter;
    cout << "Enter fluid velocity (m/s): ";
    cin >> velocity;
    cout << "Enter estimated Darcy friction factor (e.g., 0.02): ";
    cin >> friction_factor;

    if (cin.fail() || diameter <= 0)
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Diameter must be greater than 0.\n\n";
        return;
    }

    cout << "\n=========================================================\n";
    cout << "               COMPREHENSIVE SOLUTION SHEET              \n";
    cout << "=========================================================\n";

    // STEP 1: Velocity Squared
    double v_squared = velocity * velocity;
    cout << "[STEP 1] Calculate Velocity Squared (v^2):\n";
    cout << "         Working : " << velocity << "^2\n";
    cout << "         Result  : v^2 = " << v_squared << " m^2/s^2\n\n";

    // STEP 2: Geometric Ratio (L/D)
    double ld_ratio = length / diameter;
    cout << "[STEP 2] Calculate Pipe Length-to-Diameter Ratio (L/D):\n";
    cout << "         Working : " << length << " / " << diameter << "\n";
    cout << "         Result  : L/D = " << ld_ratio << "\n\n";

    // STEP 3: Kinetic Energy Denominator (2 * g)
    double two_g = 2.0 * g;
    cout << "[STEP 3] Calculate Gravity Term (2 * g):\n";
    cout << "         Working : 2 * 9.81\n";
    cout << "         Result  : 2g = " << two_g << " m/s^2\n\n";

    // STEP 4: Total Head Loss (Darcy-Weisbach Equation)
    double head_loss = friction_factor * ld_ratio * (v_squared / two_g);
    cout << "[STEP 4] Calculate Head Loss (h_f):\n";
    cout << "         Formula : h_f = f * (L/D) * (v^2 / 2g)\n";
    cout << "         Working : h_f = " << friction_factor << " * " << ld_ratio << " * (" << v_squared << " / " << two_g << ")\n";
    cout << "         Result  : h_f = " << head_loss << " meters of fluid\n";
    cout << "=========================================================\n\n";
}
