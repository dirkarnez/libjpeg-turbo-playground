#include <iostream>
#include <string.h>
#include <cstdlib>
#include "turbojpeg.h"

int main()
{
  using namespace std;

  unsigned char *srcBuf; // passed in as a param containing pixel data in RGB pixel interleaved format
  tjhandle handle = tjInitCompress();

  if (handle == NULL)
  {
    const char *err = (const char *) tjGetErrorStr();
    cerr << "TJ Error: " << err << " UNABLE TO INIT TJ Compressor Object\n";
    return EXIT_FAILURE;
  }

  int jpegQual = 92;
  int width = 128;
  int height = 128;
  int nbands = 3;
  int flags = 0;
  unsigned char *jpegBuf = NULL;
  int pitch = width * nbands;
  int pixelFormat = TJPF_GRAY;
  int jpegSubsamp = TJSAMP_GRAY;
  if (nbands == 3)
  {
    pixelFormat = TJPF_RGB;
    jpegSubsamp = TJSAMP_411;
  }
  unsigned long jpegSize = 0;

  srcBuf = new unsigned char[width * height * nbands];
  for (int j = 0; j < height; j++)
  {
    for (int i = 0; i < width; i++)
    {
      srcBuf[(j * width + i) * nbands + 0] = (i) % 256;
      srcBuf[(j * width + i) * nbands + 1] = (j) % 256;
      srcBuf[(j * width + i) * nbands + 2] = (j + i) % 256;
    }
  }

  int tj_stat = tjCompress2(handle, srcBuf, width, pitch, height,
                            pixelFormat, &(jpegBuf), &jpegSize, jpegSubsamp, jpegQual, flags);
  if (tj_stat != 0)
  {
    const char *err = (const char *)tjGetErrorStr();
    cerr << "TurboJPEG Error: " << err << " UNABLE TO COMPRESS JPEG IMAGE\n";
    tjDestroy(handle);
    handle = NULL;
    return EXIT_FAILURE;
  }

  FILE *file = fopen("out.jpg", "wb");
  if (!file)
  {
    cerr << "Could not open JPEG file: " << strerror(errno);
    return EXIT_FAILURE;
  }
  if (fwrite(jpegBuf, jpegSize, 1, file) < 1)
  {
    cerr << "Could not write JPEG file: " << strerror(errno);
    return EXIT_FAILURE;
  }
  fclose(file);

  // write out the compress date to the image file
  // cleanup
  int tjstat = tjDestroy(handle); // should deallocate data buffer
  handle = 0;

  return 0;
}