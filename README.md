# Pid-Controller-Simulation-
C++ simulation of a PID controller for robot arm position tracking. Prints error, P/I/D terms, and motor output at each time step.

#include #include #include

using namespace std;

int main() {

// 1. PID Tuning Parameters (Gains)
double Kp = 1.60;  // Proportional Gain
double Ki = 0.40;  // Integral Gain
double Kd = 0.12;  // Derivative Gain


// 2. Simulation System Parameters
double setpoint = 100.0; // Target position in centimeters (e.g., robotic joint angle)
double pv = 0.0;         // Starting position (Process Variable)
double dt = 0.1;         // Sampling time step interval (seconds)

// 3. Controller Tracking Memory States
double integral = 0.0;
double prev_error = 0.0;
int total_steps = 10;    // Total iterations to display

// 4. Print Project Header Interface
cout << "=====================================================================\n";
cout << "        DEPARTMENT OF ENGINEERING -- ROBOTICS SOFTWARE CORNER       \n";
cout << "=====================================================================\n";
cout << "Project Title : PID Feedback Controller Simulation for Robot Arm Tracking\n";
cout << "Target Position (Setpoint): " << setpoint << " cm | Sampling Rate (dt): " << dt << "s\n";
cout << "Configured Gains: Kp = " << Kp << ", Ki = " << Ki << ", Kd = " << Kd << "\n";
cout << "=====================================================================\n\n";

// 5. Print Evaluation Matrix Header
cout << "---------------------------------------------------------------------\n";
cout << "Step | Error(cm) | P-Term    | I-Term    | D-Term    | Motor Output\n";
cout << "---------------------------------------------------------------------\n";

// 6. Execute Simulation Loop
cout << fixed << setprecision(2);
for (int step = 1; step <= total_steps; ++step) {
    // Calculate raw deviation error
    double error = setpoint - pv;
    
    // Accumulate error over time (Integral term)
    integral += error * dt;
    
    // Determine rate of error change (Derivative term)
    double derivative = (error - prev_error) / dt;

    // Compute localized controller component outputs
    double p_out = Kp * error;
    double i_out = Ki * integral;
    double d_out = Kd * derivative;
    
    // Sum total control vector sequence
    double total_output = p_out + i_out + d_out;

    // Print formatted mathematical evaluation matrix line
    cout << setw(4)  << step         << " | " 
         << setw(9)  << error        << " | " 
         << setw(9)  << p_out        << " | " 
         << setw(9)  << i_out        << " | " 
         << setw(9)  << d_out        << " | " 
         << setw(12) << total_output << "\n";

    // Simulate physical mechanical actuator plant response displacement
    pv += total_output * 0.08; 
    
    // Update error state memory tracking variables
    prev_error = error;
}
cout << "---------------------------------------------------------------------\n";
cout << "STATUS: Simulation completed. Final position stabilized near target.\n";
cout << "=====================================================================\n";

return 0;
}
