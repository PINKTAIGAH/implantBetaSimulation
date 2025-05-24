import numpy as np
from tqdm import tqdm
import numpy.random as nr
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit
#parameters:
decayrate = 1/10 #Hz
implantrate = 50 #Hz
debug_mode = False

tstart = 0
tend = 100000
dt = 1e-3 #
timestep_array = np.arange(tstart, tend, dt)

spill_on = 1
spill_off = 2

tcorrwindow = 50

def get_time_of_next_implant(tcurr):
    timplant = tcurr + nr.exponential(scale=1/implantrate)
    return timplant

def get_time_of_decay(timplant):
    tbeta = timplant + nr.exponential(scale=1/decayrate)
    return tbeta

def on_or_off_spill(t):
    ncycles = t//(spill_off + spill_on)
    if t - ncycles*(spill_off+spill_on) > spill_on:
        return False
    else:
        return True


implants = [] #(timplant,tbeta)

t = tstart
tlast_implant = 0
time_next_implant = -1
time_of_next_spill_change = spill_on
spill_on_flag = False

# while t < tend:
for _ in tqdm(timestep_array):
    t = t + dt
    if t > time_next_implant and spill_on_flag:
        time_next_implant = get_time_of_next_implant(t)
        if debug_mode:
            print("current implant = ",  t,end=" ")
            print("next implant = ",  time_next_implant)
        time_beta = get_time_of_decay(t)
        implants.append((t,time_beta))
        tlast_implant = t
    
    if t > time_of_next_spill_change:
        if spill_on_flag:
            spill_on_flag = False
            time_of_next_spill_change = t + spill_off
        else:
            spill_on_flag = True
            time_of_next_spill_change = t + spill_on



# time_differences = []
# imps = []
# for implant,time_beta in tqdm(implants):
#     for implant2,time_beta2 in implants:
#             if time_beta2 - implant < - tcorrwindow:
#                  continue
#             elif time_beta2 - implant > tcorrwindow:
#                 continue
#             elif not on_or_off_spill(time_beta2):  
#                 time_differences.append(time_beta2 - implant)
            


# # Assume time_differences is already defined
# counts, bin_edges = np.histogram(time_differences, bins=500)
# bin_centers = 0.5 * (bin_edges[1:] + bin_edges[:-1])

# # Define the exponential model
# def exponential_model_w_forced_backwards(t, A, B, tau):
#     return np.where(t<0,B,B+A*np.exp(-t / tau))

# def exponential_model_wo_forced_backwards(t, A, B, tau):
#     return B+A*np.exp(-t / tau)
    
# # Filter out zero counts to avoid log(0) issues during fitting
# nonzero = counts > 0
# x_fit = bin_centers[nonzero]
# y_fit = counts[nonzero]
# idx_of_pos = int(np.argwhere(x_fit>0)[0])

# # Fit the model
# popt1, pcov1 = curve_fit(exponential_model_w_forced_backwards, x_fit, y_fit, p0=(np.max(y_fit), np.min(y_fit), 10))
# A_fit1, B_fit1, tau_fit1 = popt1

# popt2, pcov2 = curve_fit(exponential_model_wo_forced_backwards, x_fit[idx_of_pos:], y_fit[idx_of_pos:], p0=(np.max(y_fit), np.min(y_fit), 10))
# A_fit2, B_fit2, tau_fit2 = popt2

# # Plot histogram
# plt.bar(bin_centers, counts, width=np.diff(bin_edges), edgecolor='black', alpha=0.6, label='Data')

# # Plot fitted curve
# t_vals = np.linspace(bin_edges[0], bin_edges[-1], 500)
# t_vals_new = np.linspace(0, 50, 500)
# plt.plot(t_vals, exponential_model_w_forced_backwards(t_vals, A_fit1, B_fit1, tau_fit1), 'r-', label=f'Fit: $A e^{{-t/\\tau}}$\n$\\tau$ (fixed B) = {tau_fit1:.3f}s')
# # plt.plot(t_vals_new, exponential_model_wo_forced_backwards(t_vals_new, A_fit2, B_fit2, tau_fit2), 'b--', label=f'Fit: $A e^{{-t/\\tau}}$\n$\\tau$ (free B) = {tau_fit2:.3f}s')

# # Labels and legend
# plt.xlabel('Time (s)')
# plt.ylabel('Counts')
# plt.title('Exponential Fit to Time Differences')
# plt.legend()
# plt.show()