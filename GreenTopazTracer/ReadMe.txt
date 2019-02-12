GreenTopazTracer  - ray tracer made for learning purposes.

Platform: Windows.

Created: January 17, 2018

-----

TODO:
- add the execution timer.
- using HDR right in the Color class seems to be faster. Check if it's really so; 
  if yes, think about something (but don't change the current color object). Maybe perform RGB/BGR conversion in the tone mapper.
  Measure the execution time again.
- after flipping the image vertically in the window (to correspond to the file output), a thin white stripe appeared at the top.
- if the window is closed during ray tracing, the app fails.
