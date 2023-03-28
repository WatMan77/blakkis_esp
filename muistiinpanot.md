# Nappilamput

1-2 Sähkö kulkee kun EI paina

3-4 Sähkö kulkee kun PAINAA

## How to connect them?

               pin
                |
                |
vcc---Resistor------/ *------gnd

## How to print a .wav file in hexadecimal?
hexdump -v -e '16/1 "0x%02x, "' -e '"\n"' <file.wav> > alarm.txt

OR

ffmpeg -i alarm.wav -ac 1 -ar 8000 -f u8 alarm.raw
xxd -i alarm.raw > alarm.txt