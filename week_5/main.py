import numpy as np
from scipy.optimize import minimize
import math
import matplotlib.pyplot as plt

# X_INS
X = np.array([
    0.0, 0.005, 0.01, 0.015, 0.02, 0.025, 0.03, 0.035, 0.04, 0.045, 0.05,
    0.055, 0.06, 0.065, 0.07, 0.075, 0.08, 0.085, 0.09, 0.095, 0.1, 0.105,
    0.11, 0.115, 0.12, 0.125, 0.13, 0.135, 0.14, 0.145, 0.15, 0.155, 0.16,
    0.165, 0.17, 0.175, 0.18, 0.185, 0.19, 0.195, 0.2, 0.205, 0.21, 0.215,
    0.22, 0.225, 0.23, 0.235, 0.24, 0.245, 0.25
  ]);

# Y_Training
Y = np.array([
  10.198039027185569, 10.339324442344374, 10.442714214341391,
  10.505105417386023, 10.52455362464219, 10.500441450485722,
  10.4335335370236, 10.325908556769988, 10.180779867363889,
  10.002234320137994, 9.794928864398871, 9.563785369537165,
  9.31371695113202, 9.049407437122607, 8.775153190732745,
  8.494766136276018, 8.211529887667988, 7.928197445359825,
  7.647018299040706, 7.36978396146955, 7.097883046194359,
  6.832359311259672, 6.573968210850365, 6.32322923357303,
  6.080472613113552, 5.845879910381798, 5.619518557921894,
  5.401370806363354, 5.191357690171117, 4.989358693348711,
  4.795227788056323, 4.608806470641276, 4.42993435055386,
  4.2584577706991995, 4.094236860241398, 3.9371513463315315,
  3.7871053808457034, 3.644031571632328, 3.507894343750633,
  3.3786926931679306, 3.2564623319677435, 3.141277159625666,
  3.033249930077024, 2.9325319221410635, 2.839311367593713,
  2.7538103569913344, 2.676279942593332, 2.606993207773451,
  2.5462361902382327, 2.494296743043913, 2.4514516892273
]);
  
def a(x):
    return 1 / (1 + math.exp(-x));
  
def y_out(x_in, weight_array):
  sum_result = 0;
  for k in range(0, 4):
    sum_result += weight_array[k+10]*a(weight_array[k]*x_in + weight_array[k+5]);
  
  result = weight_array[15] + sum_result;
  return result;

def optimization_function(weight_array):
  sum_result = 0;
  
  for k in range(0, 50):
      x_k = X[k];  
      y_training_k = Y[k];  
      sum_result += (y_out(x_k, weight_array)-y_training_k)**2;

  result = (1 / 51) * sum_result;
  return result


# Starting point. 
# ===============

if __name__ == '__main__':
  while(True):
    weight_array = np.random.uniform(low=-30, high=30, size=(16,));
    simplex = minimize(
        optimization_function,  # Objective function to be minimized
        weight_array,  # Initial guess or starting point
        method="Nelder-Mead",  # Optimization method
        options={
            # 'xtol': 1e-15,  # Tolerance for termination by the change of the independent variables
            'maxfev': 1e10,  # Maximum number of function evaluations
            'disp': True,  # If True, print convergence messages
            # 'ftol': 1e-7  # Tolerance for termination by the change of the cost function
        }
    )
    
    optimized_weights = simplex.x;
    minimum_value = simplex.fun
    success = simplex.success

    if minimum_value < 10e-3:
      break;

  print("============ Results ============")
  print("\nOptimized weights:")
  print("[", end="")
  for i in range(len(optimized_weights)):
      print(' {:.15f}'.format(optimized_weights[i]), end="")
      if i < len(optimized_weights) - 1:
          print(",", end="")
  print("]")

  print("Cost is: " + str(minimum_value))

  x_ins = np.arange(0., 0.255, 0.005);

  y_train = Y;

  yOut = [];
  for x in x_ins:
    yOut.append(y_out( x_in=x ,weight_array=optimized_weights));
    
  # print("Length of x_ins:", len(x_ins))
  # print("Length of x_train:", len(y_train))

  plt.figure(dpi=300, figsize=[10.8, 9.60])
  plt.grid(color='lightgray', linestyle='-', linewidth=2)

  # Plotting y_train with blue solid line
  plt.plot(x_ins, y_train, label='y_train', color='blue', linestyle='-', linewidth=2)

  # Plotting y_out with red dashed line
  plt.plot(x_ins, yOut, label='y_out', color='red', linestyle='--', linewidth=2)

  # Adding labels and legend
  plt.xlabel('X')
  plt.ylabel('Y')
  plt.title('Graph')
  plt.legend()
  plt.savefig("graph.png")
  plt.show()
