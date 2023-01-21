echo Deploying Centre Module to the Pico.
script="$0"
basename="${script%/*}"

openocd -f interface/cmsis-dap.cfg -f target/rp2040.cfg -c "adapter speed 4000" -c "program ${basename}/build/src/shift-register.elf verify reset exit"

