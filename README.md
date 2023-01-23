# Shift Register Test

Simple code to test use of two shift registers. Both registers share a connection to the latch and clock lines.
There is a separate data line for each shift register.

Wiring requirements.

* GPIO 02     Latch
* GPIO 03     Clock
* GPIO 04     Data 01
* GPIO 05     Data 02

Ensure the CLK_INH pin is tied to ground. SER should also be grounded, though this should not affect the tests.