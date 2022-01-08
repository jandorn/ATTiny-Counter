# ATTiny Counter

I built this project in the end of 2020 as a christmas present for my dad.

![7 Segment Counter Showcase](media/7seg_counter_gif.gif)

This project got some traction on [reddit](https://www.reddit.com/r/electronics/comments/kse3wp/i_made_a_freeform_circuit_counter_for_my_dad_to/), and I wanted to release the code used for the Attiny85.

Some technical details from my comment on the reddit post:

> This project is powered by an ATTiny85. Five of its pins were used, three of them for the MAX7219 module controling the 7-segment display and one for the button and piezo buzzer respectively. The user can give input through the button. A normal short press to count one up and a long 6-second press to reset it to 0. I also added a simple switch. The microcontroller stores the value in its EEPROM so it doesn't lose it when powered off. I used a charger of an old phone as a power supply. My dad was really excited when he got it for Christmas and it should certainly help him quit smoking :)

Thanks for reading. :)