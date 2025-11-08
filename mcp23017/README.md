# MCP23017 I/O Expander Library for Raspberry Pi Pico

## ⚙️ Hardware Interface

| Raspberry Pi Pico Pin | MCP23017 Pin | Description |
| --------------------- | ------------ | ----------- |
| GP4                   | SDA          | I2C Data    |
| GP5                   | SCL          | I2C Clock   |
| 3V3(OUT)              | VDD          | 3.3V Power  |
| GND                   | VSS          | Ground      |

-----

## 🛠️ Setup & Integration

To use this library, copy the `mcp23017` directory into your project and add the following to your `CMakeLists.txt`:

```cmake
# Add the library's subdirectory
add_subdirectory(mcp23017)

# Link the library to your main executable
target_link_libraries(my_project PRIVATE mcp23017_lib)
```

-----

## 💻 Example Code

Here is a basic example of how to control GPIO pins using the MCP23017.

```cpp
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "mcp23017.h"

#define I2C_PORT i2c0
#define MCP23017_ADDRESS 0x20

int main() {
    stdio_init_all();
    
    // Initialize I2C
    i2c_init(I2C_PORT, 400 * 1000);
    gpio_set_function(4, GPIO_FUNC_I2C);
    gpio_set_function(5, GPIO_FUNC_I2C);
    gpio_pull_up(4);
    gpio_pull_up(5);

    // Initialize the MCP23017
    Mcp23017 mcp(I2C_PORT, MCP23017_ADDRESS);
    mcp.init();

    printf("MCP23017 Example\n");

    // Set pin 0 as output, pin 1 as input
    mcp.setPinDirection(0, Mcp23017::PinDirection::OUTPUT);
    mcp.setPinDirection(1, Mcp23017::PinDirection::INPUT);

    while (true) {
        // Toggle pin 0
        mcp.writePin(0, true);
        sleep_ms(500);
        mcp.writePin(0, false);
        sleep_ms(500);
        
        // Read pin 1
        bool pin1_state = mcp.readPin(1);
        printf("Pin 1 state: %s\n", pin1_state ? "HIGH" : "LOW");
    }
    return 0;
}
```

-----

**License:** This project is licensed under the MIT License.