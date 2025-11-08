# picolib.h
An easy way to use c++ with common modules

---

> [!IMPORTANT]
> As you can see, main branch is empty. This is caused by the fact that i don't have time to finish/test all of the libs from dev branch.
> For now the only lib that im 100% that works is **mcp23017**, i will try to check on the rest as soon as i can

So... im big RPi Pico fan. Why? Cause its cheap. 

I'm also not a big fan of python. Why? Try importing 10+ libs and you'll understand.

Another way of programming microcontrollers is c/c++, but it comes with one big disadvantage. Most of well known and loved adafruit components comes with native circuit-python support, so when you try to use c/c++ for those it can be quite difficult. Thats why i created this project. So me and you can use the queen of all programming languages with ease.

## How does this work?
It is quite simple actually, project is organized into folders, in those folders there are `README.md` files with instructions on how to use and import each lib.

For most cases you just copy directory with desired library, lets use `ht16k33` lib for this. After copying the folder, just put those lines in your `CMakeLists.txt` file. And it's done.
```cmake
# Add the library's subdirectory
add_subdirectory(ht16k33)

# Link the library to your main executable
target_link_libraries(my_project PRIVATE ht16k33_lib)
```

## What do i use for testing?
For now its good old RPi Pico W, but in the future i might test those libs also on Pico 2

### What if some library does not work?
Just open an issue, i will look into it as fast as i can

## License

This project is licensed under the **MIT License**. See the `LICENSE.md` file for details.

## Attributions

This project is a port and derivative work based on the following original libraries:

* **LiquidCrystal_I2C:** by Lucas Maziero  ([GitHub](https://github.com/lucasmaziero/LiquidCrystal_I2C))
* **Adafruit_MCP3008:** by Adafruit Industries ([GitHub](https://github.com/adafruit/Adafruit_MCP3008))

This project includes the original copyright and license notices from these libraries. Please see the `NOTICE.md` file for full details.