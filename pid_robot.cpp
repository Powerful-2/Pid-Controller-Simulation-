#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

int main()
{
    // 1. PID gains
    double Kp = 1.60; // Proportional gain
    double Ki = 0.40; // Integral gain
    double Kd = 0.12; // Derivative gain

    // 2. Simulation parameters
    double setpoint = 100.0; // Target position (cm)
    double pv = 0.0;         // Current position (process variable)
    double dt = 0.1;         // Time step (seconds)
    int total_steps = 150;   // Total simulation steps (15 seconds)
    int print_every = 10;    // Print one row every 10 steps

    // 3. Controller memory
    double integral = 0.0;
    double prev_error = setpoint - pv; // Start equal to the first error to avoid a derivative spike
    double peak = pv;

    // 4. Header
    cout << "=====================================================================\n";
    cout << " PID Feedback Controller Simulation for Robot Arm Tracking\n";
    cout << "=====================================================================\n";
    cout << "Setpoint: " << setpoint << " cm | dt: " << dt << " s | Steps: " << total_steps << "\n";
    cout << "Gains: Kp = " << Kp << ", Ki = " << Ki << ", Kd = " << Kd << "\n";
    cout << "---------------------------------------------------------------------\n";
    cout << "Step | Position | Error(cm) | P-Term | I-Term | D-Term | Motor Output\n";
    cout << "---------------------------------------------------------------------\n";

    // 5. Simulation loop
    cout << fixed << setprecision(2);
    double error = 0.0;
    for (int step = 1; step <= total_steps; ++step)
    {
        error = setpoint - pv;
        integral += error * dt;
        double derivative = (error - prev_error) / dt;

        double p_out = Kp * error;
        double i_out = Ki * integral;
        double d_out = Kd * derivative;
        double total_output = p_out + i_out + d_out;

        if (step == 1 || step % print_every == 0)
        {
            cout << setw(4) << step << " | "
                 << setw(8) << pv << " | "
                 << setw(9) << error << " | "
                 << setw(6) << p_out << " | "
                 << setw(6) << i_out << " | "
                 << setw(6) << d_out << " | "
                 << setw(12) << total_output << "\n";
        }

        // Simple model of the arm's response to the motor output
        pv += total_output * 0.08;
        if (pv > peak)
            peak = pv;
        prev_error = error;
    }

    // 6. Result summary (calculated, not assumed)
    double final_error = setpoint - pv;
    cout << "---------------------------------------------------------------------\n";
    cout << "Final position: " << pv << " cm | Final error: " << final_error << " cm\n";
    cout << "Peak position: " << peak << " cm | Overshoot: " << (peak - setpoint) << " cm\n";
    if (fabs(final_error) < 1.0)
        cout << "STATUS: Settled within 1 cm of the target.\n";
    else
        cout << "STATUS: Not yet within 1 cm of the target.\n";
    cout << "=====================================================================\n";
    return 0;
}
