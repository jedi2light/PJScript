# PJScript - TJS (Text adventure game Javascript) compiler and interpreter

## What's the goal?

Have you ever played **Nekopara**? If so, you know what the kind of video games it is.  
**Nekopara** is the visual novel, and every visual novel nowadays are based on **RenPy**
visual novel engine, as you may be heard. Some people even use **Unity** for that, but...  
Anyways, **Nekopara** is based on a **modified** version of **KrKrX** visual novel engine.
There are also a lot of other good novels based on that engine as well... But it's a lyric.  

So what's the **PJScript** project is for? **KrKrX** engine has two primary components. Hm...
Have you heard about Electron desktop applications? They are regular web-sites. but have a specific
JS runtime and their interface is written in HTML/CSS. Well, **KrKrX** architecture is a bit similar to this.  
But **KrKrX** does not use either plain JS or HTML/CSS. This engine has its own analogues: **TJS** and **KAG3**.

And now we're close to the point! This project is an attempt to interpret or even compile **TJS** scripts! And when
I say **compile**, I mean this project can actually take the **TJS** source code and **translate**
(**translation** is the valid variant of **compilation** (as long as we can get ELF/EXE binary file at the end)) it
to **C++**, compile this **C++** source with your system compiler (**clang++** for instance) and link with the tiny
replica of **KrKrX**' **TJS** runtime

## What's the license?

**PJScript** project was initially created in late June 2020 by @jedi2light, and licensed under **WTFPL** public license