# DupliChecker
<p>
Qt project on C++.
</p>
<p>
This program shows equal files from two different directories that you specified.
</p>

## User Guide: 
1. Specify two comlete path to directories like "D:\Temp\1"
2. Press "Process" button

## Additional info:
- You can specify relative path like ".\folder"
- This program can use both type of slashes - / and \
- This program compare files less than 100kB byte - by - byte, and other files string - by - string

### Example folder contains:
- DriverPack solution online installer as "binary.exe"
- Sample photo as "image.jpg"
- Schubert - Der Erlkönig as "video.mp4"
- Compressed binary.exe, image.jpg and video.mp4 files as "compressed.rar"
- Small text file as "text.txt". This file has one duplicate "same text copy.txt" and another with Macintosh EOS type - "text with CR"
- Large text file as "text large.txt". This file has duplicate with Macintosh EOS type - "text large with CR.txt"

### Output with example folders must be:
<p>
"./1/binary.exe" equal "./2/same binary.exe"
</p><p>
"./1/compressed.rar" equal "./2/compressed.rar"
</p><p>
"./1/image.jpg" equal "./2/same image.jpg"
</p><p>
"./1/text large.txt" equal "./2/same text large.txt"
</p><p>
"./1/text.txt" equal "./2/same text copy.txt"
</p><p>
"./1/text.txt" equal "./2/same text.txt"
</p><p>
"./1/video.mp4" equal "./2/same video.mp4"
</p>

