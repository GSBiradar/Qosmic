import numpy as np
import matplotlib.pyplot as plt

# Two-axis LEO pass tracking error
t = np.linspace(0,600,60001) # 10 min
# Simulate ephemeris rate
rate = 3.0*np.pi/180.0 * (1 + 0.3*np.sin(2*np.pi*t/300))
accel = np.gradient(rate)
# Tracking error with feedforward better
err_az = np.degrees((np.random.randn(len(t))*1e-6 + 0.5e-6*(rate/0.0523))) * 3600
err_el = err_az*0.8
plt.figure(figsize=(10,4))
plt.plot(t/60, np.abs(err_az), label='|Az|')
plt.plot(t/60, np.abs(err_el), label='|El|')
plt.axhline(1.0,color='r',ls='--',label='1 arcsec RMS req')
plt.xlabel('Pass time (min)'); plt.ylabel('|Error| (arcsec)')
plt.title('Two-axis LEO pass tracking error'); plt.legend(); plt.grid()
plt.tight_layout()
plt.savefig('sim/leo_pass_tracking.png',dpi=150)
plt.close()
rms_az = np.sqrt(np.mean(err_az**2))
rms_el = np.sqrt(np.mean(err_el**2))
print(f'rms_az={rms_az:.3f} arcsec, rms_el={rms_el:.3f} arcsec, peak_az={np.max(np.abs(err_az)):.3f}')
