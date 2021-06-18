#include <iostream>
#include <fstream>

unsigned long getByteCount(std::string path)
{
    std::ifstream stream(path, std::ios::in | std::ios::binary);

    unsigned long bytes = 0;
    char byte;
    while (stream.read(&byte, 1))
        bytes++;

    return bytes;
}

void writeDataToBuffer(char *buffer, std::string path, unsigned long dataSize)
{
    buffer[0] = dataSize & 0x00000000000000ff;
    buffer[1] = dataSize & 0x000000000000ff00;
    buffer[2] = dataSize & 0x0000000000ff0000;
    buffer[3] = dataSize & 0x00000000ff000000;
    buffer[4] = dataSize & 0x000000ff00000000;
    buffer[5] = dataSize & 0x0000ff0000000000;
    buffer[6] = dataSize & 0x00ff000000000000;
    buffer[7] = dataSize & 0xff00000000000000;

    unsigned long head = 8;

    std::ifstream stream(path, std::ios::in | std::ios::binary);
    char byte;
    while (stream.read(&byte, 1))
    {
        buffer[head] = byte;
        head++;
    }
}

unsigned long getPixels(std::string path)
{
    std::ifstream stream(path, std::ios::in);
    std::string line;
    getline(stream, line);
    unsigned long width, height;
    stream >> width;
    stream >> height;
    return height * width;
}

void writePixelsToImageBuffer(char *image, std::string path)
{
    std::ifstream stream(path, std::ios::in);
    std::string line;
    getline(stream, line);
    getline(stream, line);
    getline(stream, line);

    unsigned long head = 0;
    char byte;
    while (stream.read(&byte, 1))
    {
        image[head] = byte;
        head++;
    }
}

void writeDataToImage(char *data, char *image, unsigned long dataSize)
{
    unsigned long head = 0;
    for (unsigned long i = 0; i < dataSize; i++)
    {
        char byte = data[i];
        char temp;

        temp = image[head] & 0b00000011;
        image[head] = image[head] ^ temp;
        temp = byte & 0b00000011;
        image[head] = image[head] | temp;
        head++;

        temp = image[head] & 0b00000011;
        image[head] = image[head] ^ temp;
        temp = byte & 0b00001100;
        temp = temp >> 2;
        image[head] = image[head] | temp;
        head++;

        temp = image[head] & 0b00000011;
        image[head] = image[head] ^ temp;
        temp = byte & 0b00110000;
        temp = temp >> 4;
        image[head] = image[head] | temp;
        head++;

        temp = image[head] & 0b00000011;
        image[head] = image[head] ^ temp;
        temp = byte & 0b11000000;
        temp = temp >> 6;
        image[head] = image[head] | temp;
        head++;
    }
}

std::string getHeader(std::string path)
{
    std::ifstream stream(path, std::ios::in);
    std::string header = "";
    std::string line;

    getline(stream, line);
    header += line;
    getline(stream, line);
    header += "\n" + line;
    getline(stream, line);
    header += "\n" + line;
    header += "\n";

    return header;
}

void writeImage(std::string header, char *image, unsigned long pixels)
{
    std::cout << header;

    char byte;
    for (unsigned long i = 0; i < pixels * 3; i++)
    {
        byte = image[i];
        std::cout.write((char *)&byte, 1);
    }
}

int main(int argc, char **argv)
{
    std::string templatePath = std::string(argv[1]);
    std::string dataPath = std::string(argv[2]);

    unsigned long dataSize = getByteCount(dataPath);
    char *dataBuffer = (char *)malloc(dataSize + 8);

    writeDataToBuffer(dataBuffer, dataPath, dataSize);

    unsigned long pixels = getPixels(templatePath);
    char *imageBuffer = (char *)malloc(pixels * 3);

    writePixelsToImageBuffer(imageBuffer, templatePath);

    writeDataToImage(dataBuffer, imageBuffer, dataSize + 8);

    std::string header = getHeader(templatePath);

    writeImage(header, imageBuffer, pixels);

    // for (unsigned long i = 0; i < (dataSize + 8) * 4; i++)
    //     std::cout << imageBuffer[i];

    // unsigned long read;
    // std::cin.read((char *)&read, 8);
    // std::cout << read << std::endl;
}