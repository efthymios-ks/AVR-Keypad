# AVR Keypad Library  

---

**Description:**  
A library to control matrix keypads using AVR microcontrollers.  
+ **The keypad pins can be configured to any pin in any port in any sequence.**  
+ Supports 3x3, 3x4 and 4x4 keypads.  
+ Can perform immediate readings, which are noise-susceptible, or debounced readings using a timer interrupt.
+ Functions include:  
  + Read 
  + Wait till key pressed  
  + Wait till key released  
   _Functions can be used with or without debounce._  
   _Read the bottom of "Keypad.h" to see all functions available._  
+ My custom I/O macros are required and are included.  

---  

**Memory usage:**  
+ Program: 9/12/16 bytes  
  + Keypad layout: 9/12/16 bytes (3x3, 3x4, 4x4 layout)  
+ Data: 10 bytes  
  + Noise filtering array: 10 bytes (default)  

**Compiler:**  
AVR-GCC  
  
**Optimization Level:**  
Optimize (-O1)  
  
--- 
  
![picture alt](https://raw.githubusercontent.com/efthymios-ks/AVR-Keypad-Library/master/Images/Demonstration.png)  
![picture alt](https://raw.githubusercontent.com/efthymios-ks/AVR-Keypad-Library/master/Images/Pinout.png)  
![picture alt](https://raw.githubusercontent.com/efthymios-ks/AVR-Keypad-Library/master/Images/Mapping.png)  
![picture alt](https://raw.githubusercontent.com/efthymios-ks/AVR-Keypad-Library/master/Images/Key%20Codes.png)  
--- 
