#include "bmp_file.h"

bmp_file::bmp_file(){/**< Default Constructor */}
bmp_file::~bmp_file(){/**< Default Destructor */}

/**< Assignment operator overload, copy image data to this */
void bmp_file::operator=(const bmp_file &b)
{
    fileData = b.fileData;
}

/**< The following functions extract data from the bitmap header */
unsigned long bmp_file::getFileSize(){return get32(2);}
unsigned long bmp_file::getStartOfBitmap(){return get32(10);}
unsigned long bmp_file::getWidth(){return get32(18);}
unsigned long bmp_file::getHeight(){return get32(22);}

/**< Extracts a 32-bit unsigned long value from fileData beginning with element LSBindex */
unsigned long bmp_file::get32(int LSBindex) {
    unsigned long temp = 0;
    for (int i = 3; i >=0; --i) {
        temp = (fileData[LSBindex+i] | temp << 8);
        temp |= fileData[LSBindex + i];
    }
    return temp;
}

/**< Creates an instance of bmp_file containing the specified file */
bmp_file::bmp_file(char* filepath) {
    std::ifstream infile;
    infile.open(filepath, std::ifstream::in | std::ifstream::binary);
    if (!infile){
        std::cout << "\nFile " << filepath << " not found.";
        return;
    } else {
        std::cout << "\nOpening " << filepath << "...";
    }
    char * buffer = new char [1];
    while (!infile.eof())
    {
        infile.read(buffer, 1);
        fileData.push_back(*buffer);
    }
    //get rid of extra byte
    fileData.pop_back();
}

/**< Outputs header data to the console using the std::cout stream */
void bmp_file::printData() {
    std::cout << "\nHeader data:";
    std::cout << "\n  Filesize: " << getFileSize();
    std::cout << "\n  Offset: " << getStartOfBitmap();
    std::cout << "\n  Width: " << getWidth();
    std::cout << "\n  Height: " << getHeight();
    std::cout << "\n  Vector Size: " << fileData.size();
}

unsigned char * bmp_file::getFileData()
{
    unsigned char *data = reinterpret_cast<unsigned char*>(&this->fileData[this->getStartOfBitmap()]);
    return data;
}
