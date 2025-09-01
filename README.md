## 🚀 How to Build

To compile the project, use the provided script:

```bash
chmod +x compile.sh
sudo ./compile.sh
```
Or manually:
Requirements:
1- C compiler (preferably gcc)
2- Standard C libraries for working with QR code and png format called libqrencode-dev and libpng-dev.
Install these according to your package manager, for example for Debian based systems with root privilege:

```bash
apt install -y gcc libqrencode-dev libpng-dev
```

After running, the QR file is ready for you.
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
