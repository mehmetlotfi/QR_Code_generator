## 🚀 How to Build

To compile the project, use the provided script:

```bash
chmod +x compile.sh
sudo ./compile.sh
```
Or manually:

  Requirements:
  1- C compiler (like gcc)
  
  2- Standard C libraries for working with QR code and png format called libqrencode-dev and libpng-dev.

  
  Install these according to your package manager, for example for Debian based systems with root privilege:

  ```bash
    apt-get install -y gcc libqrencode-dev libpng-dev
  ```
  After these 3 packages are fully installed, it is time to compile the qr_generator.c file:
  To do this, enter:
  ```bash
  gcc qr_generator.c -o QR -lqrencode -lpng
  ```
  It actually links the 2 libraries we installed to the program.
  (You can do this with any compiler other than gcc)

After running, the QR executable file is ready for you.
To create a QR code, run the QR program and execute the following commands (which are also in the program's usage):

```bash
./QR <url> <output.png>
```
Where url is the link where you want to save the QR code in the output.png file. 
Note that the program is written so that the output file format is png.
example :
```bash
./QR https://github.com/mehmetlotfi qr_code.png
```
