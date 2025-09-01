#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "qrencode.h"
#include "png.h"

void write_png (const char *filename , QRcode *qrcode , int pixel_size)
{
	int width = qrcode -> width;
	if (width == 0)
	{
		fprintf (stderr , "QR code width is 0\n");
		return ;
	}

	int image_size = pixel_size * width;

	FILE *fp = fopen (filename , "wb");
	if (!fp)
	{
		fprintf (stderr , "[+] ERROR in open the %s file\n" , filename);
		exit (1);
	}
	png_structp png_ptr = png_create_write_struct (PNG_LIBPNG_VER_STRING , NULL , NULL , NULL);
	png_infop info_ptr = png_create_info_struct (png_ptr);
	if (!png_ptr || !info_ptr)
	{
		fprintf (stderr , "Failed to create PNG structures\n");
		exit (1);
	}
	if (setjmp(png_jmpbuf(png_ptr)))
	{
		fprintf (stderr , "Error during PNG creation\n");
		exit (1);
	}

	png_init_io (png_ptr, fp);
	png_set_IHDR (png_ptr , info_ptr , image_size , image_size , 8 , PNG_COLOR_TYPE_GRAY , PNG_INTERLACE_NONE , PNG_COMPRESSION_TYPE_DEFAULT , PNG_FILTER_TYPE_DEFAULT);
	png_write_info (png_ptr, info_ptr);

	png_bytep row = (png_bytep) malloc (image_size);
	unsigned char color;
	int y , x , i , j;
	for (y = 0 ; y < width ; y++)
	{
		for (i = 0; i < pixel_size; i++)
		{
			for (x = 0 ; x < width ; x++)
			{
				color = (qrcode -> data [y * width + x] & 0x01) ? 0 : 255;
				for (j = 0 ; j < pixel_size ; j++)
					row [x * pixel_size + j] = color;
			}
			png_write_row (png_ptr , row);
		}
	}

	png_write_end (png_ptr , NULL);
	png_destroy_write_struct (&png_ptr , &info_ptr);
	fclose (fp);
	free (row);
}

int main(int argc, char ** argv)
{
	if (argc < 3)
	{
        fprintf (stderr , "[+] usage : %s <url> <output.png>\n", argv[0]);
        return 0;
	}

	QRcode * qrcode = QRcode_encodeString(argv [1], 0, QR_ECLEVEL_H, QR_MODE_8, 1);
	if (!qrcode)
	{
		fprintf(stderr , "Failed to encode QR code\n");
		return 1;
	}

	int scale = 2000 / qrcode -> width;
	write_png (argv [2] , qrcode , scale);
	QRcode_free (qrcode);
	printf("QR Code Saved As: %s\n", argv [2]);
	return 0;
}
