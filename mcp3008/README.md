# MCP3008 ADC Library for Raspberry Pi Pico

## ⚙️ Hardware Interface

| Raspberry Pi Pico Pin | MCP3008 Pin | Description   |
| --------------------- | ----------- | ------------- |
| GP19                  | CS          | Chip Select   |
| GP18                  | SCK         | SPI Clock     |
| GP16                  | TX (MOSI)   | Data In (DIN) |
| GP17                  | RX (MISO)   | Data Out (DOUT)|
| 3V3(OUT)              | VDD / VREF  | 3.3V Power    |
| GND                   | AGND / DGND | Ground        |

-----

## 🛠️ Setup & Integration

To use this library, copy the `mcp3008` directory into your project and add the following to your `CMakeLists.txt`:

```cmake
# Add the library's subdirectory
add_subdirectory(mcp3008)

# Link the library to your main executable
target_link_libraries(my_project PRIVATE mcp3008_lib)
```

-----

## 💻 Example Code

Here is a basic example of how to read from analog channel 0.

```cpp
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "mcp3008.h"

#define SPI_PORT spi0
#define PIN_CS   19

int main() {
    stdio_init_all();
    
    // Initialize SPI
    spi_init(SPI_PORT, 1000