To download: Navigate to "Releases" on the right, and click on .7z file
showcase/guide video - https://youtu.be/edFPnLBjc3E

**Program Information**

- **Platform:** Windows only

**Usage Instructions:**

1. Open `run.bat`.
2. If the console displays "SUCCESS, took x.xxx seconds," the program has worked.
3. If the console repeatedly shows "starting," try increasing `optimizationFactor` (default is 3.6) in `config.ini`. 
   - Increasing this setting will slow down the program but may reduce crashes.

**Post-Execution:**

- If successful, a folder named `src` should appear. This folder is your mod folder.

**Testing the Mod:**

1. Open HOI4 and add "Generated Map Mod" to your current playset.
2. Play the game.
3. If the game crashes, follow "Usage Instructions".

**Editing the Map:**

1. Open `input.bmp` in Paint.
2. Choose any HOI4-supported resolution for your image (must be a multiple of 256):
   - Examples: 512x512, 768x512, 512x768, 768x768, ..., 5632x2048.
   - If choosing a large resolution, increase `provinceSize` (default is 6).
3. Draw the map:
   - White color represents water.
   - Black color is filled in with nearby pixels.
   - Any other color represents a separate country.
4. Run the program to generate a new mod.

**Example Mod:**

- https://steamcommunity.com/sharedfiles/filedetails/?id=3299211370
