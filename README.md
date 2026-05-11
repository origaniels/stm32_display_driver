# Overview

The goal of this small project is to write a small driver for the SSD1306 I2C display using the STM32C031C6's I2C IP.
The driver should be as exhaustive as possible so as to allow for the best flexibility between performance and simplicity.

# Conclusions & Takeways

In progress...

# Dependencies

To run this project you will need the following dependencies (Arch Linux):

```
pacman -S arm-none-eabi-gcc arm-none-eabi-newlib
```

```
yay -S stlink
```

# Hardware

For this project I used a GM00965 128*64 OLED I2C display and a Nucleo C031C6 developpement board.

# Setup and running

Flash and compile the program running:

```
make flash
```


# References

- [STM32C0x1 MCU reference manual](https://www.st.com/resource/en/reference_manual/rm0490-stm32c0x1-advanced-armbased-32bit-mcus-stmicroelectronics.pdf)
- [STM32C031Cx datasheet](https://www.st.com/resource/en/datasheet/stm32c031c4.pdf)
- [ARM Cortex M0+ Documentation](https://developer.arm.com/documentation/dui0662/b)
- [Nucleo C031C6 user manual](https://www.st.com/resource/en/user_manual/um2953-stm32-nucleo64-board-mb1717-stmicroelectronics.pdf)
- [SSD1306 reference manual](https://cdn-shop.adafruit.com/datasheets/SSD1306.pdf)


