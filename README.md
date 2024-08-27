To download: Navigate to "Releases" on the right, and click on .7z file

showcase/guide video - youtu.be/edFPnLBjc3E

**Program Information**

- **Platform:** Windows only

**Usage Instructions:**

1. Open `run.bat`.
2. If the console displays "SUCCESS, took x.xxx seconds," the program has worked.
3. If the console repeatedly shows "starting," try increasing `optimizationFactor` or setting it to `100000` in `config.ini`. 
   - Increasing this setting will slow down the program but may reduce crashes.

**Testing the Mod:**

1. Open HOI4 and add "Generated Map Mod" to your current playset.
2. Play the game.
3. If the game crashes, follow "Usage Instructions".

**Post-Execution:**

- If successful, a folder named `src` should appear. This folder is your mod folder. 
If the mod is not showing up in the launcher then in the launcher go: 
1. All installed mods > upload mod > create a mod
2. After creation select the mod you have created in the list > "..." > show in folder
3. Then copy all files from `src` folder and paste them in the folder that the launcher has showed you

**Editing the Map:**

1. Open image `input.bmp`.
2. Choose any HOI4-supported resolution for your image (**must be a multiple of 256**):
   - Examples: 512x512, 768x512, 512x768, 768x768, ..., 5632x2048.
   - If choosing a large resolution, increase `provinceSize` (default is 6).
3. Draw the map(don't use brush tool):
   - White color represents water.
   - Black color is filled in with nearby pixels.
   - Any other color represents a separate country.
4. Export as 24 bit bmp image and name it `input.bmp`.
5. Run the program to generate a new mod.

**Example Mod:**

- https://steamcommunity.com/sharedfiles/filedetails/?id=3299211370

**Compilation flag if you want to compile source file yourself**

`g++ -std=c++2a -O3 -o C:\master.exe C:\master.cpp --static`

tutorial how to download C++ compiler: youtu.be/sQjI5vqKUEo
