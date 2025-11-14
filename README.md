# weather-station
Simple Weather Station prototype using STM32

<img width="604" height="534" alt="image" src="https://github.com/user-attachments/assets/13080c82-c820-4ca3-bb62-7502244c41ba" /> <br>
The system is divided into three main functional blocks: data acquisition, data processing, and output control. The data acquisition block consists of all sensors connected to the STM32. Environmental parameters are sensed and converted into electrical signals. The processing block, handled by the STM32 firmware, reads the ADC values and digital data. It converts them into physical units and applies scaling formulas or calibration constants. The output control block then formats this processed data and updates the LCD screen with the latest readings in real-time.

<br>
Simulation Circuit on Wokwi:<br>
<img width="940" height="498" alt="image" src="https://github.com/user-attachments/assets/3ea3a69a-94d2-4a92-ab81-eb7d4940f4a4" />

Hardware Setup:<br>
<img width="527" height="411" alt="image" src="https://github.com/user-attachments/assets/67bbdc83-9969-4f7a-93e0-8c7c988a9d37" />
