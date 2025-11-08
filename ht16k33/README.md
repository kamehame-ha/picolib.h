# HT16K33 Seven-Segment Display Library for Raspberry Pi Pico

## ⚙️ Hardware Interface

| Raspberry Pi Pico Pin | HT16K33 Pin | Description |
| --------------------- | ----------- | ----------- |
| GP4                   | SDA         | I2C Data    |
| GP5                   | SCL         | I2C Clock   |
| 3V3(OUT)              | VCC         | 3.3V Power  |
| GND                   | GND         | Ground      |

-----

## 🛠️ Setup & Integration

To use this library, copy the `ht16k33` directory into your project and add the following to your `CMakeLists.txt`:

```cmake
# Add the library's subdirectory
add_subdirectory(ht16k33)

# Link the library to your main executable
target_link_libraries(my_project PRIVATE ht16k33_lib)
```

-----

## 💻 Example Code

Here is a basic example of how to display numbers on the seven-segment display.

```cpp
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "ht16k33.h"

#define I2C_PORT i2c0
#define I2C_ADDRESS 0x70

int main() {
    stdio_init_all();
    
    // Initialize I2C
    i2c_init(I2C_PORT, 400 * 1000);
    gpio_set_function(4, GPIO_FUNC_I2C);
    gpio_set_function(5, GPIO_FUNC_I2C);
    gpio_pull_up(4);
    gpio_pull_up(5);

    // Initialize the display
    Ht16k33 display(I2C_PORT, I2C_ADDRESS);
    display.init();

    printf("HT16K33 Display Example\n");

    int counter = 0;
    while (true) {
        // Display counter value
        display.displayInt(counter++);
        
        // Display time format
        display.displayTime(12, 34);
        sleep_ms(1000);
        
        // Display date format
        display.displayDate(25, 12);
        sleep_ms(1000);
    }
    return 0;
}
```

-----

**License:** This project is licensed under the MIT License.