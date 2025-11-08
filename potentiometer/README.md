# Potentiometer Library for Raspberry Pi Pico

## ⚙️ Hardware Interface

| Raspberry Pi Pico Pin | Potentiometer Pin | Description    |
| --------------------- | ----------------- | -------------- |
| GP26 (ADC0)           | Wiper             | Analog Input 0 |
| GP27 (ADC1)           | Wiper             | Analog Input 1 |
| GP28 (ADC2)           | Wiper             | Analog Input 2 |
| 3V3(OUT)              | VCC               | 3.3V Power     |
| GND                   | GND               | Ground         |

-----

## 🛠️ Setup & Integration

To use this library, copy the `potentiometer` directory into your project and add the following to your `CMakeLists.txt`:

```cmake
# Add the library's subdirectory
add_subdirectory(potentiometer)

# Link the library to your main executable
target_link_libraries(my_project PRIVATE potentiometer_lib)
```

-----

## 💻 Example Code

Here is a basic example of how to read a potentiometer value.

```cpp
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "potentiometer.h"

int main() {
    stdio_init_all();
    
    // Initialize ADC
    adc_init();

    // Initialize potentiometer on ADC channel 0 (GP26)
    Potentiometer pot(0);
    pot.init();

    printf("Potentiometer Example\n");

    while (true) {
        // Read raw 12-bit value
        uint16_t raw = pot.readRaw();
        
        // Read as percentage
        float percent = pot.readPercent();
        
        // Read as normalized value (0.0 to 1.0)
        float normalized = pot.readNormalized();
        
        // Map to custom range (0 to 255)
        int32_t mapped = pot.readMapped(0, 255);
        
        printf("Raw: %d, Percent: %.1f%%, Normalized: %.3f, Mapped: %ld\n", 
               raw, percent, normalized, mapped);
        
        sleep_ms(500);
    }
    return 0;
}
```

-----

**License:** This project is licensed under the MIT License.