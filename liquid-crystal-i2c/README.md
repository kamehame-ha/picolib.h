# LiquidCrystal I2C Library for Raspberry Pi Pico

## ⚙️ Hardware Interface

| Raspberry Pi Pico Pin | LCD I2C Module Pin | Description |
| --------------------- | ------------------ | ----------- |
| GP4                   | SDA                | I2C Data    |
| GP5                   | SCL                | I2C Clock   |
| 5V(VBUS)              | VCC                | 5V Power    |
| GND                   | GND                | Ground      |

-----

## 🛠️ Setup & Integration

To use this library, copy the `liquid-crystal-i2c` directory into your project and add the following to your `CMakeLists.txt`:

```cmake
# Add the library's subdirectory
add_subdirectory(liquid-crystal-i2c)

# Link the library to your main executable
target_link_libraries(my_project PRIVATE liquid_crystal_i2c_lib)
```

-----

## 💻 Example Code

Here is a basic example of how to display text on a 16x2 LCD.

```cpp
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "liquid-crystal-i2c.h"

#define I2C_PORT i2c0
#define LCD_ADDRESS 0x27

int main() {
    stdio_init_all();
    
    // Initialize I2C
    i2c_init(I2C_PORT, 400 * 1000);
    gpio_set_function(4, GPIO_FUNC_I2C);
    gpio_set_function(5, GPIO_FUNC_I2C);
    gpio_pull_up(4);
    gpio_pull_up(5);

    // Initialize the LCD (16 columns, 2 rows)
    LiquidCrystal_I2C lcd(I2C_PORT, LCD_ADDRESS, 16, 2);
    if (!lcd.init()) {
        printf("LCD initialization failed!\n");
        return 1;
    }

    printf("LCD Example\n");

    lcd.backlight();
    lcd.setCursor(0, 0);
    lcd.print("Hello, World!");
    lcd.setCursor(0, 1);
    lcd.print("Pico LCD Test");

    while (true) {
        sleep_ms(1000);
    }
    return 0;
}
```

-----

**License:** This project is licensed under the MIT License.